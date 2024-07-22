cmake_minimum_required(VERSION 3.5)
project(buildgame)

find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

add_executable(build_game src/main.cpp raygui.h src/utils.hpp src/utils.cpp src/json.hpp)
target_link_libraries(build_game raylib GL m pthread rt dl X11)
target_link_libraries(build_game ${Qt5Widgets_LIBRARIES})