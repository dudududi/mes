cmake_minimum_required(VERSION 3.3)
project(mes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(armadillo/include/)
set(SOURCE_FILES sources/main.cpp sources/GlobalData.cpp headers/GlobalData.h sources/Exception.cpp headers/Exception.h sources/Node.cpp headers/Node.h sources/Element.cpp headers/Element.h sources/FEMGrid.cpp headers/FEMGrid.h sources/Matrix.cpp headers/Matrix.h sources/BoundaryCondition.cpp headers/BoundaryCondition.h sources/Solver.cpp headers/Solver.h)
add_executable(mes ${SOURCE_FILES})