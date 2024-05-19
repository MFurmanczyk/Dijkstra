//
// Created by Maciej Furmańczyk on 19/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_ROADTILE_H
#define EDURITHM_DIJKSTRA_ROADTILE_H

#include "../Actor.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "TileBase.h"

class RoadTile : public TileBase
{
public:
    RoadTile();
    ~RoadTile() override = default;

    void update(float _deltaTime) override;

};


#endif //EDURITHM_DIJKSTRA_ROADTILE_H
