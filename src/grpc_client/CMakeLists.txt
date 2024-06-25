cmake_minimum_required(VERSION 3.20)


set(PROJECT_NAME grpc_client)


project(${PROJECT_NAME})


# find pkgconf
set(PKG_CONFIG_EXECUTABLE $ENV{PKGCONF_EXE_PATH})
set(PKG_CONFIG_PATH $ENV{PKGCONF_CFG_PATH})
find_package(PkgConfig REQUIRED)

# find zlib
set(ZLIB_ROOT $ENV{VCPKG_LIB_PATH})
set(ZLIB_INCLUDE_DIR $ENV{VCPKG_INCLUDE_PATH})
find_package(ZLIB REQUIRED)

# find fmt
set(fmt_DIR $ENV{FMT_CMAKE_PATH})
find_package(fmt CONFIG REQUIRED)

# find spdlog
set(spdlog_DIR $ENV{SPDLOG_CMAKE_PATH})
find_package(spdlog CONFIG REQUIRED)

# find protobuf
set(protobuf_DIR $ENV{PROTOBUF_CMAKE_PATH})
find_package(protobuf CONFIG REQUIRED)

# find protobuf
set(upb_DIR $ENV{UPB_CMAKE_PATH})
find_package(upb CONFIG REQUIRED)

# find absl
set(absl_DIR $ENV{ABSL_CMAKE_PATH})
find_package(absl CONFIG REQUIRED)

# find c-ares
set(c-ares_DIR $ENV{C_ARES_CMAKE_PATH})
find_package(c-ares CONFIG REQUIRED)

# find re2
set(re2_DIR $ENV{RE2_CMAKE_PATH})
find_package(re2 CONFIG REQUIRED)

# find grpc
set(gRPC_DIR $ENV{GRPC_CMAKE_PATH})
find_package(gRPC CONFIG REQUIRED)

# find cli11
set(CLI11_DIR $ENV{CLI11_CMAKE_PATH})
find_package(CLI11 CONFIG REQUIRED)


# Visual Stuido - Properify - Linker - General - Additional Library Directories
link_directories(
        $ENV{VCPKG_LIB_PATH}
)


# Defines
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
ADD_DEFINITIONS(-DVC_EXTRALEAN)
ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)



# Classify filters
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


# Visual Studio - Properity - C/C++ - General - Additional Include Directories
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $ENV{VCPKG_INCLUDE_PATH}
)


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
