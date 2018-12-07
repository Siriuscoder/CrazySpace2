
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

cmake_minimum_required(VERSION 2.8.9)
project(cs2)

unset(SOURCES_LIST)
unset(HEADERS_LIST)

source_files("src")
headers_files("include")
add_library(cs2 SHARED ${SOURCES_LIST} ${HEADERS_LIST})

if(MSVC)
target_compile_definitions(cs2 PRIVATE
"$<BUILD_INTERFACE:WIN_CS2_DLL>")
endif()

target_compile_definitions(cs2 PRIVATE
"$<BUILD_INTERFACE:${PLATFORM_TYPE}>")

target_include_directories(cs2 PRIVATE 
"$<BUILD_INTERFACE:${SDL2_INCLUDE_DIR}>"
"$<BUILD_INTERFACE:${CMAKE_CRAZYSPACE2_TOP_DIR}/3dlite/lite3d/include>"
"$<BUILD_INTERFACE:${CMAKE_CRAZYSPACE2_TOP_DIR}/3dlite/lite3dpp/include>"
"$<BUILD_INTERFACE:${CMAKE_CRAZYSPACE2_TOP_DIR}/3dlite/lite3dpp_font/include>")

target_link_libraries(cs2
lite3d
lite3dpp
lite3dpp_font)
