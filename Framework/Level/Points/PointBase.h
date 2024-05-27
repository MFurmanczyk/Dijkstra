//
// Created by MFurmaczyk on 19/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_POINTBASE_H
#define EDURITHM_DIJKSTRA_POINTBASE_H


#include "SFML/Graphics/CircleShape.hpp"
#include "../Actor.h"

/**
 * Base class for all types of points.
 */
class PointBase : public Actor
{

public:

    PointBase();
    ~PointBase() override = default;

    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f &_position) override;

    ///Getter for color.
    ///@return color of main Drawable component.
    virtual sf::Color getColor() const;
    ///Setter by reference.
    virtual void setColorByRef(sf::Color& _color);
    ///Setter by value.
    virtual void setColor(sf::Color _color);

    ///Getter for radius.
    ///Returns radius of main Drawable circular component.
    virtual float getRadius() const;
    ///Setter.
    virtual void setRadius(float _radius);

    void update(float _deltaTime) override = 0;

    sf::Drawable& getDrawable() override;

protected:

    ///Point shape - main Drawable component.
    sf::CircleShape m_shape;
};


#endif //EDURITHM_DIJKSTRA_POINTBASE_H
