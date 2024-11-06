cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

file(GLOB IMGUI_SRC "*.cpp")

project(imgui)

add_library(${PROJECT_NAME} STATIC ${IMGUI_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${RPROJECT_SOURCE_DIR}../)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

link_directories(${PROJECT_SOURCE_DIR}/../../lib)

target_link_libraries(${PROJECT_NAME} glfw3)
target_link_libraries(${PROJECT_NAME} opengl32)
