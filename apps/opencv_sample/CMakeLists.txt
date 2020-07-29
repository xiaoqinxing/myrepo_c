# TODO: Set the project name
project(opencv_sample)
message("====================================================")
message(STATUS "build app: " ${PROJECT_NAME})
 
# TODO: set source file (c/cpp)
set(SOURCES 
    ${PROJECT_SOURCE_DIR}/src/opencv_sample.cpp
)
message(STATUS "SRC FILES: " ${SOURCES})

# set output file path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
message(STATUS "BUILD EXE: " ${EXECUTABLE_OUTPUT_PATH} "/" ${PROJECT_NAME})

# Add an executable
add_executable(${PROJECT_NAME} ${SOURCES})

# set(OpenCV_DIR C:\\install_pack\\opencv\\build\\x64\\vc14\\lib) 
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    # set(OpenCV_DIR C:\\opencv\\opencv\\build\\x64\\vc15\\lib)
    set(OpenCV_DIR C:\\opencv\\opencv\\sources\\build\\install\\x64\\mingw\\lib)
endif()

find_package( OpenCV REQUIRED )
if(OpenCV_FOUND)
    message(STATUS "OpenCV library has found")
    message(STATUS "OpenCV_INCLUDE_DIR: " ${OpenCV_INCLUDE_DIRS})
    message(STATUS "OpenCV_LIBRARY: " ${OpenCV_LIBS})
    target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
else(OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV library not found")
endif(OpenCV_FOUND)