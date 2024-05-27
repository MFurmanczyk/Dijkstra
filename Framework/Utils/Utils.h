//
// Created by MFurmanczyk on 27/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_UTILS_H
#define EDURITHM_DIJKSTRA_UTILS_H


#include "SFML/System/Vector2.hpp"

class Utils final
{

public:

    static int compareVectorsByX(sf::Vector2f _v1, sf::Vector2f _v2);

    static int compareVectorsByY(sf::Vector2f _v1, sf::Vector2f _v2);

};


#endif //EDURITHM_DIJKSTRA_UTILS_H
