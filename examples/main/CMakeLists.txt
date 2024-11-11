cmake_minimum_required(VERSION 3.30)

# Variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

set(EXAMPLE_SRC src/main.cpp)

# Project
project(main)

# Add subdirectories
# add_subdirectory(wengine)
# add_subdirectory(include/imgui)
# add_subdirectory(include/glad)

# Library directory
# link_directories(${PROJECT_SOURCE_DIR}/lib)

# Executable
add_executable(${PROJECT_NAME} ${EXAMPLE_SRC})

# Include directory
# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/imgui)

# Libraries to link
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} wengine)
target_link_libraries(${PROJECT_NAME} glfw3)

# directories and file essential for program
file(COPY shader DESTINATION .)
file(COPY res DESTINATION .)
