cmake_minimum_required(VERSION 3.5)
# set compiler path
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# get git version
set(COMMIT_HASH "")
set(BRANCH_NAME "")
find_package(Git QUIET)
if(GIT_FOUND)
execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%H
    OUTPUT_VARIABLE COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} symbolic-ref --short -q HEAD
    OUTPUT_VARIABLE BRANCH_NAME
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
endif()
string(SUBSTRING ${COMMIT_HASH} 0 8 COMMIT_HASH)
string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%dT%H:%M:%S")
message(STATUS "Git version is ${BRANCH_NAME}:${COMMIT_HASH}")
message(STATUS "Build time: ${BUILD_TIMESTAMP}")
add_definitions(-DCOMMIT_HASH=\"${COMMIT_HASH}\")
add_definitions(-DBRANCH_NAME=\"${BRANCH_NAME}\")
add_definitions(-DBUILD_TIMESTAMP=\"${BUILD_TIMESTAMP}\")

project(repo_c)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# gdb debug
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb -lpthread")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -lpthread")  

add_subdirectory(debug)
add_subdirectory(apps/hello_world)
add_subdirectory(apps/datastruct_test)
add_subdirectory(apps/opencv_sample)
add_subdirectory(common)
