# TODO: Set the project name
project(hello_world)
message("====================================================")
message(STATUS "build app: " ${PROJECT_NAME})
# add version
# configure_file(config.h.in config.h)

# TODO: set source file (c/cpp)
set(SOURCES 
    ${PROJECT_SOURCE_DIR}/src/hello_world.c
)
message(STATUS "SRC FILES: " ${SOURCES})

# set output file path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
message(STATUS "BUILD EXE: " ${EXECUTABLE_OUTPUT_PATH} "/" ${PROJECT_NAME})

# Add an executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    libdebug
)