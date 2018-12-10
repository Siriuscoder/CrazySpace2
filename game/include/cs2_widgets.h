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

#include <lite3dpp/lite3dpp_main.h>
#include <cs2_common.h>

namespace CS2
{
    class CS2Widget : public lite3dpp::Noncopiable
    {
    public:

        CS2Widget(lite3dpp::Scene &scene, const kmVec2 &origin);

    protected:

        kmVec2 mOrigin;
        lite3dpp::Scene &mScene;
    };

    class CS2Panel : public CS2Widget
    {
    public:

        CS2Panel(lite3dpp::Scene &scene, const kmVec2 &origin,
            const kmVec2 &size);

    protected:

        kmVec2 mSize;
    };

    class CS2Button : public CS2Widget
    {
    public:

        CS2Button(lite3dpp::Scene &scene, const kmVec2 &origin,
            const kmVec2 &size, const std::string &text);

    protected:

        kmVec2 mSize;
        std::string mText;
    };
}
