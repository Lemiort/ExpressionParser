cmake_minimum_required(VERSION 3.6)
project(ExpressionParser)

set(CMAKE_CXX_STANDARD 11)
include_directories( include
        include/optimization)
set(SOURCE_FILES
        include/optimization/lab3.h
        include/optimization/lab3_vector.h
        include/exception.h
        include/expression.h
        include/MathVector.h
        include/Matrix.h
        include/parser.h
        src/main.cpp
        src/MathVector.cpp
        src/Matrix.cpp)

add_executable(ExpressionParser ${SOURCE_FILES})