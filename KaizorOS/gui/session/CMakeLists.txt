cmake_minimum_required(VERSION 3.16)

project(kaizor-session)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(kaizor-session
    src/main.cpp
)

target_link_libraries(kaizor-session
    PRIVATE Qt6::Widgets
)
