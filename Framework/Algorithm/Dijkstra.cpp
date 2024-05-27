//
// Created by MFurmanczyk on 21/05/2024.
//

#include "Dijkstra.h"
#include <limits>

Dijkstra::Dijkstra(const Graph& _g, int _from) : m_pq(_g.verticesCount())
{
    m_edgeTo = std::vector<WeightedEdge>(_g.verticesCount());
    m_distanceTo = std::vector<float>(_g.verticesCount(), std::numeric_limits<float>::infinity());
    m_distanceTo[_from] = 0.f;

    m_pq.insert(_from, 0.f);
    while(!m_pq.isEmpty())
    {
        int vert = m_pq.removeTop();
        for(auto edge : _g.getEdges(vert))
        {
            relax(edge);
        }
    }
}

float Dijkstra::distanceTo(int _to)
{
    return m_distanceTo[_to];
}

std::stack<WeightedEdge> Dijkstra::pathTo(int _to)
{
    std::stack<WeightedEdge> path;

    for(auto edge = m_edgeTo[_to]; edge.isValidEdge(); edge = m_edgeTo[edge.m_from])
    {
        path.push(edge);
    }

    return path;
}

void Dijkstra::relax(const WeightedEdge& _edge)
{
    int from = _edge.m_from;
    int to = _edge.m_to;

    if(m_distanceTo[to] > m_distanceTo[from] + _edge.m_weight)
    {
        m_distanceTo[to] = m_distanceTo[from] + _edge.m_weight;
        m_edgeTo[to] = _edge;
        if(m_pq.contains(to)) m_pq.decreaseKey(to, m_distanceTo[to]);
        else m_pq.insert(to, m_distanceTo[to]);
    }
}
