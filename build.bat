mkdir build
cd build
rm -r *
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. -G "MinGW Makefiles"
cmake --build .