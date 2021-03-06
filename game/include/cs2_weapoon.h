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

#include <cs2_common.h>
#include <cs2_missle.h>

namespace CS2
{
    class CS2Weapoon
    {
    public:

        using CS2WeapoonPtr = std::shared_ptr<CS2Weapoon>;

        CS2Weapoon(float reloadTimeMs);

        virtual bool isReloaded();
        virtual CS2Missle::CS2MisslePtr fire() = 0;

    protected:

        float mReloadTime;
    };
}
