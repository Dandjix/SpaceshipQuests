#!/bin/bash
# Uninstall previous version
if [ -f build/install_manifest.txt ]; then
    xargs rm -f < build/install_manifest.txt
fi

cmake -B build -DBUILD_TESTS=OFF
cmake --build build
cmake --install build --prefix ~/.local