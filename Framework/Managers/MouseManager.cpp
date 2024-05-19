//
// Created by MFurmanczyk on 18/05/2024.
//

#include "MouseManager.h"
#include "../../Application.h"

MouseManager::MouseManager()
{
    //Add your mappings here
    addMapping(sf::Mouse::Left, &Application::leftClick);
    addMapping(sf::Mouse::Right, &Application::rightClick);
}

void MouseManager::addMapping(sf::Mouse::Button _button, const MouseMappingCallback& _mappingFunc)
{
    m_mappings.insert(std::make_pair(_button, _mappingFunc));
}

void MouseManager::invokeMapping(sf::Event::MouseButtonEvent _buttonEvent)
{
    if(m_mappings.contains(_buttonEvent.button))
    {
        auto callback = m_mappings[_buttonEvent.button];
        auto relativeMousePosition = sf::Vector2i(_buttonEvent.x, _buttonEvent.y);
        callback(Application::instantiate(),relativeMousePosition);
    }
}