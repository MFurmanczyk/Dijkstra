//
// Created by MFurmanczyk on 19/05/2024.
//

#include "TileBase.h"

sf::Vector2f TileBase::getSize() const
{
    return m_shape.getSize();
}

void TileBase::setSize(const sf::Vector2f &_size)
{
    m_shape.setSize(_size);
    m_shape.setOrigin(_size.x / 2, _size.y / 2);
}

sf::Vector2f TileBase::getPosition() const
{
    return m_shape.getPosition();
}

void TileBase::setPosition(const sf::Vector2f &_position)
{
    m_shape.setPosition(_position);
}

sf::Drawable &TileBase::getDrawable() {
    return m_shape;
}