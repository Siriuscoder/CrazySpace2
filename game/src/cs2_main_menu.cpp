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
        mGame(game),
        mMainMenuScene(nullptr)
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
        show(false);
    }

    void CS2MainMenu::createMenu()
    {
        kmVec2 resolution, origin, buttonSize;
        kmVec4 background = { 0.2, 0.2, 0.2, 0.4 };
        mGame.calculateGameAreaMetrics(resolution, origin);

        buttonSize.x = resolution.x * ButtonRelatedXSize;
        buttonSize.y = ButtonHeight;

        mMenuPanel.reset(new CS2Panel("menu_panel", *mMainMenuScene, origin, resolution));
        mMenuButtonNewGame.reset(new CS2Button("menu_button_new_game", *mMainMenuScene, origin, buttonSize, "New Game",
            "cs2:fonts/arial.ttf", background, 16, mMenuPanel.get()));
        mMenuButtonResume.reset(new CS2Button("menu_button_resume", *mMainMenuScene, origin, buttonSize, "Resume",
            "cs2:fonts/arial.ttf", background, 14, mMenuPanel.get()));
        mMenuButtonExit.reset(new CS2Button("menu_button_exit", *mMainMenuScene, origin, buttonSize, "Exit",
            "cs2:fonts/arial.ttf", background, 14, mMenuPanel.get()));
    }

    void CS2MainMenu::engineStops()
    {
        mMenuButtonExit.reset();
        mMenuButtonResume.reset();
        mMenuButtonNewGame.reset();
        mMenuPanel.reset();
    }

    void CS2MainMenu::processEvent(SDL_Event *e)
    {
        if (e->type == SDL_KEYDOWN)
        {
            /* exit */
            if (e->key.keysym.sym == SDLK_ESCAPE)
                getEngine().stop();
        }

        // Post events to GUI
        if (mMenuPanel)
            mMenuPanel->processEvent(e);
    }

    bool CS2MainMenu::isVisible()
    {
        if (mMenuPanel)
            return mMenuPanel->getObject()->isEnabled();

        return false;
    }

    void CS2MainMenu::show(bool resumeButton)
    {
        if (mMenuPanel && mMenuButtonNewGame && mMenuButtonResume && mMenuButtonExit)
        {
            kmVec2 buttonOrigin;
            buttonOrigin.x = mMenuPanel->getSize().x * (1 - ButtonRelatedXSize) / 2;
            buttonOrigin.y = -ButtonHeight;

            mMenuPanel->show();

            mMenuButtonNewGame->show();
            mMenuButtonNewGame->setOrigin(buttonOrigin);

            if (resumeButton)
            {
                mMenuButtonResume->show();
                buttonOrigin.y -= ButtonHeight + 4;
                mMenuButtonResume->setOrigin(buttonOrigin);
            }

            mMenuButtonExit->show();
            buttonOrigin.y -= ButtonHeight + 4;
            mMenuButtonResume->setOrigin(buttonOrigin);
        }
    }

    void CS2MainMenu::hide()
    {
        if (mMenuPanel && mMenuButtonNewGame && mMenuButtonResume && mMenuButtonExit)
        {
            mMenuPanel->hide();
            mMenuButtonNewGame->hide();
            mMenuButtonResume->hide();
            mMenuButtonExit->hide();
        }
    }
}