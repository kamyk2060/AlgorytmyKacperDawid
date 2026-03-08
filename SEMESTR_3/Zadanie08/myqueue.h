// myqueue.h
#include <cstddef>
#include <cassert>
#include <utility>
#include <iostream>

template <typename T>
class MyQueue {
    T* tab;
    std::size_t msize; // największa możliwa liczba elementów plus jeden
    std::size_t head; // pierwszy do pobrania
    std::size_t tail; // pierwsza wolna pozycja
public:
    MyQueue(std::size_t s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor

    ~MyQueue() { delete [] tab; }

    MyQueue(const MyQueue& other); // copy constructor
    MyQueue(MyQueue&& other); // move constructor
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    MyQueue& operator=(const MyQueue& other); // copy assignment operator, return *this
    MyQueue& operator=(MyQueue&& other); // move assignment operator, return *this
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    
    bool empty() const { return head == tail; }
    bool full() const { return (head + msize -1) % msize == tail; }
    std::size_t size() const { return (tail - head + msize) % msize; }
    std::size_t max_size() const { return msize-1; }

    void push(const T& item); // dodanie na koniec
    void push(T&& item); // dodanie na koniec

    T& front() { return tab[head]; } // zwraca początek
    T& back() { return tab[(tail + msize -1) % msize]; } // zwraca koniec

    void pop(); // usuwa początek
    void clear(); // czyszczenie listy z elementów
    void display();
};

// *********************** IMPLEMENTACJE ***********************

// copy constructor
template<typename T>
MyQueue<T>::MyQueue(const MyQueue& other)
    : msize(other.msize), head(other.head), tail(other.tail)
{
    tab = new T[msize];
    for (std::size_t i = 0; i < msize; ++i)
        tab[i] = other.tab[i];
}

// move constructor
template<typename T>
MyQueue<T>::MyQueue(MyQueue&& other)
    : tab(other.tab), msize(other.msize), head(other.head), tail(other.tail)
{
    other.tab = nullptr;
    other.msize = 1;
    other.head = 0;
    other.tail = 0;
}

// copy assignment operator
template<typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& other)
{
    if (this != &other) {
        delete [] tab;

        msize = other.msize;
        head = other.head;
        tail = other.tail;

        tab = new T[msize];
        for (std::size_t i = 0; i < msize; ++i)
            tab[i] = other.tab[i];
    }
    return *this;
}

// move assignment operator
template<typename T>
MyQueue<T>& MyQueue<T>::operator=(MyQueue&& other)
{
    if (this != &other) {
        delete [] tab;

        tab  = other.tab;
        msize = other.msize;
        head = other.head;
        tail = other.tail;

        other.tab = nullptr;
        other.msize = 1;
        other.head = 0;
        other.tail = 0;
    }
    return *this;
}

// push(const T&)
template<typename T>
void MyQueue<T>::push(const T& item)
{
    assert(!full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

// push(T&&)
template<typename T>
void MyQueue<T>::push(T&& item)
{
    assert(!full());
    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}

// pop()
template<typename T>
void MyQueue<T>::pop()
{
    assert(!empty());
    head = (head + 1) % msize;
}

// clear()
template<typename T>
void MyQueue<T>::clear()
{
    head = 0;
    tail = 0;
}

// display()
template<typename T>
void MyQueue<T>::display()
{
    std::cout << "[ ";
    for (std::size_t i = head; i != tail; i = (i + 1) % msize)
        std::cout << tab[i] << " ";
    std::cout << "]\n";

    std::cout << "Head: " << head 
              << ", Tail: " << tail
              << ", Size: " << size()
              << ", Empty: " << empty()
              << ", Full: " << full()
              << std::endl;
}
