if (NOT CMAKE_INSTALL_PREFIX) 
 set (CMAKE_INSTALL_PREFIX /usr) 
endif () 

cmake_minimum_required(VERSION 2.8.12)
#cmake_policy(SET CMP0037 OLD)

project (CPUFreqUtility)

find_package(KF5Auth          REQUIRED)
find_package(KF5Notifications REQUIRED)
add_subdirectory(src)

install ( FILES       ${PROJECT_NAME}.desktop
          DESTINATION ${SHARE_INSTALL_PREFIX}/applications )
