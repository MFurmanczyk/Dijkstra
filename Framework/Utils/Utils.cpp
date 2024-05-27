//
// Created by MFurmanczyk on 27/05/2024.
//

#include "Utils.h"

int Utils::compareVectorsByX(sf::Vector2f _v1, sf::Vector2f _v2) {
    if(_v1.x < _v2.x) return -1;
    else if(_v1.x == _v2.x) return 0;
    else return 1;
}

int Utils::compareVectorsByY(sf::Vector2f _v1, sf::Vector2f _v2) {
    if(_v1.y < _v2.y) return -1;
    else if(_v1.y == _v2.y) return 0;
    else return 1;
}
