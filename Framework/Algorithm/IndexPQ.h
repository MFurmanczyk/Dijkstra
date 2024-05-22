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

    IndexPQ(unsigned _maxSize)
    {
        m_maxSize = _maxSize;
        m_size = 0;
        m_pq = new int[m_maxSize + 1];
        m_qp = new int[m_maxSize + 1];
        m_keys = new T[m_maxSize + 1];

        for(int i = 0; i < m_maxSize + 1; i++)
        {
            m_pq[i] = -1;
            m_qp[i] = -1;
        }
    };

    bool isEmpty() const { return m_size == 0; };

    bool contains(int _id) const
    {
        std::stringstream ss;
        ss << _id;
        if(!isIndexValid(_id)) throw std::invalid_argument("contains: Element with index " + ss.str() + " does not exist.");
        return m_qp[_id] != -1;
    };

    int size() const { return m_size; };

    void insert(int _id, T _key)
    {
        std::stringstream ss;
        ss << _id;
        if(!isIndexValid(_id)) throw std::invalid_argument("insert:" + ss.str() + " Index invalid.");
        if(contains(_id)) throw std::invalid_argument("insert: Element with index: " + ss.str() + " already exists.");

        m_qp[_id] = ++m_size;
        m_pq[m_size] = _id;
        m_keys[_id] = _key;

        swim(m_size);

    };

    int topIndex()
    {
        if(m_size == 0) throw std::out_of_range("topIndex: Empty queue");
        return m_pq[1];
    };

    T topKey()
    {
        if(m_size == 0) throw std::out_of_range("topKey: Empty queue");
        return m_keys[m_pq[1]];
    };

    int removeTop()
    {
        if(m_size == 0) throw std::out_of_range("rwmoveTop: Empty queue");
        int min = m_pq[1];
        swap(1, m_size--);
        sink(1);

        m_qp[min] = -1;
        m_pq[m_size + 1] = -1;

        return min;
    };

    T keyOf(int _id)
    {
        std::stringstream ss;
        ss << _id;
        if(!isIndexValid(_id)) throw std::invalid_argument("keyOf: Element with index" + ss.str() + " does not exist.");
        if(!contains(_id)) throw std::invalid_argument("keyOf: Element with index " + ss.str() + " already exists.");

        return m_keys[_id];
    };

    void changeKey(int _id, T _key)
    {
        std::stringstream ss;
        ss << _id;
        if(!isIndexValid(_id)) throw std::invalid_argument("changeKey: Element with index " + ss.str() + " does not exist.");
        if(!contains(_id)) throw std::invalid_argument("changeKey: Element with index " + ss.str() + " already exists.");

        m_keys[_id];
        swim(m_qp[_id]);
        sink(m_qp[_id]);
    };

    void decreaseKey(int _id, T _key)
    {
        std::stringstream ss;
        ss << _id;
        if(!isIndexValid(_id)) throw std::invalid_argument("decreaseKey: Element with index " + ss.str() + " does not exist.");
        if(!contains(_id)) throw std::invalid_argument("decreaseKey: Element with index " + ss.str() + " already exists.");

        if(m_comparator(_key, m_keys[_id])) throw std::invalid_argument("decreaseKey: _key is greater than or equal to the key in the priority queue.");
        m_keys[_id] = _key;
        swim(m_qp[_id]);
    };

    void increaseKey(int _id, T _key)
    {
        std::stringstream ss;
        ss << _id;
        if(!isIndexValid(_id)) throw std::invalid_argument("increaseKey: Element with index " + ss.str() + " does not exist.");
        if(!contains(_id)) throw std::invalid_argument("increaseKey: Element with index " + ss.str() + " already exists.");

        if(m_comparator(m_keys[_id], _key)) throw std::invalid_argument("increaseKey: _key is less than or equal to the key in the priority queue.");
        m_keys[_id] = _key;
        sink(m_qp[_id]);
    };

    void remove(int _id)
    {
        std::stringstream ss;
        ss << _id;
        if(!isIndexValid(_id)) throw std::invalid_argument("remove: Element with index " + ss.str() + " does not exist.");
        if(!contains(_id)) throw std::invalid_argument("remove: Element with index _id already exists.");

        int index = m_qp[_id];
        swap(index, m_size--);
        swim(index);
        sink(index);
        m_qp[_id] = -1;
    };

    ~IndexPQ()
    {
        delete[] m_pq;
        delete[] m_qp;
        delete[] m_keys;
    }

private:

    bool isIndexValid(int _id) const
    {
        if(_id >= 0) return true;
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
        m_qp[m_pq[_id1]] = _id1;
        m_qp[m_pq[_id2]] = _id2;
    };

private:

    int         m_size;
    unsigned    m_maxSize;
    int*        m_pq;
    int*        m_qp;
    T*          m_keys;
    C           m_comparator;
};


#endif //EDURITHM_DIJKSTRA_INDEXPQ_H
