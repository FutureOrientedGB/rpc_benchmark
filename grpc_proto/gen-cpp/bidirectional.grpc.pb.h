// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: bidirectional.proto
#ifndef GRPC_bidirectional_2eproto__INCLUDED
#define GRPC_bidirectional_2eproto__INCLUDED

#include "bidirectional.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace bidirectional {

class BidirectionalService final {
 public:
  static constexpr char const* service_full_name() {
    return "bidirectional.BidirectionalService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status send_message(::grpc::ClientContext* context, const ::bidirectional::MessageRequest& request, ::bidirectional::MessageResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::bidirectional::MessageResponse>> Asyncsend_message(::grpc::ClientContext* context, const ::bidirectional::MessageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::bidirectional::MessageResponse>>(Asyncsend_messageRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::bidirectional::MessageResponse>> PrepareAsyncsend_message(::grpc::ClientContext* context, const ::bidirectional::MessageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::bidirectional::MessageResponse>>(PrepareAsyncsend_messageRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>> send_stream(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>>(send_streamRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>> Asyncsend_stream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>>(Asyncsend_streamRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>> PrepareAsyncsend_stream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>>(PrepareAsyncsend_streamRaw(context, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void send_message(::grpc::ClientContext* context, const ::bidirectional::MessageRequest* request, ::bidirectional::MessageResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void send_message(::grpc::ClientContext* context, const ::bidirectional::MessageRequest* request, ::bidirectional::MessageResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void send_stream(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::bidirectional::StreamRequest,::bidirectional::StreamResponse>* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::bidirectional::MessageResponse>* Asyncsend_messageRaw(::grpc::ClientContext* context, const ::bidirectional::MessageRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::bidirectional::MessageResponse>* PrepareAsyncsend_messageRaw(::grpc::ClientContext* context, const ::bidirectional::MessageRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientReaderWriterInterface< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>* send_streamRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>* Asyncsend_streamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>* PrepareAsyncsend_streamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status send_message(::grpc::ClientContext* context, const ::bidirectional::MessageRequest& request, ::bidirectional::MessageResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::bidirectional::MessageResponse>> Asyncsend_message(::grpc::ClientContext* context, const ::bidirectional::MessageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::bidirectional::MessageResponse>>(Asyncsend_messageRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::bidirectional::MessageResponse>> PrepareAsyncsend_message(::grpc::ClientContext* context, const ::bidirectional::MessageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::bidirectional::MessageResponse>>(PrepareAsyncsend_messageRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderWriter< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>> send_stream(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>>(send_streamRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>> Asyncsend_stream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>>(Asyncsend_streamRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>> PrepareAsyncsend_stream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>>(PrepareAsyncsend_streamRaw(context, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void send_message(::grpc::ClientContext* context, const ::bidirectional::MessageRequest* request, ::bidirectional::MessageResponse* response, std::function<void(::grpc::Status)>) override;
      void send_message(::grpc::ClientContext* context, const ::bidirectional::MessageRequest* request, ::bidirectional::MessageResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
      void send_stream(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::bidirectional::StreamRequest,::bidirectional::StreamResponse>* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::bidirectional::MessageResponse>* Asyncsend_messageRaw(::grpc::ClientContext* context, const ::bidirectional::MessageRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::bidirectional::MessageResponse>* PrepareAsyncsend_messageRaw(::grpc::ClientContext* context, const ::bidirectional::MessageRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientReaderWriter< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>* send_streamRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>* Asyncsend_streamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>* PrepareAsyncsend_streamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_send_message_;
    const ::grpc::internal::RpcMethod rpcmethod_send_stream_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status send_message(::grpc::ServerContext* context, const ::bidirectional::MessageRequest* request, ::bidirectional::MessageResponse* response);
    virtual ::grpc::Status send_stream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::bidirectional::StreamResponse, ::bidirectional::StreamRequest>* stream);
  };
  template <class BaseClass>
  class WithAsyncMethod_send_message : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_send_message() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_send_message() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status send_message(::grpc::ServerContext* /*context*/, const ::bidirectional::MessageRequest* /*request*/, ::bidirectional::MessageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestsend_message(::grpc::ServerContext* context, ::bidirectional::MessageRequest* request, ::grpc::ServerAsyncResponseWriter< ::bidirectional::MessageResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_send_stream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_send_stream() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_send_stream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status send_stream(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::bidirectional::StreamResponse, ::bidirectional::StreamRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestsend_stream(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::bidirectional::StreamResponse, ::bidirectional::StreamRequest>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(1, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_send_message<WithAsyncMethod_send_stream<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_send_message : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_send_message() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::bidirectional::MessageRequest, ::bidirectional::MessageResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::bidirectional::MessageRequest* request, ::bidirectional::MessageResponse* response) { return this->send_message(context, request, response); }));}
    void SetMessageAllocatorFor_send_message(
        ::grpc::MessageAllocator< ::bidirectional::MessageRequest, ::bidirectional::MessageResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::bidirectional::MessageRequest, ::bidirectional::MessageResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_send_message() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status send_message(::grpc::ServerContext* /*context*/, const ::bidirectional::MessageRequest* /*request*/, ::bidirectional::MessageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* send_message(
      ::grpc::CallbackServerContext* /*context*/, const ::bidirectional::MessageRequest* /*request*/, ::bidirectional::MessageResponse* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_send_stream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_send_stream() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackBidiHandler< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>(
            [this](
                   ::grpc::CallbackServerContext* context) { return this->send_stream(context); }));
    }
    ~WithCallbackMethod_send_stream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status send_stream(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::bidirectional::StreamResponse, ::bidirectional::StreamRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerBidiReactor< ::bidirectional::StreamRequest, ::bidirectional::StreamResponse>* send_stream(
      ::grpc::CallbackServerContext* /*context*/)
      { return nullptr; }
  };
  typedef WithCallbackMethod_send_message<WithCallbackMethod_send_stream<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_send_message : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_send_message() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_send_message() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status send_message(::grpc::ServerContext* /*context*/, const ::bidirectional::MessageRequest* /*request*/, ::bidirectional::MessageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_send_stream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_send_stream() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_send_stream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status send_stream(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::bidirectional::StreamResponse, ::bidirectional::StreamRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_send_message : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_send_message() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_send_message() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status send_message(::grpc::ServerContext* /*context*/, const ::bidirectional::MessageRequest* /*request*/, ::bidirectional::MessageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestsend_message(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_send_stream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_send_stream() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_send_stream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status send_stream(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::bidirectional::StreamResponse, ::bidirectional::StreamRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestsend_stream(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(1, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_send_message : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_send_message() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->send_message(context, request, response); }));
    }
    ~WithRawCallbackMethod_send_message() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status send_message(::grpc::ServerContext* /*context*/, const ::bidirectional::MessageRequest* /*request*/, ::bidirectional::MessageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* send_message(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_send_stream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_send_stream() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackBidiHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context) { return this->send_stream(context); }));
    }
    ~WithRawCallbackMethod_send_stream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status send_stream(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::bidirectional::StreamResponse, ::bidirectional::StreamRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* send_stream(
      ::grpc::CallbackServerContext* /*context*/)
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_send_message : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_send_message() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::bidirectional::MessageRequest, ::bidirectional::MessageResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::bidirectional::MessageRequest, ::bidirectional::MessageResponse>* streamer) {
                       return this->Streamedsend_message(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_send_message() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status send_message(::grpc::ServerContext* /*context*/, const ::bidirectional::MessageRequest* /*request*/, ::bidirectional::MessageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedsend_message(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::bidirectional::MessageRequest,::bidirectional::MessageResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_send_message<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_send_message<Service > StreamedService;
};

}  // namespace bidirectional


#endif  // GRPC_bidirectional_2eproto__INCLUDED
