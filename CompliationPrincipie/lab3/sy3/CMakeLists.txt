cmake_minimum_required(VERSION 3.12)
project(a)
set(CMAKE_C_STANDARD 99)

add_executable(a ast.c main.c lex.yy.c lrparser.tab.c ast.h lrparser.tab.h )
#add_custom_target(lrparser COMMAND make -C ${lrparser_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})
