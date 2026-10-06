cmake_minimum_required(VERSION 3.29)
project(Game-Of-Life DESCRIPTION "Simple simulator of the Game of Life")

message("--------------------------")
message("  Compiling ${PROJECT_NAME}")
message("      By Z4na14 <3        ")
message("--------------------------")

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/inc)

add_executable(${PROJECT_NAME} ${SRC_DIR}/main.c
                                ${SRC_DIR}/dot.c
                                 ${SRC_DIR}/console.c)

include_directories(${INC_DIR})