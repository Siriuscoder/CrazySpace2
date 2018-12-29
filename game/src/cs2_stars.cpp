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

#include <cs2_game.h>
#include <cs2_stars.h>
#include <cs2_utils.h>

namespace CS2
{
    CS2Star::CS2Star()
    {
        recycle(false);
    }

    void CS2Star::recycle(bool ontop)
    {
        mPos.x = CS2Math::random(CS2Game::gameDimensions.x);
        mPos.y = ontop ? -CS2Game::gameDimensions.y : -CS2Math::random(CS2Game::gameDimensions.y);
        mPos.z = 0;

        mSpeed = CS2Math::random_range(minSpeed, maxSpeed);
    }

    bool CS2Star::isNotVisible()
    {
        return mPos.y > 0;
    }

    void CS2Star::animate()
    {
        mPos.y += mSpeed;
    }

    CS2BackgroundStars::CS2BackgroundStars(CS2Game &game) :
        CS2EngineListener(game.getEngine()),
        mGame(game),
        mStarsMesh(nullptr)
    {}

    void CS2BackgroundStars::engineLoad()
    {
        // load background assets here
        createStars();
        loadStarsScene();
    }

    void CS2BackgroundStars::animate(int32_t firedPerRound, uint64_t deltaMs)
    {
        assert(mStarsMesh);

        // animate background here
        for (auto &star : mStars)
        {
            star.animate();
            // recycle stars
            if (star.isNotVisible())
            {
                star.recycle(true);
            }
        }

        syncStars();
    }

    void CS2BackgroundStars::loadStarsScene()
    {
        getEngine().getResourceManager()->queryResource<lite3dpp::Scene>("stars_scene",
            CS2Game::assetsScenePath("stars.json"));
    }

    void CS2BackgroundStars::createStars()
    {
        assert((starsCount % 3) == 0);
        // create empty mesh first
        mStarsMesh = getEngine().getResourceManager()->queryResourceFromJson<lite3dpp::Mesh>(
            "stars_particles.mesh", LITE3D_EMPTY_JSON);

        std::vector<kmVec3> initialPoints;
        for (int i = 0; i < starsCount; ++i)
        {
            mStars.emplace_back();
            initialPoints.push_back(mStars.back().getPos());
        }

        kmVec3 bbNull = {0, 0, 0};
        mStarsMesh->genArray(initialPoints, bbNull, bbNull, true);
    }

    void CS2BackgroundStars::syncStars()
    {
        assert(mStarsMesh);
        
        int i = 0;
        auto mapped = mStarsMesh->vertexBuffer().map(lite3dpp::BufferScopedMapper::LockTypeWrite);

        for (auto &star : mStars)
        {
            mapped.getPtr<kmVec3>()[i++] = star.getPos();
        }
    }
}
