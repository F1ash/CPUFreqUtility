if (NOT CMAKE_INSTALL_PREFIX) 
 set (CMAKE_INSTALL_PREFIX /usr) 
endif () 

cmake_minimum_required(VERSION 2.8.12)
project (kf5-cpufrequtility)

find_package(KF5Auth REQUIRED)
add_subdirectory(src)
