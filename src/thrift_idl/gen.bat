@echo off

..\vcpkg\installed\x64-windows-static\tools\thrift\thrift.exe                  ^
    --gen cpp                                                                  ^
    bidirectional.thrift
