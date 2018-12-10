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

#include <cs2_game.h>
#include <cs2_widgets.h>

namespace CS2
{
    CS2Widget::CS2Widget(lite3dpp::Scene &scene, const kmVec2 &origin) :
        mScene(scene),
        mOrigin(origin)
    {}

    CS2Panel::CS2Panel(lite3dpp::Scene &scene, const kmVec2 &origin, const kmVec2 &size) : 
        CS2Widget(scene, origin),
        mSize(size)
    {}

    CS2Button::CS2Button(lite3dpp::Scene &scene, const kmVec2 &origin, const kmVec2 &size, const std::string &text) : 
        CS2Widget(scene, origin),
        mSize(size),
        mText(text)
    {}
}