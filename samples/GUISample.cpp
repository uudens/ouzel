// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "GUISample.h"

using namespace std;
using namespace ouzel;

GUISample::GUISample(Application& app):
    application(app)
{
    eventHandler = make_shared<EventHandler>();
    eventHandler->uiHandler = bind(&GUISample::handleUI, this, placeholders::_1, placeholders::_2, placeholders::_3);
    sharedEngine->getEventDispatcher()->addEventHandler(eventHandler);

    scene::LayerPtr layer = make_shared<scene::Layer>();
    addLayer(layer);
    layer->setCamera(make_shared<scene::Camera>());

    button = gui::Button::create("button.png", "button.png", "button_down.png", "", "Button", graphics::Color(255, 0, 0, 255), "arial.fnt");
    button->setPosition(Vector2(-200.0f, 100.0f));
    layer->addChild(button);
    
    checkBox = gui::CheckBox::create("checkbox.png", "", "", "", "tick.png");
    checkBox->setPosition(Vector2(-100.0f, 100.0f));
    layer->addChild(checkBox);

    gui::LabelPtr label = gui::Label::create("arial.fnt", "label");
    label->setColor(graphics::Color(0, 255, 255, 255));
    label->setPosition(Vector2(-70.0f, 100.0f));
    layer->addChild(label);

    sharedEngine->getLocalization()->addLanguage("latvian", "lv.mo");
    sharedEngine->getLocalization()->setLanguage("latvian");

    gui::LabelPtr label2 = gui::Label::create("font.fnt", sharedEngine->getLocalization()->getString("Test"));
    layer->addChild(label2);

    scene::LayerPtr guiLayer = make_shared<scene::Layer>();
    guiLayer->setCamera(make_shared<scene::Camera>());
    addLayer(guiLayer);

    backButton = gui::Button::create("button.png", "button.png", "button_down.png", "", "Back", graphics::Color(0, 0, 0, 255), "arial.fnt");
    backButton->setPosition(Vector2(-200.0f, -200.0f));
    guiLayer->addChild(backButton);
}

GUISample::~GUISample()
{
    sharedEngine->getEventDispatcher()->removeEventHandler(eventHandler);
}

bool GUISample::handleUI(Event::Type type, const UIEvent& event, const VoidPtr& sender) const
{
    OUZEL_UNUSED(event);

    if (type == Event::Type::UI_CLICK_NODE && sender == backButton)
    {
        application.back();
    }

    return true;
}
