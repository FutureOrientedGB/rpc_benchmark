namespace cpp bidirectional


struct MessageRequest {
    1: i32 version
    2: string text
    3: binary content
}

struct MessageResponse {
    1: i32 version
    2: string text
    3: binary content
}


struct StreamRequest {
    1: i32 version
    2: string text
    3: binary content
}

struct StreamResponse {
    1: i32 version
    2: string text
    3: binary content
}



service BidirectionalService {
    MessageResponse send_message(1: MessageRequest request)
    StreamResponse send_stream(1: StreamRequest request)
}

