#ifndef MYPRIORITYQUEUE_H
#define MYPRIORITYQUEUE_H

#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class MyPriorityQueue {
    std::vector<T> lst;
public:
    MyPriorityQueue(std::size_t s = 10) { lst.reserve(s); }
    ~MyPriorityQueue() { lst.clear(); }

    // copy constructor
    MyPriorityQueue(const MyPriorityQueue& other) : lst(other.lst) {}

    // move constructor
    MyPriorityQueue(MyPriorityQueue&& other) : lst(std::move(other.lst)) {}

    // copy assignment operator
    MyPriorityQueue& operator=(const MyPriorityQueue& other) {
        if (this != &other)
            lst = other.lst;
        return *this;
    }

    // move assignment operator
    MyPriorityQueue& operator=(MyPriorityQueue&& other) {
        if (this != &other)
            lst = std::move(other.lst);
        return *this;
    }

    bool empty() const { return lst.empty(); }
    std::size_t size() const { return lst.size(); }

    void push(const T& item) {
        lst.push_back(item);
        std::push_heap(lst.begin(), lst.end());
    }

    void push(T&& item) {
        lst.push_back(std::move(item));
        std::push_heap(lst.begin(), lst.end());
    }

    T& top() { return lst.front(); }

    void pop() {
        std::pop_heap(lst.begin(), lst.end());
        lst.pop_back();
    }

    void clear() { lst.clear(); }

    void display() {
        for (const T& item : lst)
            std::cout << item << " ";
        std::cout << std::endl;
    }
};

#endif