project(libcommon) 
add_library(${PROJECT_NAME}
        ${PROJECT_SOURCE_DIR}/template/fileoperate/file_operate.c
        ${PROJECT_SOURCE_DIR}/template/memalloc/alloc.c
        ${PROJECT_SOURCE_DIR}/template/queue/queue.c
        ${PROJECT_SOURCE_DIR}/template/stack/stack.c
        ${PROJECT_SOURCE_DIR}/datastruct/queue/queue_utils.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/
        ${PROJECT_SOURCE_DIR}/template/fileoperate
        ${PROJECT_SOURCE_DIR}/template/memalloc
        ${PROJECT_SOURCE_DIR}/template/queue
        ${PROJECT_SOURCE_DIR}/template/stack
        ${PROJECT_SOURCE_DIR}/datastruct/queue
        ${PROJECT_SOURCE_DIR}/datastruct/list
)
find_package (Threads)
target_link_libraries(${PROJECT_NAME}
    libdebug
    ${CMAKE_THREAD_LIBS_INIT}
)