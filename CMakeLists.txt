cmake_minimum_required(VERSION 3.10)

project(opeglsa)

set(
    SRC
    src/main.cpp
    "include/renderer.h"
    src/vertexarray.cpp
    src/vertexbuffer.cpp
    src/indexbuffer.cpp
    src/renderer.cpp
    src/Game.cpp
    src/shader.cpp
    src/Gui.cpp
    src/timer.cpp

#   ImGui
    vendor/imgui/src/imgui.cpp
    vendor/imgui/src/imgui_demo.cpp
    vendor/imgui/src/imgui_draw.cpp
    vendor/imgui/src/imgui_impl_glfw.cpp
    vendor/imgui/src/imgui_impl_opengl3.cpp
    vendor/imgui/src/imgui_tables.cpp
    vendor/imgui/src/imgui_widgets.cpp
)
set(
    CPP_INCLUDE_PATH
    "include/"
)

add_executable(
    ${PROJECT_NAME}
    ${SRC}
)

find_library(glfw3 glfw)
find_library(opengl GL)
find_library(glm glm)
find_library(glew GLEW)

target_link_libraries(
    ${PROJECT_NAME}
    ${glfw3}
    ${opengl}
    ${glm}
    ${glew}
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${CPP_INCLUDE_PATH}
    PRIVATE vendor/imgui/include
)