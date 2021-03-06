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
#include <cs2_engine_listener.h>

namespace CS2
{
    class CS2Star
    {
    public:

        const float maxSpeed = 0.9f;
        const float minSpeed = 0.2f;

        CS2Star();

        bool isNotVisible();

        inline const kmVec3 &getData() const
        { return mData; }

        void animate();
        void recycle(bool ontop);

    private:

        kmVec3 mData;
        float mSpeed;
    };

    class CS2BackgroundStars : public CS2EngineListener, public lite3dpp::Noncopiable
    {
    public:

        const int starsCount = 90;

        CS2BackgroundStars(CS2Game &game);

        void animate(int32_t firedPerRound, uint64_t deltaMs) override;
        void engineLoad() override;

    private:

        void loadStarsScene();
        void createStars();
        void syncStars();

        CS2Game &mGame;
        lite3dpp::Mesh *mStarsMesh;
        std::vector<CS2Star> mStars;
    };
}
