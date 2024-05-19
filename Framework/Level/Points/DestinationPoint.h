//
// Created by MFurmanczyk on 19/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_DESTINATIONPOINT_H
#define EDURITHM_DIJKSTRA_DESTINATIONPOINT_H


#include "PointBase.h"

class DestinationPoint : public PointBase
{
public:

    DestinationPoint();
    ~DestinationPoint() override = default;

    void update(float _deltaTime) override;
};


#endif //EDURITHM_DIJKSTRA_DESTINATIONPOINT_H
