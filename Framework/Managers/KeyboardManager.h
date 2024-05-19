//
// Created by MFurmanczyk on 19/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_KEYBOARDMANAGER_H
#define EDURITHM_DIJKSTRA_KEYBOARDMANAGER_H

#include <map>
#include <functional>
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Event.hpp"

class Application;
typedef std::function<void(Application&)> KeyboardMappingCallback;

/**
 * This class is responsible for processing keyboard input.
 */
class KeyboardManager
{
public:

    ///Add your bindings here.
    KeyboardManager();

    ///Calls function bound to the given key.
    void invokeMapping(sf::Event::KeyEvent _keyEvent);

private:

    ///Adds binding for the given key.
    void addMapping(sf::Keyboard::Key _key, const KeyboardMappingCallback& _mappingFunc);

private:

    ///Stores bindings.
    std::map<sf::Keyboard::Key, KeyboardMappingCallback> m_mappings;
};


#endif //EDURITHM_DIJKSTRA_KEYBOARDMANAGER_H
