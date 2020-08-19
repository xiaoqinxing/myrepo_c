cmake_minimum_required(VERSION 3.5)

project(ImageTools LANGUAGES CXX)
message("====================================================")
message(STATUS "build app: " ${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VLCQt_INCLUDE
    "C:/Program Files (x86)/VLC-Qt/include/VLCQtWidgets"
)

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
aux_source_directory(${PROJECT_SOURCE_DIR}/imageeditor SOURCES)
aux_source_directory(${PROJECT_SOURCE_DIR}/imageproc SOURCES)
aux_source_directory(${PROJECT_SOURCE_DIR}/mainwindow SOURCES)
aux_source_directory(${PROJECT_SOURCE_DIR}/videoplayer SOURCES)
message(STATUS "SRC FILES: " ${SOURCES})

include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/imageeditor)
include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/imageproc)
include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/mainwindow)
include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/videoplayer)
include_directories(${PROJECT_NAME} ${VLCQt_INCLUDE})
#查找当前文件夹中所有的ui文件
set(UI_FILES
    mainwindow/mainwindow.ui
    imageeditor/imageeditor.ui
    imageeditor/staticsview.ui
    imageeditor/histgramview.ui
    videoplayer/rtspconfigview.ui
    videoplayer/videoplayer.ui
    videoplayer/SimplePlayer.ui
    videoplayer/EqualizerDialog.ui
)
#FILE(GLOB UI_FILES "*.ui")

#通过Ui文件生成对应的头文件，一定要添加
#qt5_wrap_ui(UI_HEADERS ${UI_FILES})

#添加资源文件
set( QRCS resource.qrc )



if(ANDROID)
  add_library( ${PROJECT_NAME} ${SOURCES} ${UI_FILES} ${QRCS})
else()
  add_executable( ${PROJECT_NAME} ${SOURCES} ${UI_FILES} ${QRCS})
endif()

# find QT
find_package(Qt5 COMPONENTS Widgets Core Gui PrintSupport REQUIRED)
target_link_libraries(ImageTools PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::PrintSupport)

# find Opencv
find_package( OpenCV REQUIRED )
if(OpenCV_FOUND)
    message(STATUS "OpenCV library has found")
    message(STATUS "OpenCV_INCLUDE_DIR: " ${OpenCV_INCLUDE_DIRS})
    message(STATUS "OpenCV_LIBRARY: " ${OpenCV_LIBS})
#    target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
else(OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV library not found")
endif(OpenCV_FOUND)

#CONFIGURE_FILE(
#    "${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
#    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
#    IMMEDIATE @ONLY)

#ADD_CUSTOM_TARGET(uninstall
#    "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")

# find VLCQt
find_package(VLCQt REQUIRED COMPONENTS Widgets Core)

#target_include_directories(${PROJECT_NAME} PRIVATE ${VLCQt_INCLUDE})
message(STATUS "INC:" ${VLCQt_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE VLCQt::Widgets VLCQt::Core)


## Set Qt bin dir to find QtCore*.dll and other libs to install
#STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" QT_BIN_DIR_TMP "${QT_MOC_EXECUTABLE}")
#STRING(REGEX REPLACE "\\\\" "/" QT_BIN_DIR "${QT_BIN_DIR_TMP}")  # Replace back slashes to slashes
#STRING(REGEX REPLACE "bin" "lib" QT_LIB_DIR "${QT_BIN_DIR}")

## Set default install path:
## In *nix environments this is /usr/local
## Under M$ Windows this is C:\Program files\${PROJECT_NAME}
## WARNING: Leading slash should be added - this is for easier concatenation of the strings due to slash/backslash issues
#IF(MINGW OR MSVC)
#    IF(NOT CMAKE_INSTALL_PREFIX)
#        SET(CMAKE_INSTALL_PREFIX "C:/Program files/${PROJECT_NAME}")
#    ENDIF()
#    SET(PROJECT_INSTALL_BIN_DIR ".")
#    SET(PROJECT_INSTALL_LIB_DIR "lib")
#ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    IF(NOT CMAKE_INSTALL_PREFIX)
#        SET(CMAKE_INSTALL_PREFIX "/Applications")
#    ENDIF()
#    SET(PROJECT_INSTALL_BIN_DIR "${PROJECT_NAME}.app/Contents/MacOS")
#    SET(PROJECT_INSTALL_LIB_DIR "${PROJECT_NAME}.app/Contents/MacOS/lib")
#    SET(CMAKE_INSTALL_RPATH "@executable_path/lib")
#ELSE()
#    IF(NOT CMAKE_INSTALL_PREFIX)
#        SET(CMAKE_INSTALL_PREFIX "/usr/local")
#    ENDIF()
#    SET(PROJECT_INSTALL_BIN_DIR "bin")
#    SET(PROJECT_INSTALL_LIB_DIR "lib")
#ENDIF()

## Set the OS X Bundle specific CMake variables which will be used to populate the plist for
## the application bundle
#SET(MACOSX_BUNDLE_COPYRIGHT "2020 liqinxing")
#SET(MACOSX_BUNDLE_ICON_FILE "${PROJECT_NAME}.icns")
#SET(MACOSX_BUNDLE_GUI_IDENTIFIER "si.tano.${PROJECT_NAME_LOWER}")

#SET(WINDOWS_AUTHOR "liqinxing")
#SET(WINDOWS_DESCRIPTION "image tool")
#SET(WINDOWS_COPYRIGHT "Copyright (C) ${MACOSX_BUNDLE_COPYRIGHT}")
