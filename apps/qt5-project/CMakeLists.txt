project( Qt5Project )
message("====================================================")
message(STATUS "build app: " ${PROJECT_NAME})

# set( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/Qt/5.15.0/mingw81_64/lib/cmake" ) # remember to add `C:\Qt\VS2015x64\Qt5.6.0\5.6\msvc2015_64\bin` to %PATH%
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )

find_package( Qt5 COMPONENTS Core Gui Qml Quick Widgets REQUIRED )

# find all source file in src
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCES)
message(STATUS "SRC FILES: " ${SOURCES})

# include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR})

#查找当前文件夹中所有的ui文件
FILE(GLOB UI_FILES "*.ui") 

#通过Ui文件生成对应的头文件，一定要添加
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

#添加资源文件
qt5_add_resources( QRCS resources.qrc )

add_executable( ${PROJECT_NAME} ${SOURCES} ${UI_HEADERS} ${QRCS} )
target_link_libraries( ${PROJECT_NAME} Qt5::Widgets )
