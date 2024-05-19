//
// Created by Maciej Furmańczyk on 19/05/2024.
//

#include "DestinationPoint.h"

DestinationPoint::DestinationPoint()
{
    this->setRadius(10.f);
    this->setColor(sf::Color::Red);
}

void DestinationPoint::update(float _deltaTime)
{
    //Static object
}
