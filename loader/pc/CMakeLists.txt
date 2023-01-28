
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

project(loader)

unset(SOURCES_LIST)
unset(HEADERS_LIST)

source_files("src")
headers_files("include")
add_executable(loader ${SOURCES_LIST} ${HEADERS_LIST})

target_compile_definitions(loader PRIVATE
"$<BUILD_INTERFACE:${PLATFORM_TYPE}>")
target_include_directories(loader PRIVATE 
"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>")

target_link_libraries(loader
cs2)
