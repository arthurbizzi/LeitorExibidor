cmake_minimum_required(VERSION 3.2)
project(LeitorExibidor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES
    main.c
    main.h)

add_executable(LeitorExibidor ${SOURCE_FILES} imprime.h imprime.c carregamento.h carregamento.c exec_intrucoes.h Instrucoes/exec_instrucoes.h Instrucoes/exec_instrucoes.c)
add_definitions(-std=c99)