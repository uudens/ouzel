// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "MainMenu.h"
#include "SpritesSample.h"
#include "GUISample.h"
#include "RTSample.h"
#include "AnimationsSample.h"
#include "InputSample.h"

using namespace std;
using namespace ouzel;

MainMenu::MainMenu(Application& app):
    application(app)
{
    eventHandler = make_shared<EventHandler>();

    eventHandler->uiHandler = bind(&MainMenu::handleUI, this, placeholders::_1, placeholders::_2, placeholders::_3);

    sharedEngine->getEventDispatcher()->addEventHandler(eventHandler);
    
    scene::LayerPtr layer = make_shared<scene::Layer>();
    addLayer(layer);

    layer->setCamera(make_shared<scene::Camera>());

    spritesButton = gui::Button::create("button.png", "button.png", "button_down.png", "", "Sprites", graphics::Color(20, 0, 0, 255), "arial.fnt");
    spritesButton->setPosition(Vector2(0.0f, 80.0f));
    layer->addChild(spritesButton);

    GUIButton = gui::Button::create("button.png", "button.png", "button_down.png", "", "GUI", graphics::Color(20, 0, 0, 255), "arial.fnt");
    GUIButton->setPosition(Vector2(0.0f, 40.0f));
    layer->addChild(GUIButton);

    renderTargetButton = gui::Button::create("button.png", "button.png", "button_down.png", "", "Render target", graphics::Color(20, 0, 0, 255), "arial.fnt");
    renderTargetButton->setPosition(Vector2(0.0f, 0.0f));
    layer->addChild(renderTargetButton);

    animationsButton = gui::Button::create("button.png", "button.png", "button_down.png", "", "Animations", graphics::Color(20, 0, 0, 255), "arial.fnt");
    animationsButton->setPosition(Vector2(0.0f, -40.0f));
    layer->addChild(animationsButton);

    inputButton = gui::Button::create("button.png", "button.png", "button_down.png", "", "Input", graphics::Color(20, 0, 0, 255), "arial.fnt");
    inputButton->setPosition(Vector2(0.0f, -80.0f));
    layer->addChild(inputButton);
}

MainMenu::~MainMenu()
{
    sharedEngine->getEventDispatcher()->removeEventHandler(eventHandler);
}

bool MainMenu::handleUI(Event::Type type, const UIEvent& event, const VoidPtr& sender)
{
    OUZEL_UNUSED(event);

    if (type == Event::Type::UI_CLICK_NODE)
    {
        scene::ScenePtr newScene;

        if (sender == spritesButton)
        {
            newScene = make_shared<SpritesSample>(application);
        }
        else if (sender == GUIButton)
        {
            newScene = make_shared<GUISample>(application);
        }
        else if (sender == renderTargetButton)
        {
            newScene = make_shared<RTSample>(application);
        }
        else if (sender == animationsButton)
        {
            newScene = make_shared<AnimationsSample>(application);
        }
        else if (sender == inputButton)
        {
            newScene = make_shared<InputSample>(application);
        }

        if (newScene)
        {
            sharedEngine->getSceneManager()->setScene(newScene);
        }
    }

    return true;
}
