project(libdebug)

add_library(${PROJECT_NAME}
        # ${LIB_ROOT_PATH}/fdleak/fdleak_dbg.cpp
        ${PROJECT_SOURCE_DIR}/log/logprint.c
        # ${LIB_ROOT_PATH}/memleak/memleak_dbg.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
                ${PROJECT_SOURCE_DIR}/fdleak/
                ${PROJECT_SOURCE_DIR}/log/
                ${PROJECT_SOURCE_DIR}/memleak/
)