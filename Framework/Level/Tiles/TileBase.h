//
// Created by Maciej Furmańczyk on 19/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_TILEBASE_H
#define EDURITHM_DIJKSTRA_TILEBASE_H


#include "../Actor.h"
#include "SFML/Graphics/RectangleShape.hpp"

/**
 * Base class for all types tiles.
 */
class TileBase : public Actor
{

public:

    TileBase() = default;
    ~TileBase() override = default;

    ///Getter for size.
    ///@return size of the main Drawable component.
    virtual sf::Vector2f getSize() const;
    ///Setter by reference.
    virtual void setSize(const sf::Vector2f& _size);

    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f& _position) override;

    void update(float _deltaTime) override = 0;

    sf::Drawable& getDrawable() override;

protected:

    ///Tile shape - main Drawable component
    sf::RectangleShape m_shape;
};


#endif //EDURITHM_DIJKSTRA_TILEBASE_H
