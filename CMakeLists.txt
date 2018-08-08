cmake_minimum_required(VERSION 3.9)
project(ft_ls C)

set(CMAKE_C_STANDARD 99)

add_executable(ft_ls src/main.c inc/ft_ls_header.h src/ft_ls_algorithm.c src/buffer_management.c src/file_management.c src/main_utils.c src/sorting_management.c src/sort_cmp_functions.c src/printing_management.c)