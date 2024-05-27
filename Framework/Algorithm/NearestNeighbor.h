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
        Node(const sf::Vector2f& _point, int _index, Node* _left, Node* _right)
        {
            m_point = _point;
            m_index = _index;
            p_left = _left;
            p_right = _right;
        };

        sf::Vector2f m_point;
        int     m_index;
        Node*   p_left;
        Node*   p_right;
    };

    typedef std::function<bool(Node*, Node*)> vertexComparator;

public:

    NearestNeighbor() = default;
    NearestNeighbor(const Graph& _g, int _dim);
    Node* getNearest(const sf::Vector2f& _point);
    ~NearestNeighbor();

private:

    Node* buildTree(std::vector<Node*> _nodes, int _depth);
    void getNearest(Node *_node, const sf::Vector2f &_point, Node *&_guess, float &_minDist, int _depth);
    void preDestruct(Node* _node);

    float distance(sf::Vector2f _p1, sf::Vector2f _p2);

private:

    Node*                         p_root;
    int                           m_dim;
    std::vector<vertexComparator> m_comparators;

};

#endif //EDURITHM_DIJKSTRA_NEARESTNEIGHBOR_H