
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_DIR} ${ECM_KDE_MODULE_DIR})
include(KDEInstallDirs)
include(KDECMakeSettings)

set(cpu_freq_helper_SRCS
    cpu_freq_helper.cpp
    #cpu_freq_helper.h
    )

#qt5_wrap_cpp (HELPER_MOC_SOURCES ${cpu_freq_helper_SRCS})

add_executable(cpu_freq_helper ${cpu_freq_helper_SRCS})
target_link_libraries(cpu_freq_helper KF5::Auth)
install(TARGETS cpu_freq_helper DESTINATION ${KAUTH_HELPER_INSTALL_DIR})
message("KAUTH_HELPER_INSTALL_DIR: ${KAUTH_HELPER_INSTALL_DIR}")
message("KAUTH_POLICY_FILES_INSTALL_DIR: ${KAUTH_POLICY_FILES_INSTALL_DIR}")
message("DBUS_SYSTEM_SERVICES_INSTALL_DIR: ${DBUS_SYSTEM_SERVICES_INSTALL_DIR}")

kauth_install_helper_files(
    cpu_freq_helper
    org.freedesktop.auth.cpufrequtility
    root)
kauth_install_actions(
    org.freedesktop.auth.cpufrequtility
    actions.actions)
