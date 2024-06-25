// thrift
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

// spdlog
#include <spdlog/spdlog.h>

// project
#include "BidirectionalService.h"


// thrift namespace
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

// project namespace
using namespace bidirectional;



class BidirectionalServiceHandler : virtual public BidirectionalServiceIf {
public:
	BidirectionalServiceHandler() {
		// Your initialization goes here
	}

	void send_message(MessageResponse &response, const MessageRequest &request) {
		// Your implementation goes here
		response.version = request.version;
		response.text = request.text;
		response.content = request.content;

		if (0 == request.version % 100000) {
			SPDLOG_INFO(
				"recv: version={}, text={}, content={}; "
				"send: version={}, text={}, content={}",
				request.version, request.text, request.content,
				response.version, response.text, response.content
			);
		}
	}

	void send_stream(StreamResponse &response, const StreamRequest &request) {
		// Your implementation goes here
		response.version = request.version;
		response.text = request.text;
		response.content = request.content;
	}

};

int main(int argc, char **argv) {
	int port = 9090;
	std::shared_ptr<BidirectionalServiceHandler> handler(new BidirectionalServiceHandler());
	std::shared_ptr<TProcessor> processor(new BidirectionalServiceProcessor(handler));
	std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	server.serve();

	return 0;
}

