#include <cassert>
#include "mypriorityqueue.h"

int main() {
    MyPriorityQueue<int> pq;

    // --- empty / push / size ---
    assert(pq.empty());
    assert(pq.size() == 0);

    pq.push(3);
    pq.push(7);
    pq.push(1);
    pq.push(9);
    pq.push(4);

    assert(!pq.empty());
    assert(pq.size() == 5);

    // --- top zawsze zwraca największy ---
    assert(pq.top() == 9);
    pq.display();

    // --- pop usuwa największy ---
    pq.pop();
    assert(pq.top() == 7);
    assert(pq.size() == 4);

    pq.pop();
    assert(pq.top() == 4);

    // --- copy constructor ---
    MyPriorityQueue<int> pq2(pq);
    assert(pq2.size() == pq.size());
    assert(pq2.top() == pq.top());

    // modyfikacja kopii nie wpływa na oryginał
    pq2.push(100);
    assert(pq2.top() == 100);
    assert(pq.top() == 4);

    // --- copy assignment ---
    MyPriorityQueue<int> pq3;
    pq3 = pq;
    assert(pq3.size() == pq.size());
    assert(pq3.top() == pq.top());

    // --- move constructor ---
    MyPriorityQueue<int> pq4(std::move(pq2));
    assert(pq4.top() == 100);
    assert(pq2.empty());

    // --- move assignment ---
    MyPriorityQueue<int> pq5;
    pq5 = std::move(pq3);
    assert(pq5.top() == 4);
    assert(pq3.empty());

    // --- clear ---
    pq.clear();
    assert(pq.empty());
    assert(pq.size() == 0);

    std::cout << "Wszystkie testy zaliczone.\n";
    return 0;
}