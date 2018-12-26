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
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <cs2_utils.h>

namespace CS2
{
    float CS2Math::random(float a)
    {
        return random_range(0.0f, a);
    }

    int CS2Math::random(int a)
    {
        return random_range(0, a);
    }

    float CS2Math::random_range(float min, float max)
    {
        float scale = rand() / static_cast<float>(RAND_MAX);    /* [0, 1.0] */
        return min + scale * (max - min);                       /* [min, max] */
    }

    int CS2Math::random_range(int min, int max)
    {
        /* https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand */
        return min + rand() / (RAND_MAX / (max - min + 1) + 1);
    }
}