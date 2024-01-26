cmake_minimum_required(VERSION 3.20)
project(PROYECTO)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(NMLIB)

add_executable(PROYECTO
        NMLIB/lib_findroot.c
        NMLIB/lib_linealA.c
        NMLIB/lib_matrix.c
        NMLIB/lib_vector.c
        NMLIB/nmlib.h
        NMLIB/solvers_eigenV.c
        NMLIB/solvers_linealS.c
        image_lib.h
        eigenface_lib.h
        main.c)
