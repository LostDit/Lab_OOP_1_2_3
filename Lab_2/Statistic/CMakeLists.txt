cmake_minimum_required(VERSION 4.0)
project(Statistic)

set(CMAKE_CXX_STANDARD 23)

add_executable(Statistic main.cpp
        ui.cpp
        ui.h
        Statistic.cpp
        Statistic.h)
