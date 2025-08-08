cmake_minimum_required(VERSION 3.30)
project(Calculator C)

set(CMAKE_C_STANDARD 11)

add_executable(Calculator src/main.c
        src/parser/parser.h
        src/parser/parser.c
        src/context/calculation_context.h
        src/context/calculation_context.c
        src/token/token.h
        src/token/token.c)
