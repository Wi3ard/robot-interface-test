cmake_minimum_required(VERSION 3.5.0)

project(robot-test)

#
# Compiler options.
#

if (MSVC)
    # Ignore warning for missing PDBs.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4099")
endif()

#
# External dependencies.
#

# Load Conan configuration.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#
# Source files.
#

set(SOURCES
	src/Command.h
	src/main.cpp
	src/MockRobot.h
	src/RobotCommand.h
	src/RobotMock.h)

set(MISC
	src/pch.h
	src/targetver.h)

source_group("Implementation Files" FILES ${SOURCES})
source_group("" FILES ${MISC})

#
# Target.
#

add_executable(${PROJECT_NAME}
	${MISC}
	${SOURCES})

target_link_libraries(${PROJECT_NAME}
	robot-sdk
	${CONAN_LIBS_GTEST})

# Precompiled headers.
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "src/pch.h")
cotire(${PROJECT_NAME})
