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

namespace CS2
{
    CS2Game::CS2Game()
    {}

    void CS2Game::initGame()
    {
        mEngine.reset(new lite3dpp::Main());
        mEngine->addObserver(this);
    }

    void CS2Game::configure(std::vector<std::string> &args)
    {
        std::string json;
        mEngine->initFromConfigString(json.c_str());
    }

    void CS2Game::startGame()
    {
        mEngine->run();
    }
}