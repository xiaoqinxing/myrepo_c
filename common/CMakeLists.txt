project(libcommon)

add_library(${PROJECT_NAME}
        ${PROJECT_SOURCE_DIR}/template/fileoperate/file_operate.c
        ${PROJECT_SOURCE_DIR}/template/memalloc/alloc.c
        ${PROJECT_SOURCE_DIR}/template/queue/queue.c
        ${PROJECT_SOURCE_DIR}/template/stack/stack.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
                ${PROJECT_SOURCE_DIR}/template/fileoperate
                ${PROJECT_SOURCE_DIR}/template/memalloc
                ${PROJECT_SOURCE_DIR}/template/queue
                ${PROJECT_SOURCE_DIR}/template/stack
                ${PROJECT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
    libdebug
)