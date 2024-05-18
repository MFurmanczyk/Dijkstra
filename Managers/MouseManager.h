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

typedef std::function<void(Application&, sf::Vector2i&)> MappingCallback;

/*
 * This class is responsible for processing mouse input.
 */

class MouseManager
{
public:

    MouseManager();
    void invokeMapping(sf::Event::MouseButtonEvent buttonEvent);

private:

    void addMapping(sf::Mouse::Button button, const MappingCallback& mappingFunc);

private:

    std::map<sf::Mouse::Button, MappingCallback> m_mappings;
};


#endif //EDURITHM_DIJKSTRA_MOUSEMANAGER_H
