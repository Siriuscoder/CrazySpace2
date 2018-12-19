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
#include <cs2_game.h>
#include <cs2_stars.h>

namespace CS2
{
    CS2BackgroundStars::CS2BackgroundStars(CS2Game &game) :
        CS2EngineListener(game.getEngine()),
        mGame(game)
    {}

    void CS2BackgroundStars::engineLoad()
    {
        // load background assets here
        loadStarsScene();
        recycleStars();
    }

    void CS2BackgroundStars::animate(int32_t firedPerRound, uint64_t deltaMs)
    {
        // animate background here
    }

    void CS2BackgroundStars::loadStarsScene()
    {
        getEngine().getResourceManager()->queryResource<lite3dpp::Scene>("stars_scene",
            CS2Game::assetsScenePath("stars.json"));
    }

    void CS2BackgroundStars::recycleStars()
    {

    }
}