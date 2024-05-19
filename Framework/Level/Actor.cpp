//
// Created by MFurmanczyk on 18/05/2024.
//

#include "Actor.h"
#include <SFML/Graphics/RenderTarget.hpp>

void Actor::draw(sf::RenderTarget &_target)
{
    _target.draw(getDrawable());
}
