cmake_minimum_required(VERSION 3.24)
project(hashtable2)

set(CMAKE_CXX_STANDARD 23)

add_executable(hashtable
        main.cpp
        lib/table_form.h lib/node.h)
