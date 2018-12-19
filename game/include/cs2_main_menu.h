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
#include <cs2_widgets.h>

namespace CS2
{
    class CS2MainMenu : public CS2EngineListener, public lite3dpp::Noncopiable
    {
    public:

        const float ButtonRelatedXSize = 0.8f;
        const float ButtonHeight = 50;
        const kmVec4 PanelColor = { 0.2, 0.2, 0.2, 0.4 };
        const kmVec4 ButtonInActiveColor = { 0.8, 0.2, 0.2, 0.4 };
        const kmVec4 ButtonActiveColor = { 0.2, 0.8, 0.2, 0.4 };
        const kmVec4 TextColor = { 0.8, 0.8, 0.8, 1 };

    public:

        CS2MainMenu(CS2Game &game);

        void animate(int32_t firedPerRound, uint64_t deltaMs) override;
        void engineLoad() override;
        void engineStops() override;

        bool menuIsVisible() const;
        void showMenu(bool resumeButton);
        void hideMenu();

    protected:
        
        void createMenu();
        void setupCamera();
        void loadOutputTexture();
        void processEvent(SDL_Event *e) override;

    private:

        CS2Game &mGame;
        lite3dpp::Scene *mMainMenuScene;
        kmVec2 mResolution;
        kmVec2 mOrigin;

        std::unique_ptr<CS2Panel> mDrawPanel;
        std::unique_ptr<CS2Panel> mMenuPanel;
        std::unique_ptr<CS2Button> mMenuButtonNewGame;
        std::unique_ptr<CS2Button> mMenuButtonResume;
        std::unique_ptr<CS2Button> mMenuButtonExit;
    };
}
