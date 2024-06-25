// cpp
#include <memory>
#include <string>

// grpc
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>

// fmt
#include <fmt/format.h>

// spdlog
#include <spdlog/spdlog.h>

// cli11
#include <CLI/CLI.hpp>

// project
#include "../grpc_proto/gen-cpp/bidirectional.grpc.pb.h"


// grpc namespace
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReaderWriter;

// project namespace
using bidirectional::MessageRequest;
using bidirectional::MessageResponse;
using bidirectional::StreamRequest;
using bidirectional::StreamResponse;
using bidirectional::BidirectionalService;



class BidirectionalClient {
public:
	BidirectionalClient(std::shared_ptr<Channel> channel)
		: m_stub(BidirectionalService::NewStub(channel)) {}

	MessageResponse send_message(const MessageRequest &request) {
		ClientContext context;
		context.set_compression_algorithm(GRPC_COMPRESS_NONE);

		MessageResponse response;
		Status status = m_stub->send_message(&context, request, &response);

		if (status.ok()) {
			return response;
		}
		else {
			SPDLOG_ERROR("grpc exception, error: {}, message: {}, details: {}", (int)status.error_code(), status.error_message(), status.error_details());
			return MessageResponse();
		}
	}


	void send_stream(StreamRequest &request) {
		int32_t version = 0;

		ClientContext context;
		context.set_compression_algorithm(GRPC_COMPRESS_NONE);
		std::shared_ptr<ClientReaderWriter<StreamRequest, StreamResponse>> stream(m_stub->send_stream(&context));

		stream->Write(request);

		StreamResponse response;
		while (stream->Read(&response)) {
			if (0 == request.version() % 100000) {
				SPDLOG_INFO(
					"recv: version={}, text={}, content={}; "
					"send: version={}, text={}, content={}",
					request.version(), request.text(), request.content(),
					response.version(), response.text(), response.content()
				);
			}

			version = (version + 1) % INT32_MAX;
			request.set_version(version);

			stream->Write(request);
		}


		stream->WritesDone();
		Status status = stream->Finish();
	}

private:
	std::unique_ptr<BidirectionalService::Stub> m_stub;
};


void test_unary(BidirectionalClient &client) {
	int32_t version = 0;

	MessageRequest request;
	request.set_text("hello world");
	request.set_content("0123456789abcdefghijklmnopqrstuvwxyz");

	while (true) {
		request.set_version(version);

		MessageResponse response = client.send_message(request);

		if (0 == version % 100000) {
			SPDLOG_INFO(
				"send: version={}, text={}, content={}; "
				"recv: version={}, text={}, content={}",
				request.version(), request.text(), request.content(),
				response.version(), response.text(), response.content()
			);
		}

		version = (version + 1) % INT32_MAX;
	}
}


void test_stream_48(BidirectionalClient &client) {
	StreamRequest request;
	request.set_version(0);
	request.set_text("hello world");
	request.set_content("0123456789abcdefghijklmnopqrstuvwxyz");

	client.send_stream(request);
}


void test_stream_1400(BidirectionalClient &client) {
	StreamRequest request;
	request.set_version(0);
	request.set_text("hello world");
	request.set_content(
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789abcdefghijklmnopqrstuvwxyz"
	);

	client.send_stream(request);
}


enum class FuncType {
	Unary,
	Stream48,
	Stream1400,
};


int main(int argc, char **argv) {
	CLI::App app{ "test grpc client" };
	argv = app.ensure_utf8(argv);

	std::string host = "localhost";
	app.add_option("-i,--ip", host, "server host");

	uint32_t port = 50051;
	app.add_option("-p,--port", port, "server port");

	FuncType func = FuncType::Unary;
	app.add_option("-f,--func", func, "server func");

	CLI11_PARSE(app, argc, argv);


	grpc::ChannelArguments channel_args;
	channel_args.SetInt(GRPC_ARG_HTTP2_BDP_PROBE, 0);  // 禁用带宽延迟积探测
	channel_args.SetInt(GRPC_ARG_HTTP2_MIN_SENT_PING_INTERVAL_WITHOUT_DATA_MS, 300 * 1000);  // 无数据时最小发送 ping 的间隔
	channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 10 * 1000);  // 保持连接的空闲时间
	channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 5 * 1000);  // 保持连接的超时时间
	channel_args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);  // 无活动时保持连接
	channel_args.SetInt(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0);  // 无数据时发送的最大 ping 数量
	BidirectionalClient client(grpc::CreateCustomChannel(fmt::format("{}:{}", host, port), grpc::InsecureChannelCredentials(), channel_args));

	switch (func)
	{
	case FuncType::Unary:
		test_unary(client);
		break;

	case FuncType::Stream48:
		test_stream_48(client);
		break;

	case FuncType::Stream1400:
		test_stream_1400(client);
		break;

	default:
		break;
	}


	return 0;
}