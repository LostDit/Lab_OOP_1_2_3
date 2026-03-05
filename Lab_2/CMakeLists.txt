cmake_minimum_required(VERSION 4.0)
project(Lab_2)

set(CMAKE_CXX_STANDARD 26)

add_executable(Lab_2 main.cpp
        Radio.cpp
        Radio.h
        Field.cpp
        Field.h
        Statistic.cpp
        Statistic.h)
