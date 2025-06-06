#!/usr/bin/env bash


# Build the  MacOS artifacts


# Copyright (c) 2021 Alec Leamas
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

set -x

# Load local environment if it exists i. e., this is a local build
if [ -f ~/.config/local-build.rc ]; then source ~/.config/local-build.rc; fi

git submodule update --init

# If applicable,  restore /usr/local from cache.
if [[ -n "$CI" && -f /tmp/local.cache.tar ]]; then
  sudo rm -rf /usr/local/*
  sudo tar -C /usr -xf /tmp/local.cache.tar
fi

# Set up build directory
rm -rf build  && mkdir build

# Create a log file.
exec > >(tee build/build.log) 2>&1

export MACOSX_DEPLOYMENT_TARGET=10.10

# Return latest version of $1, optionally using option $2
pkg_version() { brew list --versions $2 $1 | tail -1 | awk '{print $2}'; }

#
# Check if the cache is with us. If not, re-install brew.
brew list --versions libexif || brew update-reset

# Install packaged dependencies
here=$(cd "$(dirname "$0")"; pwd)
for pkg in $(sed '/#/d' < $here/../build-deps/macos-deps);  do
    brew list --versions $pkg || brew install $pkg || brew install $pkg || :
    brew link --overwrite $pkg || brew install $pkg
done

#Install python virtual environment
/usr/bin/python3 -m venv $HOME/cs-venv

#Install prebuilt dependencies
wget -q https://dl.cloudsmith.io/public/nohal/opencpn-plugins/raw/files/macos_deps_universal.tar.xz \
     -O /tmp/macos_deps_universal.tar.xz
sudo tar -C /usr/local -xJf /tmp/macos_deps_universal.tar.xz

export OPENSSL_ROOT_DIR='/usr/local'

# Build and package
cd build
cmake \
  "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE:-Release}" \
  -DCMAKE_INSTALL_PREFIX= \
  -DCMAKE_OSX_DEPLOYMENT_TARGET=${MACOSX_DEPLOYMENT_TARGET} \
  -DOCPN_TARGET_TUPLE="darwin-wx32;10;universal" \
  -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
  ..

if [[ -z "$CI" ]]; then
    echo '$CI not found in environment, assuming local setup'
    echo "Complete build using 'cd build; make tarball' or so."
    exit 0
fi

# non-reproducible error on first invocation, seemingly tarball-conf-stamp
# is not created as required.
make package || make package

# Create the cached /usr/local archive
if [ -n "$CI"  ]; then
  tar -C /usr -cf /tmp/local.cache.tar  local
fi
