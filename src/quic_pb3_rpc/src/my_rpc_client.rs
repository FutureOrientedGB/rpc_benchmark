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

// my client
pub mod quick_rpc_client;


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

    type MyQuickRpcClient = quick_rpc_client::QuickRpcClient::<bidirectional::RpcRequest, bidirectional::RpcResponse>;
    if let Ok((endpoint, connection)) = MyQuickRpcClient::connect(cli.host, cli.port) {
        // test unary
        let mut req = bidirectional::RpcRequest::default();
        req.version = 1;
        req.text = "Hello world";
        req.content = "0123456789abcdefghijklmnopqrstuvwxyz";
        let resp = MyQuickRpcClient::unary_request(connection, req).await?;

        // test client stream
        let (tx, rx) = std::sync::mpsc::channel();
        let resp = MyQuickRpcClient::client_stream_request(connection, rx).await?;

        // test server stream
        let rx = MyQuickRpcClient::server_stream_request(connection, req).await?;

        // test bidirectional stream
        let (tx, rx) = std::sync::mpsc::channel();
        let rx = MyQuickRpcClient::bidirectional_stream_test(connection, rx).await?;

        // wait for all connections on the endpoint to be cleanly shut down
        endpoint.wait_idle().await;
    }

    Ok(())
}



