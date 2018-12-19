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
#include <cs2_background.h>

namespace CS2
{
    CS2Background::CS2Background(CS2Game &game) :
        CS2EngineListener(game.getEngine()),
        mGame(game)
    {}

    void CS2Background::engineLoad()
    {
        // load background assets here
        kmVec2 origin;
        mGame.calculateMainMenuMetrics(origin, mResolution);

        loadRenderTarget(1);
        loadEnvScene();
        loadStarsScene();
        setupCamera();
    }

    void CS2Background::animate(int32_t firedPerRound, uint64_t deltaMs)
    {
        // animate background here
    }

    void CS2Background::loadEnvScene()
    {
        lite3dpp::ConfigurationWriter meshParams;
        meshParams.set(L"Model", L"Plain")
            .set(L"PlainSize", CS2Game::gameDimensions);

        getEngine().getResourceManager()->queryResourceFromJson<lite3dpp::Mesh>("env_plane.mesh", meshParams.write());
        getEngine().getResourceManager()->queryResource<lite3dpp::Scene>("env_scene",
            CS2Game::assetsScenePath("env.json"));
    }

    void CS2Background::loadStarsScene()
    {

    }

    void CS2Background::loadRenderTarget(int samples)
    {
        lite3dpp::ConfigurationWriter rtParams;
        lite3dpp::ConfigurationWriter caParams;
        kmVec4 backcolor = { 0.6, 0.6, 0.3, 1.0 };

        if (samples > 1)
        {
            caParams.set(L"Renderbuffer", true);
        }
        else
        {
            std::vector<lite3dpp::ConfigurationWriter> caArray;
            lite3dpp::ConfigurationWriter caTextureParams;

            caTextureParams.set(L"TextureName", "game_output.texture");
            caArray.push_back(caTextureParams);
            caParams.set(L"Attachments", caArray);
        }

        rtParams.set(L"Width", mResolution.x)
            .set(L"Height", mResolution.y)
            .set(L"BackgroundColor", backcolor)
            .set(L"Priority", 1)
            .set(L"CleanColorBuf", true)
            .set(L"CleanDepthBuf", true)
            .set(L"CleanStencilBuf", false)
            .set(L"MSAA", samples)
            .set(L"DepthAttachments", lite3dpp::ConfigurationWriter()
                .set(L"Renderbuffer", true))
            .set(L"ColorAttachments", caParams);

        if (samples > 1)
        {
            loadResolveRenderTarget();

            rtParams.set(L"BlitResultTo", lite3dpp::ConfigurationWriter()
                .set(L"Name", "multisample_resolve.target"));
        }

        getEngine().getResourceManager()->queryResourceFromJson<lite3dpp::TextureRenderTarget>("game_render.target",
            rtParams.write());
    }

    void CS2Background::loadResolveRenderTarget()
    {
        lite3dpp::ConfigurationWriter mrParams;
        lite3dpp::ConfigurationWriter caTextureParams;
        std::vector<lite3dpp::ConfigurationWriter> caArray;
        lite3dpp::ConfigurationWriter caParams;

        caTextureParams.set(L"TextureName", "game_output.texture");
        caArray.push_back(caTextureParams);
        caParams.set(L"Attachments", caArray);

        mrParams.set(L"Width", mResolution.x)
            .set(L"Height", mResolution.y)
            .set(L"Priority", -1)
            .set(L"CleanColorBuf", false)
            .set(L"CleanDepthBuf", false)
            .set(L"CleanStencilBuf", false)
            .set(L"ColorAttachments", caParams);

        getEngine().getResourceManager()->queryResourceFromJson<lite3dpp::TextureRenderTarget>("multisample_resolve.target", 
            mrParams.write());
    }

    void CS2Background::setupCamera()
    {
        lite3dpp::Camera *gameCamera = getEngine().getCamera("game_camera");
        gameCamera->setupOrtho(0, 200, 0, CS2Game::gameDimensions.x, -CS2Game::gameDimensions.y, 0);

        kmVec3 cameraPos = { 0, 0, 190 };
        gameCamera->setPosition(cameraPos);
        gameCamera->lookAt(KM_VEC3_ZERO);
    }
}