//
// Created by MFurmanczyk on 18/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_LEVEL_H
#define EDURITHM_DIJKSTRA_LEVEL_H

#include <vector>
#include <memory>
#include <type_traits>
#include "Actor.h"
#include "../Algorithm/Graph.h"

/**
 * This class is responsible for storing and managing all object visible on the screen.
 */
class Level
{

public:

    virtual void update(float _deltaTime);
    virtual void draw(sf::RenderTarget& _target);

    ///Loads level from given file and ceates underlying connection graph with respect to window size.
    virtual void loadFromFile(std::string _mapFilename, std::string _connectionFilename, sf::Vector2u _windowSize);

    ///Spawns Actor instance in given level and in the given position.
    template<ActorBase T>
    static std::shared_ptr<T> spawnActor(Level& _level, sf::Vector2f& _position)
    {
        return _level.spawnActor<T>(_position);
    }

    ///Spawns Actor subclass instance in current level and in the given position.
    template<ActorBase T>
    std::shared_ptr<T> spawnActor(sf::Vector2f& _position)
    {
        std::shared_ptr<Actor> actor = Actor::createActor<T>();
        actor->setPosition(_position);
        addActor(actor);
        return dynamic_pointer_cast<T>(actor);
    };

    ///
    void resetDestinationPoints();

private:

    ///Adds actor to <m_actors> vector making it usable by the level.
    virtual void addActor(std::shared_ptr<Actor>& _actor);
    ///Removes actor from the level.
    virtual void removeActor(Actor* _actor);

    ///Loads and creates map.
    void loadMap(const std::string &_mapFilename, const sf::Vector2u &_windowSize);
    ///Loads and creates connections in underlying graph from given file.
    void loadConnections(const std::string &_connectionFilename);
    ///Creates tiles and graph verticesCount for given row.
    void processRow(sf::Vector2f &tileSize, std::string &line, int row);


private:

    ///Stores all Actors present in the level.
    std::vector<std::shared_ptr<Actor>> m_actors;
    ///Underlying navigation graph.
    Graph                               m_graph;

};

#endif //EDURITHM_DIJKSTRA_LEVEL_H
