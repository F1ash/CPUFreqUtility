if (NOT CMAKE_INSTALL_PREFIX) 
 set (CMAKE_INSTALL_PREFIX /usr) 
endif () 

cmake_minimum_required(VERSION 3.2)
project (kf5-cpufrequtility)

find_package(KF5Auth REQUIRED)
add_subdirectory(src)
