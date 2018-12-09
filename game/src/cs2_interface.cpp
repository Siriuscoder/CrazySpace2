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
#include <iostream>

#include <cs2_interface.h>
#include <cs2_game.h>

std::unique_ptr<CS2::CS2Game> gameInstance;

int cs2_init()
{
    try
    {
        gameInstance.reset(new CS2::CS2Game());
        gameInstance->initGame();
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

    return 0;
}

int cs2_start(int count, char *args[])
{
    if (!gameInstance)
    {
        std::cerr << "Not inited yet, call cs2_init first" << std::endl;
        return -1;
    }

    try
    {
        std::vector<std::string> commandLine;
        for (int i = 0; i < count; ++i)
            commandLine.push_back(args[i]);

        gameInstance->configure(commandLine);
        gameInstance->startGame();
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

    return 0;
}

int cs2_finalize()
{
    gameInstance->finishGame();
    gameInstance.reset();
    return 0;
}