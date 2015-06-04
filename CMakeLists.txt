if (NOT CMAKE_INSTALL_PREFIX) 
 set (CMAKE_INSTALL_PREFIX /usr) 
endif () 

cmake_minimum_required(VERSION 3.2)
project (kf5-cpufrequtility)

find_package(KF5Auth REQUIRED)
add_subdirectory(src/helper)

set(HEADERS
    src/mainwindow.h
    src/cpu_item.h
    src/toolbar.h
    src/tray/traywidget.h)
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/cpu_item.cpp
    src/toolbar.cpp
    src/tray/traywidget.cpp)
set(CFH_DESKTOP_FILE ${PROJECT_NAME}.desktop)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
qt5_add_resources(RCCs src/cpufreq_icons.qrc)
set (BUILD_PROJECT_LIBRARIES ${Qt5Widgets_LIBRARIES} KF5::Auth)
add_definitions(${Qt5Widgets_DEFINITIONS})

add_executable(
    ${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
    ${MOC_SOURCES}
    ${RCCs})
target_link_libraries(${PROJECT_NAME} ${BUILD_PROJECT_LIBRARIES}) 

install ( TARGETS     ${PROJECT_NAME}
          DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
install ( FILES CFH_DESKTOP_FILE
          DESTINATION ${SHARE_INSTALL_PREFIX}/applications )
