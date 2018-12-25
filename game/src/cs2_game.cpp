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
#include <ctime>

#include <cs2_game.h>

namespace CS2
{
    const float CS2Game::WindowAspect = 2.0f;

    const kmVec2 CS2Game::gameDimensions = { 50.0, 100.0 };

    const std::string CS2Game::assetPackageName()
    {
        return "cs2";
    }

    const std::string CS2Game::assetObjectPath(const std::string &name)
    {
        return assetPackageName() + ":objects/" + name;
    }

    const std::string CS2Game::assetsScenePath(const std::string &name)
    {
        return assetPackageName() + ":scenes/" + name;
    }

    const std::string CS2Game::assetMenuFont()
    {
        return assetPackageName() + ":fonts/arial.ttf";
    }

    void CS2Game::calculateMainMenuMetrics(kmVec2 &origin, kmVec2 &resolution)
    {
        assert(getEngine().window());
        // Get real windows size
        int rwidth = getEngine().window()->width();
        int rheight = getEngine().window()->height();

        if (rwidth > rheight)
        {
            resolution.x = rheight / WindowAspect;
            resolution.y = rheight;
        }
        else
        {
            if (rwidth * WindowAspect > rheight)
            {
                resolution.x = rheight / WindowAspect;
                resolution.y = rheight;
            }
            else
            {
                resolution.x = rwidth;
                resolution.y = rwidth * WindowAspect;
            }
        }

        origin.x = (rwidth - resolution.x) / 2.0f;
        origin.y = 0.0f;
    }

    void CS2Game::init()
    {
        // use current time as seed for random generator
        std::srand(std::time(nullptr));

        mEngine.reset(new lite3dpp::Main());
        mMainMenu.reset(new CS2MainMenu(*this));
        mBackground.reset(new CS2Background(*this));
        mBackgroundStars.reset(new CS2BackgroundStars(*this));
    }

    void CS2Game::configure(const std::vector<std::string> &args)
    {
        int logLevel = 1;
        bool fullscreen = false;
        bool logtofile = false;
        for (const std::string &s : args)
        {
            if (s == "-v")
                logLevel = 2;
            else if (s == "-vv")
                logLevel = 3;
            else if (s == "-f")
                fullscreen = true;
            else if (s == "-l")
                logtofile = true;
            else if (s == "-h")
            {
                LITE3D_THROW("help:" << std::endl
                    << "\t-v:  verbose output" << std::endl
                    << "\t-vv: debug output" << std::endl
                    << "\t-l:  save output to log file" << std::endl
                    << "\t-f:  fullscreen" << std::endl
                    << "\t-h:  print help" << std::endl);
            }
        }

        lite3dpp::ConfigurationWriter reslocation;
        reslocation.set(L"Name", assetPackageName())
            .set(L"Path", L"cs2/")
            .set(L"FileCacheMaxSize", 0xA00000);

        lite3dpp::stl<lite3dpp::ConfigurationWriter>::vector reslocationArr;
        reslocationArr.push_back(reslocation);

        lite3dpp::String json = lite3dpp::ConfigurationWriter().set(L"LogLevel", logLevel)
            .set(L"logMuteStd", logLevel == 1)
            .set(L"LogFile", logtofile ? "cs2.log" : "")
            .set(L"LogFlushAlways", false)
            .set(L"FixedUpdatesInterval", 30)
            .set(L"Minidump", true)
            .set(L"VideoSettings", lite3dpp::ConfigurationWriter()
                .set(L"Width", fullscreen ? 0 : 1024)
                .set(L"Height", fullscreen ? 0 : 768)
                .set(L"Caption", L"CrazySpace2")
                .set(L"ColorBits", 24)
                .set(L"Fullscreen", fullscreen)
                .set(L"FSAA", 1)
                .set(L"VSync", true))
            .set(L"TextureSettings", lite3dpp::ConfigurationWriter()
                .set(L"Anisotropy", 8)
                .set(L"Compression", true))
            .set(L"ResourceLocations", reslocationArr).write();

        mEngine->initFromConfigString(json.c_str());
    }

    void CS2Game::run()
    {
        mEngine->run();
    }

    void CS2Game::finish()
    {
        mBackgroundStars.reset();
        mBackground.reset();
        mMainMenu.reset();
        mEngine.reset();
    }

    void CS2Game::newGame()
    {
        mMainMenu->hideMenu();
    }

    void CS2Game::resumeGame()
    {
        mMainMenu->hideMenu();
    }

    void CS2Game::exitGame()
    {
        /* stop engine, unload all resources, exit from main loop */
        mEngine->stop();
    }
}