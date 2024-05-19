//
// Created by MFurmanczyk on 18/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_LEVEL_H
#define EDURITHM_DIJKSTRA_LEVEL_H

#include <vector>
#include <memory>
#include <type_traits>
#include "Actor.h"

/**
 * This class is responsible for storing and managing all object visible on the screen.
 */

class Level
{

public:

    virtual void update(float _deltaTime);
    virtual void draw(sf::RenderTarget& _target);

    ///Loads level from given file with respect to window size
    virtual void loadFromFile(std::string _filename, sf::Vector2u _windowSize);

    ///Spawns Actor instance in given level and in the given position
    template<ActorBase T>
    static std::shared_ptr<T> spawnActor(Level& _level, sf::Vector2i& _position)
    {
        return _level.spawnActor<T>(_position);
    }

    ///Spawns Actor subclass instance in current level and in the given position
    template<ActorBase T>
    std::shared_ptr<T> spawnActor(sf::Vector2i& _position)
    {
        std::shared_ptr<Actor> actor = Actor::createActor<T>();
        actor->setPosition(sf::Vector2f(_position));
        addActor(actor);
        return dynamic_pointer_cast<T>(actor);
    };

    //
    void resetDestinationPoints();

private:

    ///Adds actor to <m_actors> vector making it usable by the level
    virtual void addActor(std::shared_ptr<Actor>& _actor);


private:

    ///Stores all Actors present in the level
    std::vector<std::shared_ptr<Actor>> m_actors;
};

#endif //EDURITHM_DIJKSTRA_LEVEL_H
