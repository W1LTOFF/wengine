cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

set(EXAMPLE_SRC src/main.cpp)

project(wengine-example)

add_subdirectory(wengine)
add_subdirectory(include/imgui)
add_subdirectory(include/glad)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} ${EXAMPLE_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/imgui)

target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} wengine)
target_link_libraries(${PROJECT_NAME} glfw3)
target_link_libraries(${PROJECT_NAME} opengl32)

file(COPY shader DESTINATION .)
file(COPY res DESTINATION .)
file(COPY lib/glfw3.dll DESTINATION .)
