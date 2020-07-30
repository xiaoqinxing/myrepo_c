# TODO: Set the project name
project(datastruct_test)
message("====================================================")
message(STATUS "build app: " ${PROJECT_NAME})

# find all source file in src
aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCES)
message(STATUS "SRC FILES: " ${SOURCES})

include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/inc)
message(STATUS "INC FILES: " ${PROJECT_SOURCE_DIR}/inc)

# set output file path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
message(STATUS "BUILD EXE: " ${EXECUTABLE_OUTPUT_PATH} "/" ${PROJECT_NAME} ".exe")

# Add an executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    libdebug
    libcommon
)