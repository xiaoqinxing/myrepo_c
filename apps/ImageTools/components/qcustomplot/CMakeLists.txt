cmake_minimum_required(VERSION 3.5)

project(qcustomplot)
message("====================================================")
message(STATUS "build so: " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(${PROJECT_SOURCE_DIR} SOURCES)
message(STATUS "SRC FILES: " ${SOURCES})

include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR})

add_library( ${PROJECT_NAME} ${SOURCES})
message(STATUS ${PROJECT_NAME} "build finished")

# find QT
find_package(Qt5 COMPONENTS Widgets Core Gui PrintSupport REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::PrintSupport)
