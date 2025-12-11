#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <iostream>
#include <cassert>
#include <cstddef>
#include <utility>

template <typename T>
class MyDeque {
    T* tab;
    std::size_t msize; 
    std::size_t head; 
    std::size_t tail; 
    
public:
    MyDeque(std::size_t s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[msize];
        assert(tab != nullptr);
    }
    
    ~MyDeque() { delete [] tab; }

    // Copy constructor
    MyDeque(const MyDeque& other)
        : msize(other.msize), head(other.head), tail(other.tail)
    {
        tab = new T[msize];
        for (std::size_t i = 0; i < msize; ++i)
            tab[i] = other.tab[i];
    }

    // Move constructor – poprawiony
    MyDeque(MyDeque&& other) noexcept
        : tab(other.tab), msize(other.msize), head(other.head), tail(other.tail)
    {
        other.tab = nullptr;
        other.msize = 1;
        other.head = 0;
        other.tail = 0;
    }

    // Copy assignment
    MyDeque& operator=(const MyDeque& other) {
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

    // Move assignment – poprawiony
    MyDeque& operator=(MyDeque&& other) noexcept {
        if (this != &other) {
            delete [] tab;
            tab = other.tab;
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

    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }
    std::size_t size() const { return (tail - head + msize) % msize; }
    std::size_t max_size() const { return msize - 1; }

    void push_front(const T& item);
    void push_front(T&& item);
    void push_back(const T& item);
    void push_back(T&& item);

    T& front() { return tab[head]; }
    const T& front() const { return tab[head]; }

    T& back() { return tab[(tail + msize - 1) % msize]; }
    const T& back() const { return tab[(tail + msize - 1) % msize]; }

    void pop_front();
    void pop_back();
    void clear() { head = tail = 0; }

    void display();
    void display_reversed();

    T& operator[](std::size_t pos);
    const T& operator[](std::size_t pos) const;

    void erase(std::size_t pos);
    int index(const T& item);

    void insert(std::size_t pos, const T& item);
    void insert(std::size_t pos, T&& item);
};

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    assert(!full());
    head = (head + msize - 1) % msize;
    tab[head] = item;
}

template <typename T>
void MyDeque<T>::push_front(T&& item) {
    assert(!full());
    head = (head + msize - 1) % msize;
    tab[head] = std::move(item);
}

template <typename T>
void MyDeque<T>::push_back(const T& item) {
    assert(!full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::push_back(T&& item) {
    assert(!full());
    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_front() {
    assert(!empty());
    head = (head + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_back() {
    assert(!empty());
    tail = (tail + msize - 1) % msize;
}

template <typename T>
void MyDeque<T>::display() {
    for (std::size_t i = head; i != tail; i = (i + 1) % msize)
        std::cout << tab[i] << " ";
    std::cout << std::endl;
}

template <typename T>
void MyDeque<T>::display_reversed() {
    if (empty()) {
        std::cout << "pusta\n";
        return;
    }
    std::size_t i = (tail + msize - 1) % msize;
    while (true) {
        std::cout << tab[i] << " ";
        if (i == head) break;
        i = (i + msize - 1) % msize;
    }
    std::cout << std::endl;
}

template <typename T>
T& MyDeque<T>::operator[](std::size_t pos) {
    assert(pos < size());
    return tab[(head + pos) % msize];
}

template <typename T>
const T& MyDeque<T>::operator[](std::size_t pos) const {
    assert(pos < size());
    return tab[(head + pos) % msize];
}

template <typename T>
void MyDeque<T>::erase(std::size_t pos) {
    assert(pos < size());

    if (pos == 0) { pop_front(); return; }
    if (pos == size() - 1) { pop_back(); return; }

    std::size_t n = size();

    for (std::size_t i = pos; i < n - 1; ++i) {
        (*this)[i] = std::move((*this)[i + 1]);
    }

    tail = (tail + msize - 1) % msize;
}

template <typename T>
int MyDeque<T>::index(const T& item) {
    for (std::size_t i = 0; i < size(); ++i)
        if ((*this)[i] == item)
            return static_cast<int>(i);
    return -1;
}

template <typename T>
void MyDeque<T>::insert(std::size_t pos, const T& item) {
    assert(!full());
    assert(pos <= size());

    if (pos == 0) { push_front(item); return; }
    if (pos == size()) { push_back(item); return; }

    push_back(back()); // zwiększ rozmiar

    for (std::size_t i = size() - 1; i > pos; --i)
        (*this)[i] = (*this)[i - 1];

    (*this)[pos] = item;
}

template <typename T>
void MyDeque<T>::insert(std::size_t pos, T&& item) {
    assert(!full());
    assert(pos <= size());

    if (pos == 0) { push_front(std::move(item)); return; }
    if (pos == size()) { push_back(std::move(item)); return; }

    push_back(back());

    for (std::size_t i = size() - 1; i > pos; --i)
        (*this)[i] = std::move((*this)[i - 1]);

    (*this)[pos] = std::move(item);
}

#endif // MYDEQUE_H
