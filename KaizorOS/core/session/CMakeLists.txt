cmake_minimum_required(VERSION 3.16)

project(kaizor-sessionmanager)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(kaizor-sessionmanager
    sessionmanager.cpp
)

target_link_libraries(kaizor-sessionmanager
    PRIVATE Qt6::Widgets
)
