cmake_minimum_required(VERSION 4.3)
project(parking_patrol)

set(CMAKE_CXX_STANDARD 20)

add_executable(parking_patrol 
        src/main.cpp
        src/quick_sort.cpp
        src/quick_sort.h
        src/ticket.h
        src/MergeSort.h
        src/MergeSort.cpp
        src/csv_loader.h)
