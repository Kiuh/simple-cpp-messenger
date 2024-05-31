cmake_minimum_required (VERSION 3.8)
set(PROJECT_NAME client)

project(${PROJECT_NAME})

set(LOCAL_SRCS "")
aux_source_directory(src LOCAL_SRCS)

add_executable(${PROJECT_NAME} ${LOCAL_SRCS})