cmake_minimum_required(VERSION 3.20)


set(PROJECT_NAME thrift_client)


project(${PROJECT_NAME})


# find pkgconf
find_package(PkgConfig REQUIRED)

# find zlib
find_package(ZLIB REQUIRED)

# find fmt
find_package(fmt CONFIG REQUIRED)

# find spdlog
find_package(spdlog CONFIG REQUIRED)

# find openssl
find_package(openssl CONFIG REQUIRED)

# find libevent
find_package(Libevent CONFIG REQUIRED)

# find thrift
find_package(thrift CONFIG REQUIRED)

# find cli11
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
