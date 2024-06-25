// c
#include <stdint.h>

// thrift
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

// spdlog
#include <spdlog/spdlog.h>

// cli11
#include <CLI/CLI.hpp>

// project
#include "../thrift_idl/gen-cpp/BidirectionalService.h"

// thrift namespace
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

// project namespace
using namespace bidirectional;



void test_48(BidirectionalServiceClient &client) {
    int32_t version = 0;

    MessageRequest request;
    request.text = "hello world";
    request.content = "0123456789abcdefghijklmnopqrstuvwxyz";

    while (true) {
        request.version = version;

        MessageResponse response;
        client.send_message(response, request);

        if (0 == version % 100000) {
            SPDLOG_INFO(
                "send: version={}, text={}, content={}; "
                "recv: version={}, text={}, content={}",
                request.version, request.text, request.content,
                response.version, response.text, response.content
            );
        }

        version = (version + 1) % INT32_MAX;
    }
}


void test_1400(BidirectionalServiceClient &client) {
    int32_t version = 0;

    MessageRequest request;
    request.text = "hello world";
    request.content = "0123456789abcdefghijklmnopqrstuvwxyz"
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
        "0123456789abcdefghijklmnopqrstuvwxyz";

    while (true) {
        request.version = version;

        MessageResponse response;
        client.send_message(response, request);

        if (0 == version % 100000) {
            SPDLOG_INFO(
                "send: version={}, text={}, content={}; "
                "recv: version={}, text={}, content={}",
                request.version, request.text, request.content,
                response.version, response.text, response.content
            );
        }

        version = (version + 1) % INT32_MAX;
    }
}


enum class FuncType {
    Size48,
    Size1400,
};



int main(int argc, char **argv) {
    CLI::App app{ "test thrift client" };
    argv = app.ensure_utf8(argv);

    std::string host = "localhost";
    app.add_option("-i,--ip", host, "server host");

    uint32_t port = 9090;
    app.add_option("-p,--port", port, "server port");

    FuncType func = FuncType::Size48;
    app.add_option("-f,--func", func, "server func");

    CLI11_PARSE(app, argc, argv);


    std::shared_ptr<TTransport> socket = std::make_shared<TSocket>(host, port);
    std::shared_ptr<TTransport> transport = std::make_shared<TBufferedTransport>(socket);
    std::shared_ptr<TProtocol> protocol = std::make_shared<TBinaryProtocol>(transport);
    BidirectionalServiceClient client(protocol);

    try {
        transport->open();

        switch (func)
        {
        case FuncType::Size48:
            test_48(client);
            break;

        case FuncType::Size1400:
            test_1400(client);
            break;

        default:
            break;
        }


        transport->close();
    }
    catch (TException& tx) {
        SPDLOG_ERROR("thrift exception, what: {}", tx.what());
    }

    return 0;
}

