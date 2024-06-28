// std
use std::{error::Error, str::FromStr, sync::Arc};

// anyhow
use anyhow::Result;

// quinn
use quinn::{Endpoint, ServerConfig};

// rustls
use rustls::pki_types::{CertificateDer, PrivatePkcs8KeyDer};

// cli
use structopt::StructOpt;

// time
use time::{macros::format_description, UtcOffset};

// tracing
use tracing;
use tracing_subscriber::{self, fmt::time::OffsetTime};

// bidirectional proto
pub mod bidirectional {
    tonic::include_proto!("bidirectional");
}


#[derive(StructOpt)]
struct CommandLine {
    #[structopt(long, default_value = "[::1]")]
    host: String,

    #[structopt(long, default_value = "4433")]
    port: u16,

    #[structopt(long, default_value = "INFO")]
    log_level: String,
}


#[tokio::main]
async fn main() -> Result<(), Box<dyn Error + Send + Sync + 'static>> {
    // parse command line arguments
    let cli = CommandLine::from_clap(
        &CommandLine::clap()
            .name("quic_pb3_server")
            .version("2024.6.28.1")
            .get_matches(),
    );

    // setup tracing log
    tracing_subscriber::fmt()
        .json()
        .with_max_level(tracing::Level::from_str(&cli.log_level)?)
        .with_timer(OffsetTime::new(
            UtcOffset::from_hms(8, 0, 0)?,
            format_description!("[year]-[month]-[day] [hour]:[minute]:[second].[subsecond]"),
        ))
        .with_line_number(true)
        .with_ansi(false)
        .init();

    // setup endpoint
    let endpoint = setup_endpoint(cli.host, cli.port).await?;

    // accept incoming connections
    accept_incoming_connections(endpoint).await?;

    Ok(())
}

async fn setup_endpoint(host: String, port: u16) -> Result<Endpoint> {
    // setup tls
    rustls::crypto::ring::default_provider()
        .install_default()
        .expect("Failed to install rustls crypto provider");

    // config transport
    let bind_addr = format!("{}:{}", host, port).parse()?;
    let cert = rcgen::generate_simple_self_signed(vec!["localhost".into()])?;
    let cert_der = CertificateDer::from(cert.cert);
    let priv_key = PrivatePkcs8KeyDer::from(cert.key_pair.serialize_der());
    let mut server_config =
        ServerConfig::with_single_cert(vec![cert_der.clone()], priv_key.into())?;
    let transport_config = Arc::get_mut(&mut server_config.transport).unwrap();
    transport_config.max_concurrent_uni_streams(0_u8.into());

    Ok(Endpoint::server(server_config, bind_addr)?)
}

async fn accept_incoming_connections(endpoint: Endpoint) -> Result<()> {
    loop {
        match tokio::time::timeout(std::time::Duration::from_secs(1), endpoint.accept()).await {
            Err(_) => {
                // timeout
                continue;
            }
            Ok(None) => {
                // the endpoint is close
                break;
            }
            Ok(Some(incoming_connection)) => {
                tokio::spawn(async move {
                    match on_connect(incoming_connection).await {
                        Err(e) => {
                            tracing::error!("on_connect error: {error}", error = e.to_string());
                        }
                        Ok(_) => {}
                    }
                });
            }
        }
    }

    Ok(())
}

async fn on_connect(incoming_connection: quinn::Incoming) -> Result<()> {
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
                    tracing::error!("accept_bi error: {error}", error = e.to_string());
                    return Ok(());
                }
                Ok(stream) => match on_request(stream.0, stream.1).await {
                    Ok(_) => {}
                    Err(e) => {
                        tracing::error!("on_request error: {error}", error = e.to_string());
                        return Ok(());
                    }
                },
            };
        }
    }

    Ok(())
}

async fn on_request(
    mut send_stream: quinn::SendStream,
    mut recv_stream: quinn::RecvStream,
) -> Result<()> {
    // read
    let mut buf = Vec::new();
    buf.resize(11, 0);
    match recv_stream.read_exact(buf.as_mut_slice()).await {
        Err(e) => {
            tracing::error!("read_exact error: {error}", error = e.to_string());
        }
        Ok(_) => {
            // write
            send_stream.write_all(buf.as_slice()).await?;

            let text = String::from_utf8(buf)?;
            tracing::info!("read_exact: {}", text);

            // wait client to recv
            tokio::time::sleep(std::time::Duration::from_millis(200)).await;
        }
    }

    Ok(())
}
