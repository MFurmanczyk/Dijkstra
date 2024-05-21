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
    explicit Vertex(sf::Vector2f _coords)
    {
        m_coords = _coords;
    };

    sf::Vector2f                    m_coords;
};

struct WeightedEdge
{
    WeightedEdge(int _fromId, int _toId, float _weight) :
        m_from(_fromId),
        m_to(_toId)
    {
        m_weight = _weight;
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

    unsigned verticesCount();
    unsigned edgesCount();

    ///Number of edges that comes into the target.
    unsigned indegree(int _id) const;
    ///Number of edges that comes out of the target.
    unsigned outdegree(int _id) const;

    ///@return vector of all vertiices in the graph.
    std::vector<Vertex> getVertices();
    ///@return list of all edges that comes out of the given vertex.
    std::list<WeightedEdge> getEdges(int _id);

private:

    bool isValidVertex(int _id) const;

private:

    std::vector<Vertex>                     m_vertices;
    std::vector<std::list<WeightedEdge>>    m_edges;
    std::vector<int>                        m_indegree;
};


#endif //EDURITHM_DIJKSTRA_GRAPH_H
