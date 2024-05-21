//
// Created by MFurmanczyk on 21/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_INDEXPQ_H
#define EDURITHM_DIJKSTRA_INDEXPQ_H

#include <functional>

///Index priority queue based on textbook Algorithms, 4th Edition by R.Sedgewick and K.Wayne.
///@code std::less //for max heap
/// std::greater //for min heap
template<typename T, typename C = std::greater<T>>
class IndexPQ
{
public:

    IndexPQ()
    {
        m_maxSize = 1;
        m_size = 0;
        m_pq.resize(m_maxSize + 1, -1);
        m_qp.resize(m_maxSize + 1, -1);
        m_keys.resize(m_maxSize + 1);
    };

    bool isEmpty() const { return m_size == 0; };

    bool contains(int _id) const
    {
        if(!isIndexValid(_id)) throw std::invalid_argument("Element with index _id does not exist.");
        return m_qp[_id] != -1;
    };

    int size() const { return m_size; };

    void insert(int _id, T _key)
    {
        if(!isIndexValid(_id)) throw std::invalid_argument("Element with index _id does not exist.");
        if(contains(_id)) throw std::invalid_argument("Element with index _id already exists.");

        m_qp[_id] = ++m_size;
        m_pq[m_size] = _id;
        m_keys[_id] = _key;

        swim(m_size);

        if(m_size == m_maxSize)
        {
            m_maxSize *= 2;
            m_qp.resize(m_maxSize + 1, -1);
            m_pq.resize(m_maxSize + 1, -1);
            m_keys.resize(m_maxSize + 1);
        }
    };

    int topIndex()
    {
        if(m_size == 0) throw std::out_of_range("Empty queue");
        return m_pq[1];
    };

    T topKey()
    {
        if(m_size == 0) throw std::out_of_range("Empty queue");
        return m_keys[m_pq[1]];
    };

    int removeTop()
    {
        if(m_size == 0) throw std::out_of_range("Empty queue");
        int min = m_pq[1];
        swap(1, m_size--);
        sink(1);

        m_qp[min] = -1;
        m_pq[m_size + 1] = -1;

        if(m_size == (m_maxSize / 4))
        {
            m_maxSize /= 2;
            m_qp.resize(m_maxSize + 1, -1);
            m_pq.resize(m_maxSize + 1, -1);
            m_keys.resize(m_maxSize + 1);
        }
        return min;
    };

    T keyOf(int _id)
    {
        if(!isIndexValid(_id)) throw std::invalid_argument("Element with index _id does not exist.");
        if(!contains(_id)) throw std::invalid_argument("Element with index _id already exists.");

        return m_keys[_id];
    };

    void changeKey(int _id, T _key)
    {
        if(!isIndexValid(_id)) throw std::invalid_argument("Element with index _id does not exist.");
        if(!contains(_id)) throw std::invalid_argument("Element with index _id already exists.");

        m_keys[_id];
        swim(m_qp[_id]);
        sink(m_qp[_id]);
    };

    void decreaseKey(int _id, T _key)
    {
        if(!isIndexValid(_id)) throw std::invalid_argument("Element with index _id does not exist.");
        if(!contains(_id)) throw std::invalid_argument("Element with index _id already exists.");

        if(!m_comparator(_key, m_keys[_id])) throw std::invalid_argument("_key is greater than or equal to the key in the priority queue.");
        m_keys[_id] = _key;
        swim(m_qp[_id]);
    };

    void increaseKey(int _id, T _key)
    {
        if(!isIndexValid(_id)) throw std::invalid_argument("Element with index _id does not exist.");
        if(!contains(_id)) throw std::invalid_argument("Element with index _id already exists.");

        if(!m_comparator(m_keys[_id], _key)) throw std::invalid_argument("_key is less than or equal to the key in the priority queue.");
        m_keys[_id] = _key;
        sink(m_qp[_id]);
    };

    void remove(int _id)
    {
        if(!isIndexValid(_id)) throw std::invalid_argument("Element with index _id does not exist.");
        if(!contains(_id)) throw std::invalid_argument("Element with index _id already exists.");

        int index = m_qp[_id];
        swap(index, m_size--);
        swim(index);
        sink(index);
        m_qp[_id] = -1;

        if(m_size == (m_maxSize / 4))
        {
            m_maxSize /= 2;
            m_qp.resize(m_maxSize + 1, -1);
            m_pq.resize(m_maxSize + 1, -1);
            m_keys.resize(m_maxSize + 1);
        }
    };

private:

    bool isIndexValid(int _id) const
    {
        if(_id < 0 || _id >= m_maxSize) return false;
        return true;
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
        m_qp[m_pq[_id1]] = _id1;
        m_qp[m_pq[_id2]] = _id2;
    };

private:

    int                 m_size;
    int                 m_maxSize;
    std::vector<int>    m_pq;
    std::vector<int>    m_qp;
    std::vector<T>      m_keys;
    C                   m_comparator;
};


#endif //EDURITHM_DIJKSTRA_INDEXPQ_H
