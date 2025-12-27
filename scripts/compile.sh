cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
make -j $(nproc) -C build