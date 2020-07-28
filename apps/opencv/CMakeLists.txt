# TODO: Set the project name
project(opencv_sample)
message(STATUS "build app: " ${PROJECT_NAME})

find_package( OpenCV REQUIRED )

# TODO: set source file (c/cpp)
set(SOURCES 
    ${PROJECT_SOURCE_DIR}/src/opencv_sample.c
)
message(STATUS "SRC FILES: " ${SOURCES})

# set output file path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
message(STATUS "BUILD EXE: " ${EXECUTABLE_OUTPUT_PATH} "/" ${PROJECT_NAME})

# Add an executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    libdebug
    ${OpenCV_LIBS}
)

if(OpenCV_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARY})
else(OpenCV_FOUND)
    message(FATAL_ERROR ”OpenCV library not found”)
endif(OpenCV_FOUND)