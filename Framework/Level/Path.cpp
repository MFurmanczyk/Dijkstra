//
// Created by MFurmanczyk on 20/05/2024.
//

#include "Path.h"
#include "SFML/Graphics/RenderTarget.hpp"

Path::Path()
{
    m_shape = sf::VertexArray(sf::Lines);
}

sf::Vector2f Path::getPosition() const
{
    unsigned size = m_shape.getVertexCount();
    if(size == 0) return {0.f, 0.f};
    else return m_shape[0].position;
}



void Path::setPosition(const sf::Vector2f& _position)
{
    //do nothing
}

void Path::addPoint(const sf::Vector2f &_point)
{
    m_shape.append(sf::Vertex(_point, sf::Color::Blue));
}

void Path::addPoint(const sf::Vector2f &_point, const sf::Color& _color)
{
    m_shape.append(sf::Vertex(_point, _color));
}
void Path::update(float _deltaTime)
{
    //Static object
}

sf::Drawable &Path::getDrawable() {
    return m_shape;
}




