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
        mWidgetObject(nullptr)
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
        if (sysevent->type == SDL_MOUSEMOTION)
        {
            SDL_Event relevent = *sysevent;
            relevent.motion.x = relevent.motion.x - mOrigin.x;
            relevent.motion.y = relevent.motion.y + mOrigin.y;

            kmVec2 mouseRelativePos = {
                static_cast<float>(relevent.motion.x),
                static_cast<float>(relevent.motion.y)
            };
            onWidgetMouseMove(mouseRelativePos);
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

                    for (auto &w : mChilds)
                        w.second->processEvent(&relevent);
                }
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
        if (mousePos.x >= 0 && mousePos.x < mSize.x &&
            mousePos.y >= 0 && mousePos.y < mSize.y)
        {
            if (mMouseMoveHandler)
                mMouseMoveHandler(this, mousePos);
        }
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
        CS2Widget(name, scene, origin, size, parent)
    {
        mWidgetObject = scene.addObject(name, CS2Game::assetObjectsPath() + name + ".json", 
            parent ? parent->getObject() : nullptr);

        mWidgetObject->getRoot()->setPosition(mOrigin);

        // set panel color
        lite3dpp::Material *meterial = scene.getMain().getResourceManager()->
            queryResource<lite3dpp::Material>(name + ".material");
        meterial->setFloatv4Parameter(1, "color", color);
    }

    CS2Panel::~CS2Panel()
    {
        assert(mWidgetObject);

        mScene.getMain().getResourceManager()->releaseResource(mName + ".material");
        mScene.removeObject(mWidgetObject->getName());
    }

    CS2Button::CS2Button(const std::string &name, lite3dpp::Scene &scene, const kmVec2 &origin, const kmVec2 &size, 
        const std::string &text, const std::string &font, const kmVec4 &color, int fontSize, CS2Widget *parent) :
        CS2Widget(name, scene, origin, size, parent),
        mText(text),
        mFontTexture(nullptr)
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
            .set(L"BlankColor", color);

        // load button texture, font texture
        mFontTexture = scene.getMain().getResourceManager()->queryResourceFromJson<lite3dpp::lite3dpp_font::FontTexture>(
            name + ".texture", fontTextureParams.write());

        kmVec2 textPos = { 5, 5 };
        mFontTexture->clean();
        mFontTexture->drawText(mText, textPos, PassiveColor);
        mFontTexture->uploadChanges();

        mWidgetObject = scene.addObject(name, CS2Game::assetObjectsPath() + name + ".json", 
            parent ? parent->getObject() : nullptr);

        mWidgetObject->getRoot()->setPosition(mOrigin);
    }

    CS2Button::~CS2Button()
    {
        assert(mWidgetObject);

        mScene.getMain().getResourceManager()->releaseResource(mName + ".texture");
        mScene.getMain().getResourceManager()->releaseResource(mName + ".material");
        mScene.removeObject(mWidgetObject->getName());
    }

    void CS2Button::onWidgetMouseMove(const kmVec2 &mousePos)
    {
        CS2Widget::onWidgetMouseMove(mousePos);

        static bool active = false;
        bool current = mousePos.x >= 0 && mousePos.x < mSize.x && mousePos.y >= 0 && mousePos.y < mSize.y;
        
        if (active != current)
        {
            if (current)
            {
                kmVec2 textPos = { 5, 5 };
                mFontTexture->clean();
                mFontTexture->drawText(mText, textPos, ActiveColor);
                mFontTexture->uploadChanges();
            }
            else
            {
                kmVec2 textPos = { 5, 5 };
                mFontTexture->clean();
                mFontTexture->drawText(mText, textPos, PassiveColor);
                mFontTexture->uploadChanges();
            }

            active = current;
        }
    }
}