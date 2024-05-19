//
// Created by MFurmanczyk on 18/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_MOUSEMANAGER_H
#define EDURITHM_DIJKSTRA_MOUSEMANAGER_H

#include <map>
#include <functional>
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Event.hpp"

class Application;
typedef std::function<void(Application&, sf::Vector2i&)> MouseMappingCallback;

/**
 * This class is responsible for processing mouse input.
 */
class MouseManager
{
public:

    ///Add your bindings here.
    MouseManager();

    ///Calls function bound to the given button
    void invokeMapping(sf::Event::MouseButtonEvent _buttonEvent);

private:

    ///Adds binding for the given button
    void addMapping(sf::Mouse::Button _button, const MouseMappingCallback& _mappingFunc);

private:

    ///Stores bindings
    std::map<sf::Mouse::Button, MouseMappingCallback> m_mappings;
};


#endif //EDURITHM_DIJKSTRA_MOUSEMANAGER_H
