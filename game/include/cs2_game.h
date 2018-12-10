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
#include <cs2_background.h>
#include <cs2_main_menu.h>

namespace CS2
{
    class CS2Game
    {
    public:

        CS2Game();

        void initGame();
        void configure(const std::vector<std::string> &args);
        void startGame();
        void finishGame();

        lite3dpp::Main &getEngine()
        { return *mEngine; }
        const lite3dpp::Main &getEngine() const 
        { return *mEngine; }

        void calculateGameResolution(int &w, int &h) const;

    private:

        std::unique_ptr<lite3dpp::Main> mEngine;
        std::unique_ptr<CS2MainMenu> mMainMenu;
        std::unique_ptr<CS2Background> mBackground;
    };
}
