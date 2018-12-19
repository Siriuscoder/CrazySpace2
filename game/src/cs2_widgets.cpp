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
#include <cs2_widgets.h>

namespace CS2
{
    CS2Widget::CS2Widget(const std::string &name, lite3dpp::Scene &scene, const kmVec2 &origin, 
        const kmVec2 &size, CS2Widget *parent) :
        mName(name),
        mScene(scene),
        mSize(size),
        mParent(parent),
        mWidgetObject(nullptr),
        mIsMouseCursorUnderWidget(false)
    {
        lite3dpp::ConfigurationWriter meshParams;
        meshParams.set(L"Model", L"Plain")
            .set(L"PlainSize", size);

        // Preload widget mesh simple plane
        scene.getMain().getResourceManager()->queryResourceFromJson<lite3dpp::Mesh>(name + ".mesh", meshParams.write());
        
        if (parent)
            parent->addChild(this);

        mOrigin.x = origin.x;
        mOrigin.y = origin.y;
        mOrigin.z = parent ? parent->mOrigin.z + 1.0 : 0.0;
    }

    CS2Widget::~CS2Widget()
    {
        if (mParent)
            mParent->removeChild(this);

        // unload widget mesh
        mScene.getMain().getResourceManager()->releaseResource(mName + ".mesh");
    }

    void CS2Widget::addChild(CS2Widget *widget)
    {
        auto it = mChilds.find(widget->getName());
        if (it != mChilds.end())
            LITE3D_THROW("Dublicate widget " << widget->getName());

        mChilds[widget->getName()] = widget;
    }

    void CS2Widget::removeChild(CS2Widget *widget)
    {
        auto it = mChilds.find(widget->getName());
        if (it == mChilds.end())
            LITE3D_THROW("Widget not found " << widget->getName());

        mChilds.erase(it);
    }

    void CS2Widget::processEvent(SDL_Event *sysevent)
    {
        if (mWidgetObject && !mWidgetObject->isEnabled())
            return;

        if (sysevent->type == SDL_MOUSEMOTION)
        {
            SDL_Event relevent = *sysevent;
            relevent.motion.x = relevent.motion.x - mOrigin.x;
            relevent.motion.y = relevent.motion.y + mOrigin.y;

            kmVec2 mouseRelativePos = {
                static_cast<float>(relevent.button.x),
                static_cast<float>(relevent.button.y)
            };

            if (relevent.button.x >= 0 && relevent.button.x < mSize.x &&
                relevent.button.y >= 0 && relevent.button.y < mSize.y)
            {
                onWidgetMouseMove(mouseRelativePos);

                if (!mIsMouseCursorUnderWidget)
                {
                    onWidgetMouseEnter(mouseRelativePos);
                    mIsMouseCursorUnderWidget = true;
                }
            }
            else
            {
                if (mIsMouseCursorUnderWidget)
                {
                    onWidgetMouseLeave(mouseRelativePos);
                    mIsMouseCursorUnderWidget = false;
                }
            }

            for (auto &w : mChilds)
                w.second->processEvent(&relevent);
        }
        else if (sysevent->type == SDL_MOUSEBUTTONUP)
        {
            if (sysevent->button.clicks == 1)
            {
                SDL_Event relevent = *sysevent;
                relevent.button.x = relevent.button.x - mOrigin.x;
                relevent.button.y = relevent.button.y + mOrigin.y;

                if (relevent.button.x >= 0 && relevent.button.x < mSize.x &&
                    relevent.button.y >= 0 && relevent.button.y < mSize.y)
                {
                    kmVec2 mouseRelativePos = {
                        static_cast<float>(relevent.button.x),
                        static_cast<float>(relevent.button.y)
                    };

                    onWidgetMouseClick(mouseRelativePos);
                }

                for (auto &w : mChilds)
                    w.second->processEvent(&relevent);
            }
        }
    }

    void CS2Widget::onWidgetMouseClick(const kmVec2 &mousePos)
    {
        if (mMouseClickHandler)
            mMouseClickHandler(this, mousePos);
    }

    void CS2Widget::onWidgetMouseMove(const kmVec2 &mousePos)
    {
        if (mMouseMoveHandler)
            mMouseMoveHandler(this, mousePos);
    }

    void CS2Widget::onWidgetMouseEnter(const kmVec2 &mousePos)
    {
        if (mMouseEnterHandler)
            mMouseEnterHandler(this, mousePos);
    }

    void CS2Widget::onWidgetMouseLeave(const kmVec2 &mousePos)
    {
        if (mMouseLeaveHandler)
            mMouseLeaveHandler(this, mousePos);
    }

    void CS2Widget::show()
    {
        mWidgetObject->enable();
    }

    void CS2Widget::hide()
    {
        mWidgetObject->disable();
    }

    void CS2Widget::setOrigin(const kmVec2 &origin)
    {
        assert(mWidgetObject);

        mOrigin.x = origin.x;
        mOrigin.y = origin.y;
        mWidgetObject->getRoot()->setPosition(mOrigin);
    }

    CS2Panel::CS2Panel(const std::string &name, lite3dpp::Scene &scene, const kmVec2 &origin, 
        const kmVec2 &size, const kmVec4 &color, CS2Widget *parent) :
        CS2Widget(name, scene, origin, size, parent),
        mMaterial(nullptr)
    {
        mWidgetObject = scene.addObject(name, CS2Game::assetObjectPath(name + ".json"),
            parent ? parent->getObject() : nullptr);

        mWidgetObject->getRoot()->setPosition(mOrigin);

        setPanelColor(color);
    }

    CS2Panel::~CS2Panel()
    {
        assert(mWidgetObject);

        mScene.getMain().getResourceManager()->releaseResource(mName + ".material");
        mScene.removeObject(mWidgetObject->getName());
    }

    void CS2Panel::setPanelColor(const kmVec4 &color)
    {
        if (!mMaterial)
            mMaterial = mScene.getMain().getResourceManager()->queryResource<lite3dpp::Material>(mName + ".material");

        mMaterial->setFloatv4Parameter(1, "color", color);
        mPanelColor = color;
    }

    CS2Button::CS2Button(const std::string &name, lite3dpp::Scene &scene, const kmVec2 &origin, const kmVec2 &size, 
        const std::string &text, const std::string &font, const kmVec4 &buttonColor, const kmVec4 &fontColor, 
        int fontSize, CS2Widget *parent) :
        CS2Widget(name, scene, origin, size, parent),
        mText(text),
        mFontTexture(nullptr),
        mButtonColor(buttonColor),
        mFontColor(fontColor)
    {
        lite3dpp::ConfigurationWriter fontTextureParams;
        fontTextureParams.set(L"TextureType", L"2D")
            .set(L"Filtering", "None")
            .set(L"Wrapping", "ClampToEdge")
            .set(L"Compression", false)
            .set(L"TextureFormat", "RGBA")
            .set(L"Width", size.x)
            .set(L"Height", size.y)
            .set(L"Font", font)
            .set(L"FontSize", fontSize)
            .set(L"BlankColor", buttonColor);

        // load button texture, font texture
        mFontTexture = scene.getMain().getResourceManager()->queryResourceFromJson<lite3dpp::lite3dpp_font::FontTexture>(
            name + ".texture", fontTextureParams.write());

        mWidgetObject = scene.addObject(name, CS2Game::assetObjectPath(name + ".json"), 
            parent ? parent->getObject() : nullptr);

        mWidgetObject->getRoot()->setPosition(mOrigin);

        refreshText();
    }

    void CS2Button::setButtonColor(const kmVec4 &color)
    {
        mButtonColor = color;
        refreshText();
    }

    void CS2Button::setFontColor(const kmVec4 &color)
    {
        mFontColor = color;
        refreshText();
    }

    void CS2Button::refreshText()
    {
        kmVec2 textPos = { 5, 5 };
        mFontTexture->clean(mButtonColor);
        mFontTexture->drawText(mText, textPos, mFontColor);
        mFontTexture->uploadChanges();
    }

    CS2Button::~CS2Button()
    {
        assert(mWidgetObject);

        mScene.getMain().getResourceManager()->releaseResource(mName + ".texture");
        mScene.getMain().getResourceManager()->releaseResource(mName + ".material");
        mScene.removeObject(mWidgetObject->getName());
    }
}