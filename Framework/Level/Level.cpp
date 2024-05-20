//
// Created by MFurmanczyk on 18/05/2024.
//

#include "Level.h"
#include "Tiles/GrassTile.h"
#include "Tiles/RoadTile.h"
#include "Points/DestinationPoint.h"
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

void Level::loadFromFile(std::string _mapFilename, std::string _connectionFilename, sf::Vector2u _windowSize)
{
    loadMap(_mapFilename, _windowSize);
    loadConnections(_connectionFilename);
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
                m_graph.addEdge(vertexId, destVertexId);
            }
            vertexId++;
        }
    }
    connectionFile.close();
}

void Level::processRow(sf::Vector2f& tileSize, std::string& line, int row) {
    int col = 0;
    for(char& ch : line)
    {
        //calculate tile position
        auto position = sf::Vector2f(tileSize.x * (1.f/2.f + col), tileSize.y * (1.f/2.f + row));
        int type = ch - '0';
        if(type == 0)
        {
            //Grass
            auto tile= spawnActor<GrassTile>(position);
            tile->setSizeByRef(tileSize);
        }
        else if(type == 1)
        {
            //Road
            auto tile= spawnActor<RoadTile>(position);
            tile->setSizeByRef(tileSize);
        }
        else if(type == 2)
        {
            //Intersection
            auto tile= spawnActor<RoadTile>(position);
            tile->setSizeByRef(tileSize);

            m_graph.addVertex(position);
        }
        col++;
    }
}

void Level::resetDestinationPoints()
{
    auto predicate = [](const std::shared_ptr<Actor>& ptr)
            { return dynamic_pointer_cast<DestinationPoint>(ptr) != nullptr; };
    erase_if(m_actors, predicate);
}

void Level::addActor(std::shared_ptr<Actor>& _actor)
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
