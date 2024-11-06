cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

set(WENGINE_LIB_CORE_SRC
    src/core/camera.cpp 
    src/core/engine.cpp 
    src/core/gui.cpp 
    src/core/model.cpp 
    src/core/resourceManager.cpp 
    src/core/shader.cpp 
    src/core/texture.cpp 
    src/core/window.cpp 
)

set(WENGINE_LIB_ALL_SRC ${WENGINE_LIB_CORE_SRC})

project(wengine)

add_library(${PROJECT_NAME} STATIC ${WENGINE_LIB_ALL_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/imgui)

link_directories(${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw3)
target_link_libraries(${PROJECT_NAME} opengl32)
