//
// Created by MFurmanczyk on 19/05/2024.
//

#include "TileBase.h"

sf::Vector2f TileBase::getSize() const
{
    return m_shape.getSize();
}

void TileBase::setSizeByRef(sf::Vector2f &_size)
{
    m_shape.setSize(_size);
    m_shape.setOrigin(_size.x / 2, _size.y / 2);
}

void TileBase::setSize(sf::Vector2f _size)
{
    setSizeByRef(_size);
}

sf::Vector2f TileBase::getPosition() const
{
    return m_shape.getPosition();
}

void TileBase::setPositionByRef(sf::Vector2f &_position)
{
    m_shape.setPosition(_position);
}

void TileBase::setPosition(sf::Vector2f _position)
{
    setPositionByRef(_position);
}

sf::Drawable &TileBase::getDrawable() {
    return m_shape;
}