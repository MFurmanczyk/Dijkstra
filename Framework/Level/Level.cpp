//
// Created by MFurmanczyk on 18/05/2024.
//

#include "Level.h"
#include "Tiles/GrassTile.h"
#include "Tiles/RoadTile.h"
#include "Points/PointBase.h"
#include "Points/GraphPoint.h"
#include "Points/DestinationPoint.h"
#include <fstream>
#include <iostream>

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

void Level::loadFromFile(std::string _filename, sf::Vector2u _windowSize)
{
    std::ifstream file(_filename);
    if(file.is_open())
    {
        int sizeX, sizeY;
        file >> sizeX >> sizeY;

        sf::Vector2f tileSize(_windowSize.x / sizeX, _windowSize.y / sizeY);
        std::string line;

        unsigned row = 0, col = 0;

        while(file >> line)
        {
            for(char& ch : line)
            {
                //calculate tile position
                auto position = sf::Vector2i(tileSize.x * (1.f/2.f + col), tileSize.y * (1.f/2.f + row));
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

                    auto point= spawnActor<GraphPoint>(position);
                    point->setColor(sf::Color::Blue);
                    point->setRadius(5.f);
                }
                col++;
            }
            row++;
            col = 0;
        }
    }
    file.close();
}

void Level::addActor(std::shared_ptr<Actor>& _actor)
{
    m_actors.push_back(_actor);
}

void Level::resetDestinationPoints()
{
    auto predicate = [](const std::shared_ptr<Actor>& ptr)
            { return dynamic_pointer_cast<DestinationPoint>(ptr) != nullptr; };
    erase_if(m_actors, predicate);
}
