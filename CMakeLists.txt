cmake_minimum_required(VERSION 3.5)
# set compiler path
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(repo_c)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# gdb debug
SET(CMAKE_BUILD_TYPE "Debug")  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  

add_subdirectory(debug)
add_subdirectory(apps/hello_world)
