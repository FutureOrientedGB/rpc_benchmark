// std
use std::{error::Error, net::ToSocketAddrs, str::FromStr, sync::Arc};

// anyhow
use anyhow::{anyhow, Result};

use bidirectional::{RpcRequest, RpcResponse};
use quick_rpc_client::QuickRpcClient;
// quinn
use quinn::{ClientConfig, Connection, Endpoint};
use quinn_proto::{crypto::rustls::QuicClientConfig, SendStream};

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


pub struct MyQuickRpcClient {}

impl QuickRpcClient<bidirectional::RpcRequest, bidirectional::RpcResponse> for MyQuickRpcClient {
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

    if let Ok((endpoint, connection)) = MyQuickRpcClient::connect(cli.host, cli.port).await {
        // test unary
        let mut req = bidirectional::RpcRequest::default();
        req.version = 1;
        req.service = bidirectional::RpcService::Test.into();
        req.func = bidirectional::RpcFunction::UnaryTest.into();
        let mut payload = bidirectional::MessageRequest::default();
        payload.text = String::from("Hello world");
        payload.content = "0123456789abcdefghijklmnopqrstuvwxyz".as_bytes().to_owned();
        req.payload = Some(bidirectional::rpc_request::Payload::Message(payload));
        let resp1 = MyQuickRpcClient::unary_request(&connection, req.clone()).await?;

        // test client stream
        let (resp2, mut send_stream1) = MyQuickRpcClient::client_stream_request(&connection).await?;
        for _ in 0..10 {
            MyQuickRpcClient::write_request(&mut send_stream1, req.clone()).await;
        }

        // test server stream
        let mut recv_stream1 = MyQuickRpcClient::server_stream_request(&connection, req.clone()).await?;
        for _ in 0..10 {
            let resp3 = MyQuickRpcClient::read_response(&mut recv_stream1).await;
        }

        // test bidirectional stream
        let (mut send_stream2, mut recv_stream2) = MyQuickRpcClient::bidirectional_stream_request(&connection).await?;
        for _ in 0..10 {
            MyQuickRpcClient::write_request(&mut send_stream2, req.clone()).await;
        }
        for _ in 0..10 {
            let resp4 = MyQuickRpcClient::read_response(&mut recv_stream2).await;
        }

        // wait for all connections on the endpoint to be cleanly shut down
        endpoint.wait_idle().await;
    }

    Ok(())
}



