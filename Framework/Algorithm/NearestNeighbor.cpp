//
// Created by MFurmaczyk on 23/05/2024.
//

#include "NearestNeighbor.h"
#include "Dijkstra.h"
#include <algorithm>

NearestNeighbor::NearestNeighbor(const Graph& _g, int _dim)
{
    std::vector<Node*> nodes;
    int i = 0;
    for(auto vertex : _g.getVertices())
    {
        Node* node = new Node(vertex.m_coords, i++, nullptr, nullptr);
        nodes.push_back(node);
    }

    m_dim = _dim;

    m_comparators.emplace_back([](Node* _n1, Node* _n2) {
        return _n1->m_point.x < _n2->m_point.x;
    });

    m_comparators.emplace_back([](Node* _n1, Node* _n2) {
        return _n1->m_point.y < _n2->m_point.y;
    });

    p_root = buildTree(nodes, 0);
}

NearestNeighbor::Node *NearestNeighbor::getNearest(const sf::Vector2f& _point)
{
    float minDist = std::numeric_limits<float>::max();
    Node* guess;
    getNearest(p_root, _point, guess, minDist, 0);
    return guess;
}

NearestNeighbor::~NearestNeighbor()
{
    preDestruct(p_root);
}

NearestNeighbor::Node *NearestNeighbor::buildTree(std::vector<Node*> _nodes, int _depth)
{
    if(_nodes.begin() == (_nodes.end() - 1)) return _nodes.front();
    if(_nodes.empty()) return nullptr;

    std::stable_sort(_nodes.begin(), _nodes.end(), m_comparators[_depth % m_dim]);

    auto node = _nodes[_nodes.size() / 2];

    node->p_left = buildTree(std::vector<Node*>(_nodes.begin(), _nodes.begin() + _nodes.size() / 2), _depth + 1);
    node->p_right = buildTree(std::vector<Node*>(_nodes.begin() + _nodes.size() / 2 + 1, _nodes.end()), _depth + 1);

    return node;
}

void NearestNeighbor::getNearest(Node *_node, const sf::Vector2f &_point, Node *&_guess, float &_minDist, int _depth)
{
    if(!_node) return;
    sf::Vector2f nodePos = _node->m_point;

    float dist = distance(_point, nodePos);

    if(dist < _minDist)
    {
        _minDist = dist;
        _guess = _node;
    }

    std::unique_ptr<Node> pointPtr = std::make_unique<Node>(_point, -1, nullptr, nullptr);
    float difference = _depth % m_dim == 0 ? std::abs(_point.x - nodePos.x) : std::abs(_point.y - nodePos.y);
    if(m_comparators[_depth % m_dim](pointPtr.get(), _node))
    {
        getNearest(_node->p_left, _point, _guess, _minDist, _depth + 1);

        if(difference < _minDist)
        {
            getNearest(_node->p_right, _point, _guess, _minDist, _depth + 1);
        }
    }
    else
    {
        getNearest(_node->p_right, _point, _guess, _minDist, _depth + 1);
        if(difference < _minDist)
        {
            getNearest(_node->p_left, _point, _guess, _minDist, _depth + 1);
        }
    }
}

void NearestNeighbor::preDestruct(Node *_node)
{
    if(!_node) return;
    preDestruct(_node->p_left);
    preDestruct(_node->p_right);
    delete _node;
}

float NearestNeighbor::distance(sf::Vector2f _p1, sf::Vector2f _p2)
{
    return std::sqrt(
            std::pow(_p1.x - _p2.x, 2) +
            std::pow(_p1.y - _p2.y, 2)
    );
}
