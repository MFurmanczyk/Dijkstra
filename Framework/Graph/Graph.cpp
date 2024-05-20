//
// Created by MFurmanczyk on 20/05/2024.
//

#include "Graph.h"

Graph::Graph()
{

}

void Graph::addVertex(sf::Vector2f _coords)
{
    Vertex v(_coords);
    m_vertices.push_back(v);
    m_edges.emplace_back();
    m_indegree.emplace_back();
}

void Graph::addEdge(int _from, int _to)
{
    if(isValidVertex(_from) && isValidVertex(_to))
    {
        Vertex from =   m_vertices[_from];
        Vertex to =     m_vertices[_to];

        WeightedEdge edge(from, to);
        m_edges[_from].push_back(edge);
        m_indegree[_to]++;
    }
}

unsigned Graph::verticesCount() {
    return m_vertices.size();
}

unsigned Graph::edgesCount()
{
    unsigned counter = 0;
    for(const auto& edges : m_edges)
    {
        counter += edges.size();
    }
    return counter;
}

unsigned Graph::indegree(int _id) const
{
    if(!isValidVertex(_id)) return 0;
    return m_indegree[_id];
}

unsigned Graph::outdegree(int _id) const
{
    if(!isValidVertex(_id)) return 0;
    return m_edges[_id].size();
}

std::vector<Vertex>& Graph::getVertices() {
    return m_vertices;
}

std::vector<WeightedEdge>& Graph::getEdges(int _id)
{
    if(isValidVertex(_id)) return m_edges[_id];
    throw std::invalid_argument("Vertex with given _id does not exist.");
}

bool Graph::isValidVertex(int _id) const
{
    return _id < m_vertices.size();
}


