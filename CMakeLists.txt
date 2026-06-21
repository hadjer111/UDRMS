cmake_minimum_required(VERSION 3.19)
project(UDRMS LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

set(OOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../Desktop/OOP Project")

qt_add_executable(UDRMS
    WIN32 MACOSX_BUNDLE

    # Qt files
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    # OOP Project files (NO main.cpp from here)
    "${OOP_DIR}/Dormitory.cpp"
    "${OOP_DIR}/Dormitory.h"
    "${OOP_DIR}/DormitoryException.h"
    "${OOP_DIR}/Restaurant.cpp"
    "${OOP_DIR}/Restaurant.h"
    "${OOP_DIR}/Room.cpp"
    "${OOP_DIR}/Room.h"
    "${OOP_DIR}/Student.cpp"
    "${OOP_DIR}/Student.h"
    "${OOP_DIR}/University.cpp"
    "${OOP_DIR}/University.h"
)

target_include_directories(UDRMS PRIVATE "${OOP_DIR}")

target_link_libraries(UDRMS
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

install(TARGETS UDRMS
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET UDRMS
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
