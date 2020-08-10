cmake_minimum_required(VERSION 3.5)

project(ImageTools LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

# find all source file in src
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCES)
message(STATUS "SRC FILES: " ${SOURCES})

include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR})

#查找当前文件夹中所有的ui文件
set(UI_FILES
    mainwindow.ui
    images.ui
)
#FILE(GLOB UI_FILES "*.ui")

#通过Ui文件生成对应的头文件，一定要添加
#qt5_wrap_ui(UI_HEADERS ${UI_FILES})

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

if(ANDROID)
  add_library( ${PROJECT_NAME} ${SOURCES} ${UI_FILES})
else()
  add_executable( ${PROJECT_NAME} ${SOURCES} ${UI_FILES})
endif()


target_link_libraries(ImageTools PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
