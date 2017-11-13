cmake_minimum_required(VERSION 3.5.0)

project(robot-interface-test)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake Targets")

set(CMAKE_CXX_STANDARD 11)

include(CRTLinkage)
include(cotire)

#
# Project subdirectories.
#

add_subdirectory(modules/robot-sdk)
add_subdirectory(tests/robot-test)
