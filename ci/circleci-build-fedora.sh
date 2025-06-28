#!/bin/sh  -xe

#
# Build the mingw artifacts inside the Fedora container
#
set -xe

su -c "dnf install -y sudo dnf-plugins-core"
sudo dnf builddep  -y ci/opencpn-fedora.spec
rm -rf build; mkdir build; cd build
cmake -DOCPN_BUILD_TEST=ON ..
make -j12
make test
make package
