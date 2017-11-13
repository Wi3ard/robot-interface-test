cmake_minimum_required(VERSION 3.5.0)

project(robot-sdk)

#
# 3rd-party libraries.
#

#
# Source files.
#

set(HEADERS
	include/robot-sdk/IRobot.h)

set(SOURCES
	src/Robot.cpp
	src/Robot.h)

set(MISC
	src/pch.h
	src/targetver.h)

source_group("Implementation Files" FILES ${SOURCES})
source_group("Public Headers" FILES ${HEADERS})
source_group("" FILES ${MISC})

#
# Target.
#

add_library(${PROJECT_NAME} STATIC
	${HEADERS}
	${MISC}
	${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
	include)

# Precompiled headers.
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "src/pch.h")
cotire(${PROJECT_NAME})
