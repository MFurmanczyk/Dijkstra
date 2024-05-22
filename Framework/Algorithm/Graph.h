//
// Created by MFurmanczyk on 20/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_GRAPH_H
#define EDURITHM_DIJKSTRA_GRAPH_H

#include <vector>
#include <list>
#include <map>
#include "SFML/System/Vector2.hpp"

struct Vertex
{
    explicit Vertex()
    {
        m_coords = sf::Vector2f(-1,-1);
    };

    explicit Vertex(sf::Vector2f _coords)
    {
        m_coords = _coords;
    };

    bool isVertexValid() const
    {
        return m_coords != sf::Vector2f(-1,-1);
    };

    sf::Vector2f                    m_coords;
};

struct WeightedEdge
{
    explicit WeightedEdge()
    {
        m_from = -1;
        m_to = -1;
        m_weight = std::numeric_limits<float>::infinity();
    };

    explicit WeightedEdge(int _fromId, int _toId, float _weight) :
        m_from(_fromId),
        m_to(_toId)
    {
        m_weight = _weight;
    };

    bool operator<(WeightedEdge const& _other) const
    {
        return this->m_weight < _other.m_weight;
    };

    bool operator>(WeightedEdge const& _other) const
    {
        return this->m_weight > _other.m_weight;
    };

    bool operator==(WeightedEdge const& _other) const
    {
        return this->m_weight == _other.m_weight;
    };

    bool operator>=(WeightedEdge const& _other) const
    {
        return this->m_weight >= _other.m_weight;
    };

    bool operator<=(WeightedEdge const& _other) const
    {
        return this->m_weight <= _other.m_weight;
    };

    bool isValidEdge() const
    {
        return m_from != -1;
    };

    int         m_from;
    int         m_to;
    float       m_weight;
};

///Directed graph that stores cpnnections and intersections for the process of calculating the shortest paths.
class Graph
{
public:

    Graph() = default;

    ///Adds vertex with given coords to the end of vertices list.
    void addVertex(sf::Vector2f _coords);
    ///Connects two vertices.
    void addEdge(int _from, int _to);

    unsigned verticesCount() const;
    unsigned edgesCount() const;

    ///Number of edges that comes into the target.
    unsigned indegree(int _id) const;
    ///Number of edges that comes out of the target.
    unsigned outdegree(int _id) const;

    ///@return vector of all vertiices in the graph.
    std::vector<Vertex> getVertices() const;
    ///@return list of all edges that comes out of the given vertex.
    std::list<WeightedEdge> getEdges(int _id) const;

private:

    bool isValidVertex(int _id) const;

private:

    std::vector<Vertex>                     m_vertices;
    std::vector<std::list<WeightedEdge>>    m_edges;
    std::vector<int>                        m_indegree;
};

#endif //EDURITHM_DIJKSTRA_GRAPH_H
