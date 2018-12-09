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
#include <sstream>

#include <cs2_input.h>

namespace CS2
{
    CS2Input::CS2Input(lite3dpp::Main &engine) : 
        CS2EngineListener(engine)
    {}

    void CS2Input::processEvent(SDL_Event *e)
    {
        if (e->type == SDL_KEYDOWN)
        {
            /* exit */
            if (e->key.keysym.sym == SDLK_ESCAPE)
                getEngine().stop();
        }
    }
}