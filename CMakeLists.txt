cmake_minimum_required(VERSION 3.28)
project(BisonAudioConverter)

set(CMAKE_CXX_STANDARD 23)
find_package(imgui CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(nfd CONFIG REQUIRED)
find_package(mp3lame CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)
find_package(PNG REQUIRED)

find_path(MINIAUDIO_INCLUDE_DIRS "miniaudio.h")
include_directories(${MINIAUDIO_INCLUDE_DIRS})
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
add_executable(BisonAudioConverter src/main.cpp
        include/AppState.h
        src/MainWindow.cpp
        include/MainWindow.h
        src/LogWindow.cpp
        include/LogWindow.h
        src/AudioConverter.cpp
        include/AudioConverter.h
        src/SingleFileConverterWindow.cpp
        include/SingleFileConverterWindow.h
        src/AboutWindow.cpp
        include/AboutWindow.h
        src/HelpWindow.cpp
        include/HelpWindow.h)
target_link_libraries(BisonAudioConverter PRIVATE imgui::imgui glfw opengl32 fmt::fmt nfd::nfd mp3lame::mp3lame Vorbis::vorbisfile Vorbis::vorbis Vorbis::vorbisenc PNG::PNG)
