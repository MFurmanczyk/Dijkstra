//
// Created by MFurmanczyk on 20/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_GRAPH_H
#define EDURITHM_DIJKSTRA_GRAPH_H

#include <vector>
#include <map>
#include "SFML/System/Vector2.hpp"

struct Vertex
{
    explicit Vertex(sf::Vector2f _coords)
    {
        m_coords = _coords;
    };

    sf::Vector2f                    m_coords;
};


struct WeightedEdge
{
    WeightedEdge(Vertex _from, Vertex _to)
    :   m_fromVertex(_from),
        m_toVertex(_to)
    {
        m_weight = std::sqrt(
                std::pow(_from.m_coords.x - _to.m_coords.x, 2) +
                std::pow(_from.m_coords.y - _to.m_coords.y, 2)
        );
    };

    Vertex      m_fromVertex;
    Vertex      m_toVertex;
    float       m_weight;
};

class Graph
{
public:

    Graph();

    void addVertex(sf::Vector2f _coords);
    void addEdge(int _from, int _to);

    unsigned verticesCount();
    unsigned edgesCount();

    unsigned indegree(int _id) const;
    unsigned outdegree(int _id) const;

    std::vector<Vertex>& getVertices();
    std::vector<WeightedEdge>& getEdges(int _id);

private:

    bool isValidVertex(int _id) const;

private:

    mutable std::vector<Vertex>                     m_vertices;
    mutable std::vector<std::vector<WeightedEdge>>  m_edges;
    std::vector<int>                                m_indegree;
};


#endif //EDURITHM_DIJKSTRA_GRAPH_H
