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
#include <cs2_engine_listener.h>

namespace CS2
{
    CS2EngineListener::CS2EngineListener(lite3dpp::Main &engine) :
        mEngine(engine)
    {
        mEngine.addObserver(this);
    }

    CS2EngineListener::~CS2EngineListener()
    {
        mEngine.removeObserver(this);
    }

    void CS2EngineListener::engineLoad()
    {}

    void CS2EngineListener::engineShut()
    {}

    void CS2EngineListener::animate(int32_t firedPerRound, uint64_t deltaMs)
    {}

    void CS2EngineListener::regularTimerTick(lite3d_timer *timerid)
    {}

    void CS2EngineListener::init()
    {
        engineLoad();
    }

    void CS2EngineListener::shut()
    {
        engineShut();
    }

    void CS2EngineListener::timerTick(lite3d_timer *timerid)
    {
        if (timerid == mEngine.getFixedUpdateTimer())
        {
            animate(timerid->firedPerRound, timerid->deltaMs);
        }
    }
}