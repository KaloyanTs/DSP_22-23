#ifndef __AVL_DICTIONARY_HPP
#define __AVL_DICTIONARY_HPP

#include "avl_tree.ipp"

template <typename K, typename V>
class AVLDictionary
{
    struct KeyValue
    {
        K key;
        V value;

    public:
        KeyValue(const K &_k = K(), const V &_v = V()) : key(_k), value(_v) {}
        KeyValue(const KeyValue &other) : key(other.key), value(other.value) {}
        bool operator==(const KeyValue &other) { return key == other.key; }
        bool operator<(const KeyValue &other) { return key < other.key; }
        bool operator>(const KeyValue &other) { return key > other.key; }
        bool operator<=(const KeyValue &other) { return !(*this > other); }
        bool operator>=(const KeyValue &other) { return !(*this < other); }
        static K getKey(const KeyValue &kv)
        {
            return kv.key;
        }
        static V getValue(const KeyValue &kv)
        {
            return kv.value;
        }
    };

    AVLTree<KeyValue> data;

    template <typename A, typename B>
    friend std::ostream &operator<<(std::ostream &, const typename AVLDictionary<A, B>::KeyValue &);

public:
    AVLDictionary() {}
    V *const find(const K &key) const;
    void set(const K &key, const V &value);
    bool erase(const K &key);
    const V &operator[](const K &key) const;
    V &operator[](const K &key);
    std::vector<K> keys() const { return data.collect(KeyValue::getKey); }
    std::vector<V> values() const { return data.collect(KeyValue::getValue); }
    // todo printing pairs maybe not working
};

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const typename AVLDictionary<K, V>::KeyValue &kv)
{
    return os << '(' << kv.key << ", " << kv.value << ')';
}

template <typename K, typename V>
V *const AVLDictionary<K, V>::find(const K &key) const
{
    KeyValue *const p = data.search(KeyValue(key));
    if (!p)
        return nullptr;
    return &p->value;
}

template <typename K, typename V>
void AVLDictionary<K, V>::set(const K &key, const V &value)
{
    KeyValue *const pos = data.search(key);
    if (!pos)
        data.insert(KeyValue(key, value));
    else
        pos->value = value;
}

template <typename K, typename V>
bool AVLDictionary<K, V>::erase(const K &key)
{
    return data.erase(KeyValue(key));
}

template <typename K, typename V>
const V &AVLDictionary<K, V>::operator[](const K &key) const
{
    KeyValue *res = data.search(KeyValue(key));
    if (!res)
        return V();
    return res->value;
}

template <typename K, typename V>
V &AVLDictionary<K, V>::operator[](const K &key)
{
    KeyValue *res = data.search(KeyValue(key));
    if (!res)
        data.insert(KeyValue(key));
    return res->value;
}

#endif