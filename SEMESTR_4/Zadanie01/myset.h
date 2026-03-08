#ifndef MYSET_H
#define MYSET_H

#include <iostream>
#include <list>
#include <cassert>

template<typename T>
class MySet {
    int BUCKET;
    std::list<T> *table;
public:
    MySet(int b);
    ~MySet() { clear(); delete[] table; }

    bool empty() const;
    int size() const;
    void insert(T key);
    T* find(const T& key);
    bool contains(const T& key);
    void remove(const T& key);
    int hash(const T& key) const { return (int(key) % BUCKET); }
    void clear();
    void display() const;

    class Iterator {
        const MySet<T>* set;
        int bucketIdx;
        typename std::list<T>::const_iterator listIt;

        void skipEmpty() {
            while (bucketIdx < set->BUCKET && set->table[bucketIdx].empty())
                ++bucketIdx;
            if (bucketIdx < set->BUCKET)
                listIt = set->table[bucketIdx].cbegin();
        }
    public:
        Iterator(const MySet<T>* s, int b) : set(s), bucketIdx(b) { skipEmpty(); }
        Iterator(const MySet<T>* s, int b, bool) : set(s), bucketIdx(b) {}

        const T& operator*()  const { return *listIt; }
        const T* operator->() const { return &(*listIt); }

        Iterator& operator++() {
            ++listIt;
            if (listIt == set->table[bucketIdx].cend()) {
                ++bucketIdx;
                skipEmpty();
            }
            return *this;
        }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const Iterator& o) const {
            if (bucketIdx != o.bucketIdx) return false;
            if (bucketIdx >= set->BUCKET)  return true;
            return listIt == o.listIt;
        }
        bool operator!=(const Iterator& o) const { return !(*this == o); }
    };

    Iterator begin() const { return Iterator(this, 0);            }
    Iterator end()   const { return Iterator(this, BUCKET, true); }
};

template<typename T>
MySet<T>::MySet(int b) {
    BUCKET = b;
    table = new std::list<T>[BUCKET];
    assert(table != nullptr);
}

template<typename T>
bool MySet<T>::empty() const {
    for (int i = 0; i < BUCKET; i++)
        if (!table[i].empty()) return false;
    return true;
}

template<typename T>
int MySet<T>::size() const {
    int count = 0;
    for (int i = 0; i < BUCKET; i++)
        count += (int)table[i].size();
    return count;
}

template<typename T>
void MySet<T>::insert(T key) {
    if (contains(key)) return;
    table[hash(key)].push_back(key);
}

template<typename T>
T* MySet<T>::find(const T& key) {
    for (T& k : table[hash(key)])
        if (k == key) return &k;
    return nullptr;
}

template<typename T>
bool MySet<T>::contains(const T& key) {
    return find(key) != nullptr;
}

template<typename T>
void MySet<T>::remove(const T& key) {
    table[hash(key)].remove(key);
}

template<typename T>
void MySet<T>::clear() {
    for (int i = 0; i < BUCKET; i++)
        table[i].clear();
}

template<typename T>
void MySet<T>::display() const {
    std::cout << "{ ";
    bool first = true;
    for (int i = 0; i < BUCKET; i++)
        for (const T& k : table[i]) {
            if (!first) std::cout << ", ";
            std::cout << k;
            first = false;
        }
    std::cout << " }" << std::endl;
}

#endif