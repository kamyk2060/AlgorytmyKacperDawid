#include <cassert>
#include <iostream>
#include "myqueue.h"

int main() {

    // Test 1 — konstruktor i empty()
    MyQueue<int> q(3); // max 3 elementy
    assert(q.empty());
    assert(!q.full());
    assert(q.max_size() == 3);

    // Test 2 — push, size, front, back
    q.push(10);
    q.push(20);
    q.push(30);

    assert(q.size() == 3);
    assert(q.front() == 10);
    assert(q.back() == 30);
    assert(q.full());

    // Test 3 — pop
    q.pop(); // usuwa 10
    assert(q.front() == 20);
    assert(q.size() == 2);
    assert(!q.full());

    // Test 4 — cykliczne zawijanie
    q.push(40); // kolejność: 20,30,40
    assert(q.full());
    assert(q.back() == 40);

    q.pop(); // 30, 40
    q.pop(); // 40
    assert(!q.empty());
    assert(q.front() == 40);

    // Test 5 — push po zawinięciu
    q.push(50);
    q.push(60);  
    assert(q.full());
    assert(q.back() == 60);

    // Test 6 — clear()
    q.clear();
    assert(q.empty());
    assert(q.size() == 0);

    // Test 7 — kopiowanie (copy constructor)
    q.push(1);
    q.push(2);
    q.push(3);

    MyQueue<int> q2 = q; // kopia
    assert(q2.size() == 3);
    assert(q2.front() == 1);
    assert(q2.back() == 3);

    // Test 8 — przypisanie kopiujące
    MyQueue<int> q3(5);
    q3 = q;
    assert(q3.size() == 3);
    assert(q3.front() == 1);
    assert(q3.back() == 3);

    // Test 9 — przenoszenie (move constructor)
    MyQueue<int> q4 = std::move(q3);
    assert(q4.size() == 3);
    assert(q3.size() == 0);   // po przeniesieniu msize=1, empty
    assert(q3.max_size() == 0);

    // Test 10 — operator przenoszenia
    MyQueue<int> q5(10);
    q5 = std::move(q4);
    assert(q5.size() == 3);
    assert(q4.size() == 0);

    // Jeśli wszystko działa:
    std::cout << "Wszystkie testy zaliczone!" << std::endl;

    return 0;
}
