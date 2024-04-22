# CMakeList.txt : CMake project for CppClient, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CppClient")

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(PROTO_IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../Protos")

file(MAKE_DIRECTORY "${PROTO_BINARY_DIR}")

file(GLOB PROTO_FILES
    "${PROTO_IMPORT_DIRS}/*.proto"
)

add_library(proto-objects
    OBJECT "${PROTO_FILES}"
)

target_link_libraries(proto-objects
    gRPC::grpc++
    protobuf::libprotobuf
)

target_include_directories(proto-objects
    PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>"
)

protobuf_generate(
    TARGET proto-objects
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
)

protobuf_generate(
    TARGET proto-objects
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
)

add_executable(CppClient
    "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)

target_link_libraries(CppClient
    proto-objects
)