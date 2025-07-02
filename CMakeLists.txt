cmake_minimum_required(VERSION 3.10)
project(DigitalLogicSuite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

# Add executable
add_executable(digital-logic-suite main.cpp)

# Link libraries
target_link_libraries(digital-logic-suite ${GTKMM_LIBRARIES})
target_include_directories(digital-logic-suite PRIVATE ${GTKMM_INCLUDE_DIRS})
target_compile_options(digital-logic-suite PRIVATE ${GTKMM_CFLAGS_OTHER})
