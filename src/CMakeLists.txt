
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_DIR} ${ECM_KDE_MODULE_DIR})
include(KDEInstallDirs)

add_subdirectory(helper)

set(HEADERS
    mainwindow.h
    cpu_item.h
    toolbar.h
    tray/traywidget.h)
set(SOURCES
    main.cpp
    mainwindow.cpp
    cpu_item.cpp
    toolbar.cpp
    tray/traywidget.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
qt5_add_resources(RCCs cpufreq_icons.qrc)
set (
    BUILD_PROJECT_LIBRARIES
    ${Qt5Widgets_LIBRARIES}
    KF5::Auth
    KF5::Notifications)
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
#message("KNOTIFYRC_INSTALL_DIR: ${KNOTIFYRC_INSTALL_DIR}")
install(  FILES       ${PROJECT_NAME}.notifyrc
          DESTINATION ${KNOTIFYRC_INSTALL_DIR})
