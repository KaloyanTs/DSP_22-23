#ifndef __HASH_TABLE_HPP
#define __HASH_TABLE_HPP

#include <cstddef>
#include <vector>

template <typename T>
using HashFunction = unsigned (*)(const T &);

template <typename K, typename V, HashFunction<K> hash, size_t size = 100>
class HashTable
{
    using Pair = std::pair<K, V>;
    using Bucket = std::vector<Pair>;
    using Table = Bucket[size];

    Table data;

    Bucket *findBucket(const K &key)
    {
        unsigned index = hash(key) % size;
        return &data[index];
    }

    Pair *findPair(Bucket *b, const K &key)
    {
        if (!b)
            return nullptr;
        for (Pair &p : *b)
            if (p.first == key)
                return &p;
        return nullptr;
    }

public:
    HashTable() {}
    V *const find(const K &key) const
    {
        Pair *p = findPair(findBucket(key), key);
        if (!p)
            return nullptr;
        return &p->second;
    }
    void set(const K &key, const V &value)
    {
        Bucket *b = findBucket(key);
        Pair *p = findPair(findBucket(key), key);
        if (!p)
            b->push_back(Pair(key, value));
        else
            p->second = value;
    }
    bool erase(const K &key)
    {
        Bucket *b = findBucket(key);
        if (!b)
            return false;
        typename Bucket::iterator i = b->begin();
        while (i != b->end() && i->first != key)
            ++i;
        if (i == b->end())
            return false;
        b->erase(i);
        return true;
    }
    const V &operator[](const K &key) const
    {
        V *res = find(key);
        if (!res)
            return V();
        return *res;
    }
    V &operator[](const K &key)
    {
        Bucket *b = findBucket(key);
        Pair *p = findPair(b, key);
        if (!p)
        {
            b->push_back(Pair(key, V()));
            return b->back().second;
        }
        return p->second;
    }
    std::vector<K> keys() const
    {
        std::vector<K> res;
        for (const Bucket &b : data)
            for (const Pair &p : b)
                res.push_back(p.first);
        return res;
    }
    std::vector<V> values() const
    {
        std::vector<V> res;
        for (const Bucket &b : data)
            for (const Pair &p : b)
                res.push_back(p.second);
        return res;
    }
};

#endif