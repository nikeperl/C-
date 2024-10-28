cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(test_proj VERSION 0.2.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# generate a library from sources
add_subdirectory(src)
target_include_directories(Library PUBLIC .) # PRIVATE

add_executable(main main_BitArray.cpp)

enable_testing()
# as a separate target
add_subdirectory(tests)
target_link_libraries(main Library)
