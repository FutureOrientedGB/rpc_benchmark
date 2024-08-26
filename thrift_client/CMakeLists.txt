cmake_minimum_required(VERSION 3.20)


set(PROJECT_NAME thrift_client)


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

# find openssl
set(openssl_DIR $ENV{OPENSSL_CMAKE_PATH})
find_package(openssl CONFIG REQUIRED)

# find libevent
set(Libevent_DIR $ENV{LIBEVENT_CMAKE_PATH})
find_package(Libevent CONFIG REQUIRED)

# find thrift
set(thrift_DIR $ENV{THRIFT_CMAKE_PATH})
find_package(thrift CONFIG REQUIRED)

# find cli11
set(CLI11_DIR $ENV{CLI11_CMAKE_PATH})
find_package(CLI11 CONFIG REQUIRED)


# Visual Stuido - Properify - Linker - General - Additional Library Directories
link_directories(
        $ENV{VCPKG_LIB_PATH}
)


# defines
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
ADD_DEFINITIONS(-DVC_EXTRALEAN)
ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)



# classify filters
FILE(GLOB_RECURSE HEADER_FILES
        "*.hpp"
        "../thrift_idl/gen-cpp/bidirectional_types.h"
        "../thrift_idl/gen-cpp/BidirectionalService.h"
)
FILE(GLOB_RECURSE SOURCE_FILES
        "*.cpp"
        "../thrift_idl/gen-cpp/bidirectional_types.cpp"
        "../thrift_idl/gen-cpp/BidirectionalService.cpp"
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
        # zlib
        ZLIB::ZLIB
        # spdlog
        spdlog::spdlog
        # openssl
        OpenSSL::SSL
        OpenSSL::Crypto
        # libevent
        libevent::core
        libevent::extra
        # thrift
        thrift::thrift
        # cli11
        CLI11::CLI11
)
