// std
use std::{error::Error, str::FromStr};

// anyhow
use anyhow::Result;

use quick_rpc_service::QuickRpcService;
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

// my service
pub mod quick_rpc_service;
pub mod my_rpc_service;



#[derive(StructOpt)]
struct CommandLine {
    #[structopt(long, default_value = "[::1]")]
    host: String,

    #[structopt(long, default_value = "4433")]
    port: u16,

    #[structopt(long, default_value = "500")]
    min_ms_per_loop: u64,

    #[structopt(long, default_value = "INFO")]
    log_level: String,
}


#[tokio::main]
async fn main() -> Result<(), Box<dyn Error + Send + Sync + 'static>> {
    // parse command line arguments
    let cli = CommandLine::from_clap(
        &CommandLine::clap()
            .name("quic_pb3_server")
            .version("2024.7.2.1")
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

    let mut complete_flag = false;
    my_rpc_service::MyRpcService::run_until_complete(
        cli.host,
        cli.port,
        &complete_flag,
        cli.min_ms_per_loop,
        |incoming_connection| {
            tokio::spawn(async move {
                my_rpc_service::MyRpcService::on_connect(incoming_connection).await;
            });
        },
    )
    .await;
    complete_flag = true;

    Ok(())
}
