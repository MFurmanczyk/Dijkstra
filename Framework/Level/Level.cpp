//
// Created by MFurmanczyk on 18/05/2024.
//

#include "Level.h"
#include "Tiles/GrassTile.h"
#include "Tiles/RoadTile.h"
#include "Points/DestinationPoint.h"
#include "../Algorithm/Dijkstra.h"
#include "Path.h"
#include "../Algorithm/NearestNeighbor.h"
#include <fstream>
#include <sstream>

void Level::update(float _deltaTime)
{
    for(auto& actor : m_actors)
    {
        actor->update(_deltaTime);
    }
}

void Level::draw(sf::RenderTarget& _target)
{
    for(auto& actor : m_actors)
    {
        actor->draw(_target);
    }
}

void Level::loadFromFile(const std::string& _mapFilename, const std::string& _connectionFilename, const sf::Vector2u& _windowSize)
{
    loadMap(_mapFilename, _windowSize);
    loadConnections(_connectionFilename);

    /*Dijkstra d(m_graph, 12);
    auto p = d.pathTo(20);
    ;
    auto a = spawnActor<Path>(sf::Vector2f(0,0));
    auto v = m_graph.getVertices();
    while(!p.empty())
    {
        a->addPoint(v[p.top().m_to].m_coords);
        a->addPoint(v[p.top().m_from].m_coords);
        p.pop();
    }*/

    NearestNeighbor nn(m_graph, 2);
}

void Level::loadMap(const std::string &_mapFilename, const sf::Vector2u &_windowSize) {
    std::ifstream mapFile(_mapFilename);
    if(mapFile.is_open())
    {
        int sizeX, sizeY; //map resolution in tiles
        mapFile >> sizeX >> sizeY;

        sf::Vector2f tileSize(_windowSize.x / sizeX, _windowSize.y / sizeY); //single tile size

        std::string line;
        int row = 0;

        while(mapFile >> line)
        {
            processRow(tileSize, line, row++);
        }
    }
    mapFile.close();
}

void Level::loadConnections(const std::string &_connectionFilename) {
    std::ifstream connectionFile(_connectionFilename);
    if(connectionFile.is_open())
    {
        std::string line;
        int vertexId = 0; //initial vertex id
        while(std::getline(connectionFile, line))
        {
            std::stringstream ss(line); //whole line
            int destVertexId;
            while(ss >> destVertexId) //single connection
            {
                m_graph.addEdge(vertexId, destVertexId - 1);
            }
            vertexId++;
        }
    }
    connectionFile.close();
}

void Level::processRow(const sf::Vector2f& tileSize, const std::string& line, int row) {
    int col = 0;
    for(char ch : line)
    {
        //calculate tile position
        auto position = sf::Vector2f(tileSize.x * (1.f/2.f + col), tileSize.y * (1.f/2.f + row));
        int type = ch - '0';
        if(type == 0)
        {
            //Grass
            auto tile= spawnActor<GrassTile>(position);
            tile->setSize(tileSize);
        }
        else if(type == 1)
        {
            //Road
            auto tile= spawnActor<RoadTile>(position);
            tile->setSize(tileSize);
        }
        else if(type == 2)
        {
            //Intersection
            auto tile= spawnActor<RoadTile>(position);
            tile->setSize(tileSize);

            m_graph.addVertex(position);
        }
        col++;
    }
}

void Level::resetDestinationPoints()
{
    auto predicate = [](const std::shared_ptr<Actor>& ptr)
            { return dynamic_pointer_cast<PointBase>(ptr) != nullptr; };
    erase_if(m_actors, predicate);
}

void Level::addActor(const std::shared_ptr<Actor>& _actor)
{
    m_actors.push_back(_actor);
}

void Level::removeActor(Actor* _actor)
{
    if (_actor)
    {
        auto it = std::find(m_actors.begin(), m_actors.end(), std::shared_ptr<Actor>(_actor));
        if (it != m_actors.end())
        {
            m_actors.erase(it);
        }
    }
}
