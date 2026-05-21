cmake_minimum_required(VERSION 3.16)

project(kaizor-dock)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(kaizor-dock
    src/dockanim.cpp
)

target_link_libraries(kaizor-dock
    PRIVATE Qt6::Widgets
)
