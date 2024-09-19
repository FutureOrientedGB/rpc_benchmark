import platform
import subprocess
import sys


if __name__ == '__main__':
    sys.path.insert(1, '../')
    import build
    triplet = build.default_triplet()

    protoc = 'protoc'
    grpc_cpp_plugin = 'grpc_cpp_plugin'
    if platform.system() == 'Windows':
        protoc += '.exe'
        grpc_cpp_plugin += '.exe'

    subprocess.run(args=[
        f'../build/{triplet}/vcpkg_installed/{triplet}/tools/protobuf/{protoc}',
        '--cpp_out=gen-cpp/',
        '--grpc_out=gen-cpp/',
        '--proto_path=.',
        f'--plugin=protoc-gen-grpc=../build/{triplet}/vcpkg_installed/{triplet}/tools/grpc/{grpc_cpp_plugin}',
        'bidirectional.proto'
    ])
