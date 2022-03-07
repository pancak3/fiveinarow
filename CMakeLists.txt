cmake_minimum_required(VERSION 3.19)
project(fiveinarow C)

set(CMAKE_C_STANDARD 11)

include_directories(header)
add_executable(fiveinarow
        src/main.c src/game.c header/game.h header/main.h)
