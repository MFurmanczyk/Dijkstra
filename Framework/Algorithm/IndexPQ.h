//
// Created by MFurmanczyk on 21/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_INDEXPQ_H
#define EDURITHM_DIJKSTRA_INDEXPQ_H

#include <functional>
#include <sstream>

///Index priority queue based on textbook Algorithms, 4th Edition by R.Sedgewick and K.Wayne.
///@code std::less //for max heap
/// std::greater //for min heap
template<typename T, typename C = std::greater<T>>
class IndexPQ
{
public:

    IndexPQ() = default;
    IndexPQ(unsigned _maxSize)
    {
        m_maxSize = _maxSize;
        m_size = 0;
        m_pq = std::vector<int>(m_maxSize + 1, -1);
        m_index = std::vector<int>(m_maxSize, -1);
        m_keys = std::vector<T>(m_maxSize);
    };

    bool isEmpty() const { return m_size == 0; };

    bool contains(int _id) const
    {
        std::stringstream ss;
        ss << _id;
        if(!isIndexValid(_id)) throw std::invalid_argument("contains: Element with index " + ss.str() + " does not exist.");
        return m_index[_id] != -1;
    };

    int size() const { return m_size; };

    void insert(int _id, T _key)
    {
        std::stringstream ss;
        ss << _id;
        if(!isIndexValid(_id)) throw std::invalid_argument("insert:" + ss.str() + " Index invalid.");
        if(contains(_id)) throw std::invalid_argument("insert: Element with index: " + ss.str() + " already exists.");

        m_index[_id] = ++m_size;
        m_pq[m_size] = _id;
        m_keys[_id] = _key;

        swim(m_size);
    };

    int removeTop()
    {
        if(m_size == 0) throw std::out_of_range("removeTop: Empty queue");
        int top = m_pq[1];
        swap(1, m_size--);
        sink(1);

        m_index[top] = -1;
        m_pq[m_size + 1] = -1;

        return top;
    };

    void decreaseKey(int _id, T _key)
    {
        std::stringstream ss;
        ss << _id;
        if(!isIndexValid(_id)) throw std::invalid_argument("decreaseKey: Element with index " + ss.str() + " does not exist.");
        if(!contains(_id)) throw std::invalid_argument("decreaseKey: Element with index " + ss.str() + " already exists.");

        if(m_comparator(_key, m_keys[_id])) throw std::invalid_argument("decreaseKey: _key is greater than or equal to the key in the priority queue.");
        m_keys[_id] = _key;
        swim(m_index[_id]);
    };


private:

    bool isIndexValid(int _id) const
    {
        if(_id >= 0 && _id < m_maxSize) return true;
        return false;
    };

    void swim(int _id)
    {
        while (_id > 1 && m_comparator(m_keys[m_pq[_id / 2]], m_keys[m_pq[_id]])) {
            swap(_id, _id / 2);
            _id = _id / 2;
        }
    };

    void sink(int _id)
    {
        while (2 * _id <= m_size)
        {
            int _newId = 2 * _id;
            if(_newId < m_size && m_comparator(m_keys[m_pq[_newId]], m_keys[m_pq[_newId + 1]])) _newId++;
            if(!m_comparator(m_keys[m_pq[_id]], m_keys[m_pq[_newId]])) break;
            swap(_id, _newId);
            _id = _newId;
        }
    };

    void swap(int _id1, int _id2)
    {
        int swap = m_pq[_id1];
        m_pq[_id1] = m_pq[_id2];
        m_pq[_id2] = swap;
        m_index[m_pq[_id1]] = _id1;
        m_index[m_pq[_id2]] = _id2;
    };

private:

    int                     m_size;
    unsigned                m_maxSize;
    std::vector<int>        m_pq;
    std::vector<int>        m_index; //pq index - m_pq[m_index[i]] = i //i == 4, pq[1] = i -> m_keys[pq[1]] = m_keys[i]
    std::vector<T>          m_keys;
    C                       m_comparator;
};


#endif //EDURITHM_DIJKSTRA_INDEXPQ_H
