//
// Created by MFurmanczyk on 20/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_PATH_H
#define EDURITHM_DIJKSTRA_PATH_H


#include "Actor.h"
#include "SFML/Graphics/VertexArray.hpp"

class Path : public Actor
{

public:

    Path();
    ~Path() override = default;

    sf::Vector2f getPosition() const override;
    void setPositionByRef(sf::Vector2f& _position) override;
    void setPosition(sf::Vector2f _position) override;

    void update(float _deltaTime) override;

    sf::Drawable &getDrawable() override;

    virtual void addPoint(sf::Vector2f& _point);

private:

    sf::VertexArray m_shape;
};


#endif //EDURITHM_DIJKSTRA_PATH_H
