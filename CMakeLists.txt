
#	This file is part of CrazySpace2.
#	Copyright (C) 2018  Sirius (Korolev Nikita)
#
#	CrazySpace2 is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	CrazySpace2 is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with CrazySpace2.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.12.0)
project(CrazySpace2)

set(BUILD_ENGINE_ONLY ON CACHE BOOL "Do not build samples, tests and other staff" FORCE)
set(CMAKE_CRAZYSPACE2_TOP_DIR ${PROJECT_SOURCE_DIR})

add_subdirectory("${CMAKE_CRAZYSPACE2_TOP_DIR}/3dlite/")

# Configuration
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Specify build paths
if(MSVC)
    # In MSVC configuration folders created automatically  
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
else()
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
    endif()

    message(STATUS "Build configuration (${PROJECT_NAME}): ${CMAKE_BUILD_TYPE} : ${PLATFORM_TYPE}")
	
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) 
    set(DEBUG_COMPILER_FLAGS "-g3 -O0 -fstack-protector-all")
    set(RELEASE_COMPILER_FLAGS "-g0 -O3")
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-deprecated-declarations -Wno-format-security")
    set(CMAKE_CXX_FLAGS_DEBUG ${DEBUG_COMPILER_FLAGS})
    set(CMAKE_CXX_FLAGS_RELEASE ${RELEASE_COMPILER_FLAGS})
    add_definitions(-fPIC -pedantic)
elseif(MSVC)
    set(RELEASE_COMPILER_FLAGS "/O2 /Ot /Ob2")
    set(CMAKE_CXX_FLAGS_RELEASE ${RELEASE_COMPILER_FLAGS})

    add_definitions(/fp:fast /W3 /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS)
endif()

include_directories("${CMAKE_CRAZYSPACE2_TOP_DIR}/game/include")
add_subdirectory("${CMAKE_CRAZYSPACE2_TOP_DIR}/game/")
add_subdirectory("${CMAKE_CRAZYSPACE2_TOP_DIR}/loader/pc/")
