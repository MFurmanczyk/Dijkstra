//
// Created by MFurmanczyk on 23/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_NEARESTNEIGHBOR_H
#define EDURITHM_DIJKSTRA_NEARESTNEIGHBOR_H

#include <vector>
#include <array>
#include <functional>
#include "Graph.h"

class NearestNeighbor
{
    struct Node
    {
        Node(int _index, Node* _left, Node* _right)
        {
            m_index = _index;
            p_left = _left;
            p_right = _right;
        };

        int     m_index;
        Node*   p_left;
        Node*   p_right;
    };

    typedef std::function<bool(int, int)> vertexComparator;

public:

    NearestNeighbor() = default;
    NearestNeighbor(const Graph& _g, int _dim);
    int getNearest(const sf::Vector2f& _point);
    ~NearestNeighbor();

private:

    Node* buildTree(std::vector<int> _indices, int _depth);
    void getNearest(Node *_node, const sf::Vector2f &_point, int _depth);
    void preDestruct(Node* _node);

    float distance(sf::Vector2f _p1, sf::Vector2f _p2);

private:

    Node*                           p_root;
    std::vector<Vertex>             m_vertices;
    std::vector<vertexComparator>   m_comparators;
    int                             m_dim;
    int                             m_guess;
    float                           m_minDist;

};

#endif //EDURITHM_DIJKSTRA_NEARESTNEIGHBOR_H