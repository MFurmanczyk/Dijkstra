//
// Created by Maciej Furmańczyk on 19/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_GRAPHPOINT_H
#define EDURITHM_DIJKSTRA_GRAPHPOINT_H


#include "PointBase.h"

class GraphPoint : public PointBase
{
public:

    GraphPoint();
    ~GraphPoint() override = default;

    void update(float _deltaTime) override;

};


#endif //EDURITHM_DIJKSTRA_GRAPHPOINT_H
