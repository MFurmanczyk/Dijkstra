//
// Created by MFurmanczyk on 19/05/2024.
//

#include "PointBase.h"


PointBase::PointBase()
{
    m_shape.setFillColor(sf::Color::Red);
}

sf::Vector2f PointBase::getPosition() const
{
    return m_shape.getPosition();
}

void PointBase::setPositionByRef(sf::Vector2f &_position)
{
    m_shape.setPosition(_position);
}

void PointBase::setPosition(sf::Vector2f _position)
{
    m_shape.setPosition(_position);
}

sf::Color PointBase::getColor() const
{
    return m_shape.getFillColor();
}

void PointBase::setColorByRef(sf::Color& _color)
{
    m_shape.setFillColor(_color);
}

void PointBase::setColor(sf::Color _color)
{
    setColorByRef(_color);
}

float PointBase::getRadius() const
{
    return m_shape.getRadius();
}

void PointBase::setRadius(float _radius)
{
    m_shape.setRadius(_radius);
    m_shape.setOrigin(_radius, _radius);
}

sf::Drawable& PointBase::getDrawable()
{
    return m_shape;
}
