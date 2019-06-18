cmake_minimum_required(VERSION 3.13)

project(FdF C)      # project name

set(CMAKE_C_STANDARD 99)

add_compile_options()##-Wall -Werror -Wextra) # flags

find_library(OPEN_GL OpenGl)

find_library(APP_KIT AppKit)

include_directories(./src ./src/libft/includes)  #directory with headers

link_directories(/usr/local/lib ./src/libft)

link_libraries(mlx)

FILE(GLOB LIBFT_SRCS ./src/libft/*.c)  # ADD LIBFT as sources

add_executable(FdF ${LIBFT_SRCS} ./src/FdF.h ./src/geometry.c ./src/main2.c)  # all project-c-files here

target_link_libraries(FdF ${OPEN_GL} ${APP_KIT})  # LINK libraries

target_link_libraries(FdF -lft)
#${LIBFT}