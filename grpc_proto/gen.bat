@echo off

..\vcpkg\installed\x64-windows-static\tools\protobuf\protoc.exe                                              ^
    --cpp_out=gen-cpp/                                                                                       ^
    --grpc_out=gen-cpp/                                                                                      ^
    --proto_path=.                                                                                           ^
    --plugin=protoc-gen-grpc="..\vcpkg\installed\x64-windows-static\tools\grpc\grpc_cpp_plugin.exe"          ^
    bidirectional.proto
