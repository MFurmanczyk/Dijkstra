//
// Created by MFurmanczyk on 21/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_DIJKSTRA_H
#define EDURITHM_DIJKSTRA_DIJKSTRA_H


#include <stack>
#include <queue>
#include "IndexPQ.h"
#include "Graph.h"

struct Node
{
    Node(int _to, float _distance)
    {
        m_to = _to;
        m_distance = _distance;
    };

    bool operator>(const Node& _other) const
    {
        return this->m_distance > _other.m_distance;
    };

    bool operator<(const Node& _other) const
    {
        return this->m_distance < _other.m_distance;
    };

    bool operator==(const Node& _other) const
    {
        return this->m_distance == _other.m_distance;
    };

    int     m_to;
    float   m_distance;
};

class Dijkstra
{
public:

    Dijkstra() = default;
    Dijkstra(const Graph& _g, int _from);

    float distanceTo(int _to);
    std::stack<WeightedEdge> pathTo(int _to);

private:

    void relax(const WeightedEdge& _edge);

private:

    std::vector<WeightedEdge>   m_edgeTo;
    std::vector<float>          m_distanceTo;
    IndexPQ<float>              m_pq;
};

#endif //EDURITHM_DIJKSTRA_DIJKSTRA_H
