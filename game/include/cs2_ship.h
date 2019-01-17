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
#include <cs2_object.h>
#include <cs2_weapoon.h>
#include <cs2_missle.h>

namespace CS2
{
    class CS2Ship : public CS2GameObject
    {
    public:

        using CS2ShipPtr = std::shared_ptr<CS2Ship>;

        CS2Ship(lite3dpp::Scene &scene,
            const std::string &name,
            const std::string &templatePath,
            float maxSpeed,
            float accel,
            float health);

        void animate() override;

        /* movement */
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();

        /* figthing */
        CS2Missle::CS2MisslePtr fire();
        void damage(CS2Missle::CS2MisslePtr missle);
        bool isDestroyed();
        void setWeapoon(CS2Weapoon::CS2WeapoonPtr weapoon);

    protected:

        float mMaxSpeed;
        float mCurrSpeed;
        float mAccel;
        float mHealth;
        float mCurrHealth;
        CS2Weapoon::CS2WeapoonPtr mWeapoon;
    };
}
