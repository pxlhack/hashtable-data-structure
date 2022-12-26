cmake_minimum_required(VERSION 3.24)
project(hashtable2)

set(CMAKE_CXX_STANDARD 23)

add_executable(hashtable
        main.cpp
        lib/table_form.h
        lib/node.h
        lib/oa_node.h
        lib/cc_node.h
        lib/oa_form.h
        lib/hash_table.h
        lib/cc_form.h
        lib/user_menu.h)


add_executable(test
        lib/table_form.h
        lib/node.h
        lib/oa_node.h
        lib/cc_node.h
        lib/oa_form.h
        lib/hash_table.h
        lib/cc_form.h
        lib/user_menu.h
        performance_test.cpp)