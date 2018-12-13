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
#include <lite3dpp_font/lite3dpp_font_texture.h>

#include <cs2_common.h>

namespace CS2
{
    class CS2Widget : public lite3dpp::Noncopiable
    {
    public:

        using MouseEventHandler = std::function<void(CS2Widget *, const kmVec2 &)>;

        CS2Widget(const std::string &name, lite3dpp::Scene &scene, const kmVec2 &origin, 
            const kmVec2 &size, CS2Widget *parent = nullptr);
        virtual ~CS2Widget();


        inline const std::string &getName() const
        { return mName; }
        inline lite3dpp::SceneObject *getObject()
        { return mWidgetObject; }
        inline const kmVec3 &getOrigin() const
        { return mOrigin; }
        inline const kmVec2 &getSize() const
        { return mSize; }

        void setOrigin(const kmVec2 &origin);

        void show();
        void hide();

        virtual void processEvent(SDL_Event *sysevent);

        inline void setWidgetMouseClickHandler(const MouseEventHandler &handler)
        { mMouseClickHandler = handler; }
        inline void setWidgetMouseMoveHandler(const MouseEventHandler &handler)
        { mMouseMoveHandler = handler; }
        inline void setWidgetMouseEnterHandler(const MouseEventHandler &handler)
        { mMouseEnterHandler = handler; }
        inline void setWidgetMouseLeaveHandler(const MouseEventHandler &handler)
        { mMouseLeaveHandler = handler; }


    protected:

        void addChild(CS2Widget *widget);
        void removeChild(CS2Widget *widget);

        virtual void onWidgetMouseClick(const kmVec2 &mousePos);
        virtual void onWidgetMouseMove(const kmVec2 &mousePos);
        virtual void onWidgetMouseEnter(const kmVec2 &mousePos);
        virtual void onWidgetMouseLeave(const kmVec2 &mousePos);

        std::string mName;
        lite3dpp::Scene &mScene;
        kmVec3 mOrigin;
        kmVec2 mSize;
        CS2Widget *mParent;
        std::map<std::string, CS2Widget *> mChilds;
        lite3dpp::SceneObject *mWidgetObject;
        bool mIsMouseCursorUnderWidget;
        MouseEventHandler mMouseClickHandler;
        MouseEventHandler mMouseMoveHandler;
        MouseEventHandler mMouseEnterHandler;
        MouseEventHandler mMouseLeaveHandler;
    };

    class CS2Panel : public CS2Widget
    {
    public:

        CS2Panel(const std::string &name, lite3dpp::Scene &scene, const kmVec2 &origin,
            const kmVec2 &size, const kmVec4 &color, CS2Widget *parent = nullptr);

        ~CS2Panel();

        void setPanelColor(const kmVec4 &color);

    protected:

        lite3dpp::Material *mMaterial;
        kmVec4 mPanelColor;
    };

    class CS2Button : public CS2Widget
    {
    public:

        CS2Button(const std::string &name, lite3dpp::Scene &scene, const kmVec2 &origin,
            const kmVec2 &size, const std::string &text, const std::string &font,
            const kmVec4 &buttonColor, const kmVec4 &fontColor, int fontSize, CS2Widget *parent = nullptr);

        void setButtonColor(const kmVec4 &color);
        void setFontColor(const kmVec4 &color);
        void refreshText();

        ~CS2Button();

    protected:

        std::string mText;
        lite3dpp::lite3dpp_font::FontTexture *mFontTexture;
        kmVec4 mButtonColor;
        kmVec4 mFontColor;
    };
}
