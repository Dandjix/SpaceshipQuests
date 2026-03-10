cmake -B build -DBUILD_TESTS=OFF
cmake --build build
cmake --install build --prefix ~/.local