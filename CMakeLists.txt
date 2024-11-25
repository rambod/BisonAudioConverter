cmake_minimum_required(VERSION 3.28)
project(BisonAudioConverter)

set(CMAKE_CXX_STANDARD 23)
find_package(imgui CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(BisonAudioConverter main.cpp
        AppState.h
        MainWindow.cpp
        MainWindow.h
        AnotherWindow.cpp
        AnotherWindow.h)
target_link_libraries(BisonAudioConverter PRIVATE imgui::imgui glfw opengl32 fmt::fmt)
