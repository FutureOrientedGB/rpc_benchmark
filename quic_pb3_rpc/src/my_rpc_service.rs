
// bidirectional service
use crate::QuickRpcService;
use crate::bidirectional;



pub struct MyRpcService {}

impl QuickRpcService<bidirectional::RpcRequest, bidirectional::RpcResponse> for MyRpcService {
    async fn on_service(
        send_stream: &mut quinn::SendStream,
        recv_stream: &mut quinn::RecvStream,
        request: bidirectional::RpcRequest,
    ) {
        match request.service() {
            bidirectional::RpcService::Test => {
                Self::on_method(send_stream, recv_stream, request).await;
            }
        }
    }

    async fn on_method(
        send_stream: &mut quinn::SendStream,
        recv_stream: &mut quinn::RecvStream,
        request: bidirectional::RpcRequest,
    ) {
        match request.func() {
            bidirectional::RpcFunction::UnaryTest => {
                Self::unary_test(send_stream, request).await;
            }
            bidirectional::RpcFunction::ClientStreamTest => {
                Self::client_stream_test(send_stream, recv_stream, request).await;
            }
            bidirectional::RpcFunction::ServerStreamTest => {
                Self::server_stream_test(send_stream, recv_stream, request).await;
            }
            bidirectional::RpcFunction::BidirectionalStreamTest => {
                Self::bidirectional_stream_test(send_stream, recv_stream, request).await;
            }
        }
    }
}

impl MyRpcService {
    pub fn accept_incoming_connections(incoming_connection: quinn::Incoming) {
        tokio::spawn(async move {
            Self::on_connect(incoming_connection).await;
        });
    }

    async fn unary_test(send_stream: &mut quinn::SendStream, request: bidirectional::RpcRequest) {}

    async fn client_stream_test(
        send_stream: &mut quinn::SendStream,
        recv_stream: &mut quinn::RecvStream,
        request: bidirectional::RpcRequest,
    ) {
    }

    async fn server_stream_test(
        send_stream: &mut quinn::SendStream,
        recv_stream: &mut quinn::RecvStream,
        request: bidirectional::RpcRequest,
    ) {
    }

    async fn bidirectional_stream_test(
        send_stream: &mut quinn::SendStream,
        recv_stream: &mut quinn::RecvStream,
        request: bidirectional::RpcRequest,
    ) {
    }
}
