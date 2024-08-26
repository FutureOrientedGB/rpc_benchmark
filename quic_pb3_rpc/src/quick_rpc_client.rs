// std
use std::{net::ToSocketAddrs, str::FromStr, sync::Arc};

// anyhow
use anyhow::{anyhow, Result};

// protobuf (prost)
use prost;

// quinn
use quinn::{ClientConfig, Connection, Endpoint};
use quinn_proto::crypto::rustls::QuicClientConfig;

// rustls
use rustls::pki_types::{CertificateDer, ServerName, UnixTime};

// tracing
use tracing;

// url
use url::Url;



pub trait QuickRpcClient<
    RpcRequestType: Default + prost::Message,
    RpcResponseType: Default + prost::Message,
>
{
    async fn connect(host: String, port: u16) -> Result<(Endpoint, Connection)> {
        let endpoint = Self::setup().await?;

        // prepare url
        let url = Url::from_str(&format!("https://{}:{}/", host, port)).unwrap();
        let host = url.host_str().unwrap();
        let addr = (host, url.port().unwrap_or(4433))
            .to_socket_addrs()?
            .next()
            .ok_or_else(|| anyhow!("couldn't resolve to an address"))?;

        // connect to server
        let connection = endpoint
            .connect(addr, host)?
            .await
            .map_err(|e| anyhow!("failed to connect: {}", e))?;

        Ok((endpoint, connection))
    }

    async fn write_request(send_stream: &mut quinn::SendStream, request: RpcRequestType) {
        // encode
        let mut content = Vec::new();
        if let Err(e) = request.encode(&mut content) {
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

    async fn read_response(recv_stream: &mut quinn::RecvStream) -> Result<RpcResponseType> {
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

        match RpcResponseType::decode(&payload[..]) {
            Ok(resp) => {
                return Ok(resp);
            }
            Err(e) => {
                tracing::error!(
                    "RpcResponseType::decode error: {error}",
                    error = e.to_string()
                );
                return Err(e.into());
            }
        }
    }

    async fn unary_request(
        connection: &Connection,
        request: RpcRequestType,
    ) -> Result<RpcResponseType> {
        // open streams
        let (mut send_stream, mut recv_stream) = connection
            .open_bi()
            .await
            .map_err(|e| anyhow!("failed to open stream: {}", e))
            .unwrap();

        // write
        Self::write_request(&mut send_stream, request).await;

        // read
        Self::read_response(&mut recv_stream).await
    }

    async fn client_stream_request(
        connection: &Connection,
    ) -> Result<(RpcResponseType, quinn::SendStream)> {
        // open streams
        let (mut send_stream, mut recv_stream) = connection
            .open_bi()
            .await
            .map_err(|e| anyhow!("failed to open stream: {}", e))
            .unwrap();

        // read
        Ok((Self::read_response(&mut recv_stream).await?, send_stream))
    }

    async fn server_stream_request(
        connection: &Connection,
        request: RpcRequestType,
    ) -> Result<quinn::RecvStream> {
        // open streams
        let (mut send_stream, mut recv_stream) = connection
            .open_bi()
            .await
            .map_err(|e| anyhow!("failed to open stream: {}", e))
            .unwrap();

        // write
        Self::write_request(&mut send_stream, request).await;

        Ok(recv_stream)
    }

    async fn bidirectional_stream_request(
        connection: &Connection,
    ) -> Result<(quinn::SendStream, quinn::RecvStream)> {
        // open streams
        let (mut send_stream, mut recv_stream) = connection
            .open_bi()
            .await
            .map_err(|e| anyhow!("failed to open stream: {}", e))
            .unwrap();

        Ok((send_stream, recv_stream))
    }

    async fn setup() -> Result<Endpoint> {
        // setup tls
        rustls::crypto::ring::default_provider()
            .install_default()
            .expect("Failed to install rustls crypto provider");

        // set endpoint config
        let mut endpoint = Endpoint::client("[::]:0".parse().unwrap()).unwrap();
        let client_config = rustls::ClientConfig::builder()
            .dangerous()
            .with_custom_certificate_verifier(SkipServerVerification::new())
            .with_no_client_auth();
        endpoint.set_default_client_config(ClientConfig::new(Arc::new(
            QuicClientConfig::try_from(client_config).unwrap(),
        )));

        Ok(endpoint)
    }
}

/// Dummy certificate verifier that treats any certificate as valid.
/// NOTE, such verification is vulnerable to MITM attacks, but convenient for testing.
#[derive(Debug)]
struct SkipServerVerification(Arc<rustls::crypto::CryptoProvider>);

impl SkipServerVerification {
    fn new() -> Arc<Self> {
        Arc::new(Self(Arc::new(rustls::crypto::ring::default_provider())))
    }
}

impl rustls::client::danger::ServerCertVerifier for SkipServerVerification {
    fn verify_server_cert(
        &self,
        _end_entity: &CertificateDer<'_>,
        _intermediates: &[CertificateDer<'_>],
        _server_name: &ServerName<'_>,
        _ocsp: &[u8],
        _now: UnixTime,
    ) -> Result<rustls::client::danger::ServerCertVerified, rustls::Error> {
        Ok(rustls::client::danger::ServerCertVerified::assertion())
    }

    fn verify_tls12_signature(
        &self,
        message: &[u8],
        cert: &CertificateDer<'_>,
        dss: &rustls::DigitallySignedStruct,
    ) -> Result<rustls::client::danger::HandshakeSignatureValid, rustls::Error> {
        rustls::crypto::verify_tls12_signature(
            message,
            cert,
            dss,
            &self.0.signature_verification_algorithms,
        )
    }

    fn verify_tls13_signature(
        &self,
        message: &[u8],
        cert: &CertificateDer<'_>,
        dss: &rustls::DigitallySignedStruct,
    ) -> Result<rustls::client::danger::HandshakeSignatureValid, rustls::Error> {
        rustls::crypto::verify_tls13_signature(
            message,
            cert,
            dss,
            &self.0.signature_verification_algorithms,
        )
    }

    fn supported_verify_schemes(&self) -> Vec<rustls::SignatureScheme> {
        self.0.signature_verification_algorithms.supported_schemes()
    }
}
