// std
use std::{self, sync::Arc};

// anyhow
use anyhow::Result;

// protobuf (prost)
use prost;

// quinn
use quinn::{Endpoint, ServerConfig};

// rustls
use rustls::pki_types::{CertificateDer, PrivatePkcs8KeyDer};



pub trait QuickRpcService<RpcRequestType: Default + prost::Message, RpcResponseType: Default + prost::Message> {
    async fn run_until_complete(
        host: String,
        port: u16,
        complete_flag: &bool,
        min_ms_per_loop: u64,
        accpet_incoming_connections_fn: fn(incoming_connection: quinn::Incoming),
    ) {
        if let Ok(endpoint) = Self::setup(host, port).await {
            while !complete_flag {
                match tokio::time::timeout(
                    std::time::Duration::from_millis(min_ms_per_loop),
                    endpoint.accept(),
                )
                .await
                {
                    Err(_) => {
                        // timeout
                        continue;
                    }
                    Ok(None) => {
                        // the endpoint is close
                        break;
                    }
                    Ok(Some(incoming_connection)) => accpet_incoming_connections_fn(incoming_connection)
                }
            }
        }
    }

    async fn setup(host: String, port: u16) -> Result<Endpoint> {
        // setup tls
        rustls::crypto::ring::default_provider()
            .install_default()
            .expect("Failed to install rustls crypto provider");

        // config transport
        let bind_addr = format!("{}:{}", host, port).parse()?;
        let cert = rcgen::generate_simple_self_signed(vec![host])?;
        let cert_der = CertificateDer::from(cert.cert);
        let priv_key = PrivatePkcs8KeyDer::from(cert.key_pair.serialize_der());
        let mut server_config =
            ServerConfig::with_single_cert(vec![cert_der.clone()], priv_key.into())?;
        let transport_config = Arc::get_mut(&mut server_config.transport).unwrap();
        transport_config.max_concurrent_uni_streams(0_u8.into());

        match Endpoint::server(server_config, bind_addr) {
            Ok(endpoint) => {
                return Ok(endpoint);
            }
            Err(e) => {
                tracing::error!("Endpoint::server error: {error}", error = e.to_string());
                return Err(e.into());
            }
        }
    }

    async fn read_payload(recv_stream: &mut quinn::RecvStream) -> Result<Vec<u8>> {
        // read size header
        let mut header = vec![0_u8; 4];
        if let Err(e) = recv_stream.read_exact(header.as_mut_slice()).await {
            tracing::error!(
                "recv_stream.read_exact error: {error}",
                error = e.to_string()
            );
            return Err(e.into());
        }

        let mut size = 0;
        if let Ok(bytes) = header.try_into() {
            size = u32::from_be_bytes(bytes);
        }

        // read payload content
        let mut payload = vec![0_u8; size as usize];
        if let Err(e) = recv_stream.read_exact(payload.as_mut_slice()).await {
            tracing::error!(
                "recv_stream.read_exact error: {error}",
                error = e.to_string()
            );
            return Err(e.into());
        }

        Ok(payload)
    }

    async fn send_payload(
        send_stream: &mut quinn::SendStream,
        response: RpcResponseType,
    ) {
        // encode
        let mut content = Vec::new();
        if let Err(e) = response.encode(&mut content) {
            tracing::error!("resp.encode error: {error}", error = e.to_string());
            return;
        }

        // write size header
        let header = u32::to_be_bytes(content.len() as u32);
        if let Err(e) = send_stream.write_all(&header).await {
            tracing::error!(
                "send_stream.write_all error: {error}",
                error = e.to_string()
            );
            return;
        }

        // write payload content
        if let Err(e) = send_stream.write_all(&content).await {
            tracing::error!(
                "send_stream.write_all error: {error}",
                error = e.to_string()
            );
            return;
        }
    }

    async fn on_connect(incoming_connection: quinn::Incoming) {
        match incoming_connection.await {
            Err(e) => {
                tracing::error!(
                    "incoming_connection.await error: {error}",
                    error = e.to_string()
                );
            }
            Ok(connection) => {
                // accept the next incoming bidirectional stream
                match connection.accept_bi().await {
                    Err(e) => {
                        tracing::error!(
                            "connection.accept_bi error: {error}",
                            error = e.to_string()
                        );
                    }
                    Ok((mut s, mut r)) => {
                        Self::on_request(&mut s, &mut r).await;
                    }
                }
            }
        }
    }

    async fn on_request(send_stream: &mut quinn::SendStream, recv_stream: &mut quinn::RecvStream) {
        if let Ok(payload) = Self::read_payload(recv_stream).await {
            match RpcRequestType::decode(&payload[..]) {
                Err(e) => {
                    tracing::error!("RpcRequest::decode error: {error}", error = e.to_string());
                }
                Ok(request) => {
                    Self::on_service(send_stream, recv_stream, request).await;
                }
            }
        }
    }

    async fn on_service(
        send_stream: &mut quinn::SendStream,
        recv_stream: &mut quinn::RecvStream,
        request: RpcRequestType,
    );

    async fn on_method(
        send_stream: &mut quinn::SendStream,
        recv_stream: &mut quinn::RecvStream,
        request: RpcRequestType,
    );
}
