
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
project(CrazySpace2)

set(BUILD_ENGINE_ONLY ON CACHE BOOL "Do not build samples, tests and other staff" FORCE)

add_subdirectory("${PROJECT_SOURCE_DIR}/3dlite/")
add_subdirectory("${PROJECT_SOURCE_DIR}/game/")
add_subdirectory("${PROJECT_SOURCE_DIR}/loader/pc/")
