//
// Created by MFurmanczyk on 19/05/2024.
//

#include "KeyboardManager.h"
#include "../../Application.h"

KeyboardManager::KeyboardManager()
{
    addMapping(sf::Keyboard::Escape, &Application::closeApplication);
    addMapping(sf::Keyboard::R, &Application::resetLevel);
}

void KeyboardManager::invokeMapping(sf::Event::KeyEvent _keyEvent)
{
    if(m_mappings.contains(_keyEvent.code))
    {
        auto callback = m_mappings[_keyEvent.code];
        callback(Application::instantiate());
    }
}

void KeyboardManager::addMapping(sf::Keyboard::Key _key, const KeyboardMappingCallback &mappingFunc)
{
    m_mappings.insert(std::make_pair(_key, mappingFunc));
}
