//
// Created by MFurmanczyk on 19/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_GRASSTILE_H
#define EDURITHM_DIJKSTRA_GRASSTILE_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "TileBase.h"

class GrassTile : public TileBase
{
public:
    GrassTile();
    ~GrassTile() override = default;

    void update(float _deltaTime) override;

};


#endif //EDURITHM_DIJKSTRA_GRASSTILE_H
