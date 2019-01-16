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
    class CS2GameObject
    {
    public:

        CS2GameObject(lite3dpp::Scene &scene, const std::string &name, 
            const std::string &templatePath, CS2GameObject *parent = nullptr);

        inline const kmVec3 &getPosition() const
        {
            assert(mSceneObject);
            mSceneObject->getRoot()->getPtr()->position;
        }

        inline const lite3d_bounding_vol &getBBox() const
        {
            return mBBox;
        }

        void setPosition(const kmVec3 &pos);
        /* move relative to object orientation */
        void moveRelative(const kmVec3 &v);
        /* rotate around world axis */
        void rotateAngle(const kmVec3 &axis, float angle);
        /* set rotation */
        void setRotation(const kmVec3 &axis, float angle);

        /* update bounding box used to detect objects collision */
        void updateBBox();
        /* check object near other object */
        virtual bool checkCollision(const CS2GameObject &obj);

    protected:

        lite3dpp::SceneObject *mSceneObject;
        lite3d_bounding_vol mBBox;
        lite3dpp::Scene &mScene;
    };
}
