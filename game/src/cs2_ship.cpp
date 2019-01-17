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
#include <cs2_ship.h>

namespace CS2
{
    CS2Ship::CS2Ship(lite3dpp::Scene &scene,
        const std::string &name,
        const std::string &templatePath,
        float maxSpeed,
        float accel,
        float health) : 
        CS2GameObject(scene, name, templatePath),
        mMaxSpeed(maxSpeed),
        mCurrSpeed(0.0f),
        mAccel(accel),
        mHealth(health),
        mCurrHealth(health)
    {}

    void CS2Ship::animate()
    {
        
    }

    /* movement */
    void CS2Ship::moveForward()
    {

    }

    void CS2Ship::moveBackward()
    {

    }

    void CS2Ship::moveLeft()
    {

    }

    void CS2Ship::moveRight()
    {

    }

    /* figthing */
    CS2Missle::CS2MisslePtr CS2Ship::fire()
    {
        assert(mWeapoon);
        if (mWeapoon->isReloaded())
            return mWeapoon->fire();

        return CS2Missle::CS2MisslePtr();
    }

    void CS2Ship::damage(CS2Missle::CS2MisslePtr missle)
    {
        assert(missle);
        mCurrHealth -= missle->getBaseDamage();
    }

    bool CS2Ship::isDestroyed()
    {
        return mCurrHealth <= 0.0f;
    }

    void CS2Ship::setWeapoon(CS2Weapoon::CS2WeapoonPtr weapoon)
    {
        assert(weapoon);
        mWeapoon = weapoon;
    }
}