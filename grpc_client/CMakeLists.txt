cmake_minimum_required(VERSION 3.20)


set(PROJECT_NAME grpc_client)


project(${PROJECT_NAME})


# find zlib
find_package(ZLIB REQUIRED)

# find fmt
find_package(fmt CONFIG REQUIRED)

# find spdlog
find_package(spdlog CONFIG REQUIRED)

# find protobuf
find_package(protobuf CONFIG REQUIRED)

# find upb
find_package(upb CONFIG REQUIRED)

# find absl
find_package(absl CONFIG REQUIRED)

# find c-ares
find_package(c-ares CONFIG REQUIRED)

# find re2
find_package(re2 CONFIG REQUIRED)

# find grpc
find_package(gRPC CONFIG REQUIRED)

# find cli11
find_package(CLI11 CONFIG REQUIRED)


# defines
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
ADD_DEFINITIONS(-DVC_EXTRALEAN)
ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)



# classify filters
FILE(GLOB_RECURSE HEADER_FILES
        "*.hpp"
        "../grpc_proto/gen-cpp/*.h"
)
FILE(GLOB_RECURSE SOURCE_FILES
        "*.cpp"
        "../grpc_proto/gen-cpp/*.cc"
)
SOURCE_GROUP("Header Files" FILES ${HEADER_FILES})
SOURCE_GROUP("Source Files" FILES ${SRC_FILES})


# executable
add_executable(${PROJECT_NAME}
        WIN32
        ${HEADER_FILES}
        ${SOURCE_FILES}
)


# output dir
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY $ENV{OUTPUT_EXE_DIR}
)


# Visual Studio - Properity - Linker - System - SubSystem > Console
if(MSVC)
set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
)
endif(MSVC)


# Visual Studio - Properity - C/C++ - Code Generation - Rutime Library > /MT
if(MSVC)
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)
endif(MSVC)


# Visual Studio - Properity - C/C++ - General - Additional Include Libraries
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        # spdlog
        spdlog::spdlog
        # protobuf
        protobuf::libprotobuf
        # grpc
        gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts
        # cli11
        CLI11::CLI11
)
