
cmake_minimum_required(VERSION 3.10)
project(Ultrakill C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ../src/main.c ../src/movement/keysMovement.c ../src/audio/manageAudio.c)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    /usr/local/include
)

target_link_directories(${PROJECT_NAME} PRIVATE
    /usr/local/lib
)

target_link_libraries(${PROJECT_NAME} raylib m)


add_executable(test_parser
    tests/testParser.c
    src/parserJson/cJSON.c
    src/parserJson/parser.c
)

target_include_directories(test_parser PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(test_parser
    m
)

add_executable(test_terminalEngine
    tests/testTerminalEngine.c
    src/terminalEngine/v1View.c
    src/parserJson/cJSON.c
    src/parserJson/parser.c
    src/textScheduler/scheduler.c
)

target_include_directories(test_terminalEngine PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(test_terminalEngine raylib)