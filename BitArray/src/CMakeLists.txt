cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(test_proj VERSION 0.2.1 LANGUAGES CXX)
add_library(Library STATIC BitArray.cpp BitArray.h)
