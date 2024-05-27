//
// Created by MFurmaczyk on 23/05/2024.
//

#include "NearestNeighbor.h"
#include "Dijkstra.h"
#include "../Utils/Utils.h"
#include <algorithm>
#include <numeric>

NearestNeighbor::NearestNeighbor(const Graph& _g, int _dim)
{
    m_dim =         _dim;
    m_vertices =    _g.getVertices();
    m_guess =       -1;
    m_minDist =     std::numeric_limits<float>::infinity();

    std::vector<int> indices(m_vertices.size());
    std::iota(indices.begin(), indices.end(), 0);

    m_comparators.emplace_back([this](int _i1, int _i2) {
        return Utils::compareVectorsByX(m_vertices[_i1].m_coords, m_vertices[_i2].m_coords) < 0;
    });
    m_comparators.emplace_back([this](int _i1, int _i2) {
        return Utils::compareVectorsByY(m_vertices[_i1].m_coords, m_vertices[_i2].m_coords) < 0;
    });

    p_root = buildTree(indices, 0);
}

int NearestNeighbor::getNearest(const sf::Vector2f& _point)
{
    getNearest(p_root, _point, 0);
    return m_guess;
}

NearestNeighbor::~NearestNeighbor()
{
    preDestruct(p_root);
}

NearestNeighbor::Node *NearestNeighbor::buildTree(std::vector<int> _indices, int _depth)
{
    if(_indices.empty()) return nullptr;
    else if(_indices.size() == 1) return new Node(_indices[0], nullptr, nullptr);

    std::stable_sort(_indices.begin(), _indices.end(), m_comparators[_depth % m_dim]);

    Node* node = new Node(_indices[_indices.size() / 2], nullptr, nullptr);

    node->p_left =  buildTree(std::vector<int>(_indices.begin(), _indices.begin() + _indices.size() / 2), _depth + 1);
    node->p_right = buildTree(std::vector<int>(_indices.begin() + _indices.size() / 2 + 1, _indices.end()), _depth + 1);

    return node;
}

void NearestNeighbor::getNearest(Node* _node, const sf::Vector2f &_point, int _depth)
{
    if(!_node) return;
    float dist = distance(_point, m_vertices[_node->m_index].m_coords);

    if(dist < m_minDist)
    {
        m_minDist = dist;
        m_guess =   _node->m_index;
    }

    float difference =
            _depth % m_dim == 0 ?
            std::abs(_point.x - m_vertices[_node->m_index].m_coords.x) :
            std::abs(_point.y - m_vertices[_node->m_index].m_coords.y);

    std::function<int(sf::Vector2f, sf::Vector2f)> comparer =
            _depth % m_dim == 0 ?
            Utils::compareVectorsByX :
            Utils::compareVectorsByY;

    if(comparer(_point, m_vertices[_node->m_index].m_coords) < 0)
    {
       getNearest(_node->p_left, _point, _depth + 1);
       if(difference < m_minDist)
       {
           getNearest(_node->p_right, _point, _depth + 1);
       }
    }
    else
    {
        getNearest(_node->p_right, _point, _depth + 1);
        if(difference < m_minDist)
        {
            getNearest(_node->p_left, _point, _depth + 1);
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