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

#include <lite3dpp/lite3dpp_main.h>

#include <cs2_common.h>

namespace CS2
{
    class CS2EngineListener : protected lite3dpp::LifecycleObserver
    {
    public:

        CS2EngineListener(lite3dpp::Main &engine);
        ~CS2EngineListener();
        
        virtual void engineLoad();
        virtual void engineShut();
        virtual void animate(int32_t firedPerRound, uint64_t deltaMs);
        virtual void regularTimerTick(lite3d_timer *timerid);

        lite3dpp::Main &getEngine()
        { return mEngine; }
        const lite3dpp::Main &getEngine() const
        { return mEngine; }

    protected:

        void init() override final;
        void shut() override final;
        void timerTick(lite3d_timer *timerid) override final;

    private:

        lite3dpp::Main &mEngine;
    };
}
