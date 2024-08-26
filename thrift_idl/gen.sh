#!/bin/bash

./../vcpkg/installed/x64-windows-static/tools/thrift/thrift                    \
    --gen cpp                                                                  \
    bidirectional.thrift
