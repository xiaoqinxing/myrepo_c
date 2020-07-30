mkdir build
cd build
rm -r *
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. -G "MinGW Makefiles"
REM cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. -G "MinGW Makefiles"
REM cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. -G "MinGW Makefiles"
REM cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. -G "MinGW Makefiles"
cmake --build . --target all
cd ../