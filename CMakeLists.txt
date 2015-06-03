if (NOT CMAKE_INSTALL_PREFIX) 
 set (CMAKE_INSTALL_PREFIX /usr) 
endif ()

cmake_minimum_required(VERSION 3.2)
project (kf5-cpufrequtility)

find_package(KF5Auth REQUIRED)

set(cpu_freq_helper_SRCS
    src/helper/cpu_freq_helper.cpp
    src/helper/cpu_freq_helper.h)
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

qt5_wrap_cpp (HELPER_MOC_SOURCES ${cpu_freq_helper_SRCS})

find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
qt5_add_resources(RCCs src/cpufreq_icons.qrc)
set (BUILD_PROJECT_LIBRARIES ${Qt5Widgets_LIBRARIES} KF5::Auth)
add_definitions(${Qt5Widgets_DEFINITIONS})

add_executable(cpu_freq_helper ${cpu_freq_helper_SRCS} ${HELPER_MOC_SOURCES})
target_link_libraries(cpu_freq_helper KF5::Auth)
install(TARGETS cpu_freq_helper DESTINATION ${KAUTH_HELPER_INSTALL_DIR})

kauth_install_helper_files(
    cpu_freq_helper
    org.freedesktop.auth.cpufrequtility
    root)
kauth_install_actions(
    org.freedesktop.auth.cpufrequtility
    src/helper/org.freedesktop.auth.cpufrequtility.actions)

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
