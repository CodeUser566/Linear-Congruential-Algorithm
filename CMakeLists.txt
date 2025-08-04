cmake_minimum_required(VERSION 3.16)

project(LinearCongruentialAlgorithm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LinearCongruentialAlgorithm main.cpp)

include(GNUInstallDirs)
install(TARGETS LinearCongruentialAlgorithm
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
