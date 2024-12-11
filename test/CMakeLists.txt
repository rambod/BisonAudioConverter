cmake_minimum_required(VERSION 3.28)
project(BisonAudioConverter)

set(CMAKE_CXX_STANDARD 23)
find_package(imgui CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(nfd CONFIG REQUIRED)
find_path(MINIAUDIO_INCLUDE_DIRS "miniaudio.h")
add_executable(BisonAudioConverter src/main.cpp
        include/AppState.h
        src/MainWindow.cpp
        include/MainWindow.h
        src/AnotherWindow.cpp
        include/AnotherWindow.h
        src/AudioConverter.cpp
        include/AudioConverter.h
        resources/app_icon.rc)
target_link_libraries(BisonAudioConverter PRIVATE imgui::imgui glfw opengl32 fmt::fmt nfd::nfd)
include_directories(${MINIAUDIO_INCLUDE_DIRS})
