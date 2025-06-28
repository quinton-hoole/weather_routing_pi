#!/bin/sh  -xe

#
# Build the mingw artifacts inside the Fedora container
#

set -xe

su -c "dnf install -y sudo dnf-plugins-core"
sudo dnf builddep -y mingw/fedora/opencpn-deps.spec
rm -rf build; mkdir build; cd build
cmake -DOCPN_BUILD_TEST=ON -DCMAKE_TOOLCHAIN_FILE=../mingw/fedora/toolchain.cmake ..
make -j12
make test
make package
