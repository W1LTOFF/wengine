cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

file(GLOB GLAD_SRC "*.c")

project(glad)

add_library(${PROJECT_NAME} STATIC ${GLAD_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${RPROJECT_SOURCE_DIR}../)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

link_directories(${PROJECT_SOURCE_DIR}/../../lib)
