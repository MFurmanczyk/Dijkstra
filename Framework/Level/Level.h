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
#include "../Algorithm/NearestNeighbor.h"
#include "Points/GraphPoint.h"
#include "../Algorithm/Dijkstra.h"
#include "Points/DestinationPoint.h"
#include "Path.h"

/**
 * This class is responsible for storing and managing all object visible on the screen.
 */
class Level
{

public:

    virtual void update(float _deltaTime);
    virtual void draw(sf::RenderTarget& _target);

    ///Loads level from given file and ceates underlying connection graph with respect to window size.
    virtual void loadFromFile(const std::string& _mapFilename, const std::string& _connectionFilename, const sf::Vector2u& _windowSize);

    ///Spawns Actor instance in given level and in the given position.
    template<ActorBase T>
    static std::shared_ptr<T> spawnActor(Level& _level, const sf::Vector2f& _position)
    {
        return _level.spawnActor<T>(_position);
    }

    ///Spawns Actor subclass instance in current level and in the given position.
    template<ActorBase T>
    std::shared_ptr<T> spawnActor(const sf::Vector2f& _position)
    {
        std::shared_ptr<Actor> actor = Actor::createActor<T>();
        actor->setPosition(_position);
        addActor(actor);
        return dynamic_pointer_cast<T>(actor);
    };

    void setStartPoint(const sf::Vector2f& _position);

    void setDestinationPoint(const sf::Vector2f& _position);

    void reset();

private:

    ///Adds actor to <m_actors> vector making it usable by the level.
    virtual void addActor(const std::shared_ptr<Actor>& _actor);

    ///Loads and creates map.
    void loadMap(const std::string &_mapFilename, const sf::Vector2u &_windowSize);
    ///Loads and creates connections in underlying graph from given file.
    void loadConnections(const std::string &_connectionFilename);
    ///Creates tiles and graph verticesCount for given row.
    void processRow(const sf::Vector2f& tileSize, const std::string &line, int row);

    ///Reset methods
    void resetDestinationPoints();
    void resetPath();

private:

    bool                                    b_isStartInitialized;
    bool                                    b_isEndInitialized;
    ///Stores all Actors present in the level.
    std::vector<std::shared_ptr<Actor>>     m_actors;
    ///Underlying navigation graph.
    Graph                                   m_graph;
    Dijkstra                                m_paths;
};

#endif //EDURITHM_DIJKSTRA_LEVEL_H
