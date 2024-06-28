// std
use std::{error::Error, net::ToSocketAddrs, str::FromStr, sync::Arc};

// anyhow
use anyhow::{anyhow, Result};

// quinn
use quinn::{ClientConfig, Connection, Endpoint};
use quinn_proto::crypto::rustls::QuicClientConfig;

// rustls
use rustls::pki_types::{CertificateDer, ServerName, UnixTime};

// cli
use structopt::StructOpt;

// time
use time::{macros::format_description, UtcOffset};

// tracing
use tracing;
use tracing_subscriber::{self, fmt::time::OffsetTime};

// url
use url::Url;

// bidirectional proto
pub mod bidirectional {
    tonic::include_proto!("bidirectional");
}


#[derive(StructOpt)]
struct CommandLine {
    #[structopt(long, default_value = "localhost")]
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
            .name("quic_pb3_client")
            .version("2024.6.28.1")
            .get_matches(),
    );

    // setup tracing log
    tracing_subscriber::fmt()
        .json()
        .with_max_level(tracing::Level::from_str(&cli.log_level)?)
        .with_timer(OffsetTime::new(
            UtcOffset::from_hms(8, 0, 0).unwrap(),
            format_description!("[year]-[month]-[day] [hour]:[minute]:[second].[subsecond]"),
        ))
        .with_line_number(true)
        .with_ansi(false)
        .init();

    // setup endpoint
    let endpoint = setup_endpoint().await?;

    // connect
    let connection = connect(&endpoint, cli.host, cli.port).await?;

    // request
    request(connection).await?;

    // wait for all connections on the endpoint to be cleanly shut down
    endpoint.wait_idle().await;

    Ok(())
}

async fn setup_endpoint() -> Result<Endpoint> {
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

async fn connect(endpoint: &Endpoint, host: String, port: u16) -> Result<Connection> {
    // prepare url
    let url = Url::from_str(&format!("https://{}:{}/", host, port)).unwrap();
    let host = url.host_str().unwrap();
    let addr = (host, url.port().unwrap_or(4433))
        .to_socket_addrs()
        .unwrap()
        .next()
        .ok_or_else(|| anyhow!("couldn't resolve to an address"))
        .unwrap();

    // connect to server
    let connection = endpoint
        .connect(addr, host)
        .unwrap()
        .await
        .map_err(|e| anyhow!("failed to connect: {}", e))
        .unwrap();

    Ok(connection)
}

async fn request(connection: Connection) -> Result<()> {
    // open streams
    let (mut send_stream, mut recv_stream) = connection
        .open_bi()
        .await
        .map_err(|e| anyhow!("failed to open stream: {}", e))
        .unwrap();

    // write
    send_stream
        .write_all(String::from("Hello World").as_bytes())
        .await
        .unwrap();

    // read
    let mut buf = Vec::new();
    buf.resize(11, 0);
    match recv_stream.read_exact(buf.as_mut_slice()).await {
        Ok(_) => {
            let text = String::from_utf8(buf).unwrap();
            tracing::info!("read_exact: {}", text);
        }
        Err(e) => {
            tracing::info!("read_exact error: {error}", error = e.to_string());
        }
    }

    // close
    send_stream.finish().unwrap();
    connection.close(0u32.into(), b"done");

    Ok(())
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
