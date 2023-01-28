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

    Bucket *findBucket(const K &key);

    const Bucket *findBucket(const K &key) const;

    Pair *findPair(Bucket *b, const K &key);

    const Pair *findPair(const Bucket *b, const K &key) const;

public:
    HashTable() {}
    const V *const find(const K &key) const;
    void set(const K &key, const V &value);
    bool erase(const K &key);
    const V &operator[](const K &key) const;
    V &operator[](const K &key);
    std::vector<K> keys() const;
    std::vector<V> values() const;
};

template <typename K, typename V, HashFunction<K> hash, size_t size>
typename HashTable<K, V, hash, size>::Bucket *HashTable<K, V, hash, size>::findBucket(const K &key)
{
    unsigned index = hash(key) % size;
    return &data[index];
}

template <typename K, typename V, HashFunction<K> hash, size_t size>
const typename HashTable<K, V, hash, size>::Bucket *HashTable<K, V, hash, size>::findBucket(const K &key) const
{
    unsigned index = hash(key) % size;
    return &data[index];
}

template <typename K, typename V, HashFunction<K> hash, size_t size>
typename HashTable<K, V, hash, size>::Pair *HashTable<K, V, hash, size>::findPair(Bucket *b, const K &key)
{
    if (!b)
        return nullptr;
    for (Pair &p : *b)
        if (p.first == key)
            return &p;
    return nullptr;
}

template <typename K, typename V, HashFunction<K> hash, size_t size>
const typename HashTable<K, V, hash, size>::Pair *HashTable<K, V, hash, size>::findPair(const Bucket *b, const K &key) const
{
    if (!b)
        return nullptr;
    for (const Pair &p : *b)
        if (p.first == key)
            return &p;
    return nullptr;
}

template <typename K, typename V, HashFunction<K> hash, size_t size>
const V *const HashTable<K, V, hash, size>::find(const K &key) const
{
    const typename HashTable<K, V, hash, size>::Pair *p = findPair(findBucket(key), key);
    if (!p)
        return nullptr;
    return &p->second;
}

template <typename K, typename V, HashFunction<K> hash, size_t size>
void HashTable<K, V, hash, size>::set(const K &key, const V &value)
{
    Bucket *b = findBucket(key);
    Pair *p = findPair(findBucket(key), key);
    if (!p)
        b->push_back(Pair(key, value));
    else
        p->second = value;
}

template <typename K, typename V, HashFunction<K> hash, size_t size>
bool HashTable<K, V, hash, size>::erase(const K &key)
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

template <typename K, typename V, HashFunction<K> hash, size_t size>
const V &HashTable<K, V, hash, size>::operator[](const K &key) const
{
    V *res = find(key);
    if (!res)
        return V();
    return *res;
}

template <typename K, typename V, HashFunction<K> hash, size_t size>
V &HashTable<K, V, hash, size>::operator[](const K &key)
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

template <typename K, typename V, HashFunction<K> hash, size_t size>
std::vector<K> HashTable<K, V, hash, size>::keys() const
{
    std::vector<K> res;
    for (const Bucket &b : data)
        for (const Pair &p : b)
            res.push_back(p.first);
    return res;
}

template <typename K, typename V, HashFunction<K> hash, size_t size>
std::vector<V> HashTable<K, V, hash, size>::values() const
{
    std::vector<V> res;
    for (const Bucket &b : data)
        for (const Pair &p : b)
            res.push_back(p.second);
    return res;
}

#endif