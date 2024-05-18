//
// Created by MFurmanczyk on 18/05/2024.
//

#include "MouseManager.h"
#include "../Application.h"
#include "SFML/Window/Event.hpp"

void MouseManager::addMapping(sf::Mouse::Button button, const MappingCallback& mappingFun)
{
    m_mappings.insert(std::make_pair(button, mappingFun));
}

void MouseManager::invokeMapping(sf::Event::MouseButtonEvent buttonEvent)
{
    if(m_mappings.contains(buttonEvent.button))
    {
        auto callback = m_mappings[buttonEvent.button];
        auto relativeMousePosition = sf::Vector2i(buttonEvent.x, buttonEvent.y);
        callback(Application::instantiate(),relativeMousePosition);
    }
}

MouseManager::MouseManager()
{
    //Add your mappings here
    addMapping(sf::Mouse::Left, &Application::leftClick);
    addMapping(sf::Mouse::Right, &Application::rightClick);
}
