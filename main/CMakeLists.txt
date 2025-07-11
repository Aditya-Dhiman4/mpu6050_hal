# idf_component_register(SRCS "test_mpu6050.c" "main.c" "mpu6050.c"
#                     INCLUDE_DIRS ".")

# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

file(GLOB_RECURSE app_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/app/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/io/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/hw/*.c"
)

idf_component_register(SRCS ${app_sources}
                      INCLUDE_DIRS "."
                                   "app"
                                   "io"
                                   "hw")