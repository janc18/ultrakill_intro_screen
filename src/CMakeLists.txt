
cmake_minimum_required(VERSION 3.10)
project(Ultrakill C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
include_directories(/usr/local/include)
include_directories(../include)
link_directories(/usr/local/lib)

add_executable(${PROJECT_NAME} ../src/main.c ../src/drawingText.c ../src/manageAudio.c)
target_link_libraries(${PROJECT_NAME} raylib m)
