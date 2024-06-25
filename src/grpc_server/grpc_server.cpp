// cpp
#include <memory>
#include <string>

// grpc
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>

// spdlog
#include <spdlog/spdlog.h>

// project
#include "../grpc_proto/gen-cpp/bidirectional.grpc.pb.h"


// grpc namespace
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::ServerReaderWriter;
using grpc::Status;

// project namespace
using bidirectional::MessageRequest;
using bidirectional::MessageResponse;
using bidirectional::StreamRequest;
using bidirectional::StreamResponse;
using bidirectional::BidirectionalService;



class BidirectionalServiceImpl final : public BidirectionalService::Service {
	Status send_message(ServerContext *context, const MessageRequest *request, MessageResponse *response) override {
		context->set_compression_algorithm(GRPC_COMPRESS_NONE);

		response->set_version(request->version());
		response->set_text(request->text());
		response->set_content(request->content());

		if (0 == request->version() % 100000) {
			SPDLOG_INFO(
				"recv: version={}, text={}, content={}; "
				"send: version={}, text={}, content={}",
				request->version(), request->text(), request->content(),
				response->version(), response->text(), response->content()
			);
		}

		return Status::OK;
	}

	Status send_stream(ServerContext *context, ServerReaderWriter<StreamResponse, StreamRequest> *stream) override {
		context->set_compression_algorithm(GRPC_COMPRESS_NONE);

		StreamRequest request;
		while (stream->Read(&request)) {
			int32_t version = request.version();
			std::string text = request.text();
			std::string content = request.content();

			StreamResponse response;
			response.set_version(request.version());
			response.set_text(request.text());
			response.set_content(request.content());

			if (0 == request.version() % 100000) {
				SPDLOG_INFO(
					"recv: version={}, text={}, content={}; "
					"send: version={}, text={}, content={}",
					request.version(), request.text(), request.content(),
					response.version(), response.text(), response.content()
				);
			}

			if (!stream->Write(response)) {
				return Status(grpc::StatusCode::INTERNAL, "Failed to write response.");
			}
		}

		return Status::OK;
	}
};


int main() {
	std::string server_address("0.0.0.0:50051");
	BidirectionalServiceImpl service;

	ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);

	std::unique_ptr<Server> server(builder.BuildAndStart());
	server->Wait();

	return 0;
}