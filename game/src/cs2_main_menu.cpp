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
        mGame.calculateMainMenuMetrics(mOrigin, mResolution);
        getEngine().window()->setBackgroundColor(KM_VEC4_ZERO);
        // load main menu assets here
        mMainMenuScene = getEngine().getResourceManager()->queryResource<lite3dpp::Scene>("main_menu_scene",
            CS2Game::assetsScenePath("main_menu.json"));

        loadOutputTexture(); // Used by draw_panel
        setupCamera();
        createMenu();
        hideMenu();
        showMenu(true);
    }

    void CS2MainMenu::loadOutputTexture()
    {
        lite3dpp::ConfigurationWriter gameOutputParams;
        gameOutputParams.set(L"TextureType", "2D")
            .set(L"Filtering", "None")
            .set(L"Wrapping", "ClampToEdge")
            .set(L"Compression", false)
            .set(L"TextureFormat", "RGBA")
            .set(L"Width", mResolution.x)
            .set(L"Height", mResolution.y);

        getEngine().getResourceManager()->queryResourceFromJson<lite3dpp::TextureImage>("game_output.texture",
            gameOutputParams.write());
    }

    void CS2MainMenu::createMenu()
    {
        kmVec2 buttonSize = {
            mResolution.x * ButtonRelatedXSize,
            ButtonHeight
        };

        mDrawPanel.reset(new CS2Panel("draw_panel", *mMainMenuScene, mOrigin, mResolution, PanelColor));
        mMenuPanel.reset(new CS2Panel("menu_panel", *mMainMenuScene, mOrigin, mResolution, PanelColor, mDrawPanel.get()));
        mMenuButtonNewGame.reset(new CS2Button("menu_button_new_game", *mMainMenuScene, mOrigin, buttonSize, "NEW GAME",
            CS2Game::assetMenuFont(), ButtonInActiveColor, TextColor, 16, mMenuPanel.get()));
        mMenuButtonResume.reset(new CS2Button("menu_button_resume", *mMainMenuScene, mOrigin, buttonSize, "RESUME",
            CS2Game::assetMenuFont(), ButtonInActiveColor, TextColor, 14, mMenuPanel.get()));
        mMenuButtonExit.reset(new CS2Button("menu_button_exit", *mMainMenuScene, mOrigin, buttonSize, "EXIT",
            CS2Game::assetMenuFont(), ButtonInActiveColor, TextColor, 14, mMenuPanel.get()));

        auto onMouseEnter = [this](CS2Widget *w, const kmVec2 &pos)
        {
            CS2Button *button = static_cast<CS2Button *>(w);
            button->setButtonColor(ButtonActiveColor);
        };

        auto onMouseLeave = [this](CS2Widget *w, const kmVec2 &pos)
        {
            CS2Button *button = static_cast<CS2Button *>(w);
            button->setButtonColor(ButtonInActiveColor);
        };

        mMenuButtonNewGame->setWidgetMouseEnterHandler(onMouseEnter);
        mMenuButtonResume->setWidgetMouseEnterHandler(onMouseEnter);
        mMenuButtonExit->setWidgetMouseEnterHandler(onMouseEnter);
        mMenuButtonNewGame->setWidgetMouseLeaveHandler(onMouseLeave);
        mMenuButtonResume->setWidgetMouseLeaveHandler(onMouseLeave);
        mMenuButtonExit->setWidgetMouseLeaveHandler(onMouseLeave);

        mMenuButtonNewGame->setWidgetMouseClickHandler([this](CS2Widget *, const kmVec2 &)
        {
            mGame.newGame();
        });

        mMenuButtonResume->setWidgetMouseClickHandler([this](CS2Widget *, const kmVec2 &)
        {
            mGame.resumeGame();
        });

        mMenuButtonExit->setWidgetMouseClickHandler([this](CS2Widget *, const kmVec2 &)
        {
            mGame.exitGame();
        });
    }

    void CS2MainMenu::setupCamera()
    {
        lite3dpp::Camera *menuCamera = getEngine().getCamera("main_menu_camera");
        menuCamera->setupOrtho(0, 100, 0, getEngine().window()->width(),
            -getEngine().window()->height(), 0);

        kmVec3 cameraPos = { 0, 0, 90 };
        menuCamera->setPosition(cameraPos);
        menuCamera->lookAt(KM_VEC3_ZERO);
    }

    void CS2MainMenu::engineStops()
    {
        mMenuButtonExit.reset();
        mMenuButtonResume.reset();
        mMenuButtonNewGame.reset();
        mMenuPanel.reset();
        mDrawPanel.reset();
    }

    void CS2MainMenu::processEvent(SDL_Event *e)
    {
        if (e->type == SDL_KEYDOWN)
        {
            if (e->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                showMenu(true);
            }
        }

        // Post events to root widget
        if (mDrawPanel)
            mDrawPanel->processEvent(e);
    }

    bool CS2MainMenu::menuIsVisible() const
    {
        if (mMenuPanel)
            return mMenuPanel->getObject()->isEnabled();

        return false;
    }

    void CS2MainMenu::showMenu(bool resumeButton)
    {
        assert(mDrawPanel);
        assert(mMenuPanel);
        assert(mMenuButtonNewGame);
        assert(mMenuButtonResume);
        assert(mMenuButtonExit);

        kmVec2 buttonOrigin;
        kmVec2 menuOrigin = { 0, 0 };
        buttonOrigin.x = mMenuPanel->getSize().x * (1 - ButtonRelatedXSize) / 2;
        buttonOrigin.y = -ButtonHeight;

        mMenuPanel->show();
        mMenuPanel->setOrigin(menuOrigin);

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
        mMenuButtonExit->setOrigin(buttonOrigin);
    }

    void CS2MainMenu::hideMenu()
    {
        assert(mDrawPanel);
        assert(mMenuPanel);
        assert(mMenuButtonNewGame);
        assert(mMenuButtonResume);
        assert(mMenuButtonExit);

        mMenuPanel->hide();
        mMenuButtonNewGame->hide();
        mMenuButtonResume->hide();
        mMenuButtonExit->hide();
    }
}