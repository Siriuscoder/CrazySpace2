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
#include <cs2_main_menu.h>

namespace CS2
{
    CS2MainMenu::CS2MainMenu(CS2Game &game) :
        CS2EngineListener(game.getEngine()),
        mGame(game)
    {}

    void CS2MainMenu::animate(int32_t firedPerRound, uint64_t deltaMs)
    {
        // animate main menu here
    }

    void CS2MainMenu::engineLoad()
    {
        getEngine().window()->setBackgroundColor(KM_VEC4_ZERO);
        // load main menu assets here
        mMainMenuScene = getEngine().getResourceManager()->queryResource<lite3dpp::Scene>("main_menu_scene",
            "cs2:scenes/main_menu.json");

        createMenu();
    }

    void CS2MainMenu::createMenu()
    {
        kmVec2 resolution, origin;
        mGame.calculateGameAreaMetrics(resolution, origin);

        lite3dpp::ConfigurationWriter panelJson;
        panelJson.set(L"Model", L"Plane")
            .set(L"PlainSize", resolution);

        lite3dpp::ConfigurationWriter buttonJson;
        buttonJson.set(L"Model", L"Plane")
            .set(L"PlainSize", resolution);

        // Preload menu and button mesh
        getEngine().getResourceManager()->queryResourceFromJson<lite3dpp::Mesh>("menu.mesh", panelJson.write());
        getEngine().getResourceManager()->queryResourceFromJson<lite3dpp::Mesh>("menu_button.mesh", buttonJson.write());

    }

    void CS2MainMenu::processEvent(SDL_Event *e)
    {
        if (e->type == SDL_KEYDOWN)
        {
            /* exit */
            if (e->key.keysym.sym == SDLK_ESCAPE)
                getEngine().stop();
        }
    }
}