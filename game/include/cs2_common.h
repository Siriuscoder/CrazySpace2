/******************************************************************************
*	This file is part of CrazySpace2 (Sample game).
*	Copyright (C) 2018  Sirius (Korolev Nikita)
*
*	CrazySpace2 is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	CrazySpace2 is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with CrazySpace2.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/
#pragma once

#ifdef	__cplusplus
#   define CS2_EXTERN  extern "C" 
#else
#   define CS2_EXTERN 
#endif

#ifdef PLATFORM_Windows
#   ifdef WIN_CS2_DLL
// When making the DLL, export tagged symbols, so they appear
// in the import library.
#   define CS2_EXPORT __declspec(dllexport)
#   define CS2_CLASS_EXPORT CS2_EXPORT
#   else
// We must be _using_ the DLL, so import symbols instead.
#   define CS2_EXPORT
#   define CS2_CLASS_EXPORT __declspec(dllimport)
#   endif
#elif PLATFORM_Linux
#   define CS2_EXPORT
#   define CS2_CLASS_EXPORT
#endif


#define CS2_CEXPORT CS2_EXTERN CS2_EXPORT 
