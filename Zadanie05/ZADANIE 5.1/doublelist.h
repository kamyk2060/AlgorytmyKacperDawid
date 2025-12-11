// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList& other); // copy constructor
    // usage:   DoubleList<int> list2(list1);

    DoubleList(DoubleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));

    DoubleList& operator=(const DoubleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    std::size_t size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1)
    void push_back(T&& item); // O(1) NIEOBOWIAZKOWE
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(1)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](std::size_t pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](std::size_t pos) const; // dostep do obiektu const
    void erase(std::size_t pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(std::size_t pos, const T& item); // inserts item before pos,
    void insert(std::size_t pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
DoubleList<T>::~DoubleList() {
    clear();
}

template <typename T>
DoubleList<T>::DoubleList(const DoubleList& other) : head(nullptr), tail(nullptr) {
    DoubleNode<T>* current = other.head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}

template <typename T>
DoubleList<T>::DoubleList(DoubleList&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& other) {
    if (this != &other) {
        clear();
        DoubleNode<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(DoubleList&& other) {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}

template <typename T>
std::size_t DoubleList<T>::size() const {
    std::size_t count = 0;
    DoubleNode<T>* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template <typename T>
void DoubleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new DoubleNode<T>(item, nullptr, tail);
        tail = tail->next;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_back(T&& item) {
    if (!empty()) {
        tail->next = new DoubleNode<T>(std::move(item), nullptr, tail);
        tail = tail->next;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template <typename T>
void DoubleList<T>::pop_front() {
    if (!empty()) {
        DoubleNode<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
    }
}

template <typename T>
void DoubleList<T>::pop_back() {
    if (!empty()) {
        DoubleNode<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
    }
}

template <typename T>
void DoubleList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
void DoubleList<T>::display() {
    DoubleNode<T>* current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
void DoubleList<T>::display_reversed() {
    DoubleNode<T>* current = tail;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->prev;
    }
    std::cout << std::endl;
}

template <typename T>
T& DoubleList<T>::operator[](std::size_t pos) {
    assert(pos < size());
    DoubleNode<T>* current = head;
    for (std::size_t i = 0; i < pos; i++) {
        current = current->next;
    }
    return current->value;
}

template <typename T>
const T& DoubleList<T>::operator[](std::size_t pos) const {
    assert(pos < size());
    DoubleNode<T>* current = head;
    for (std::size_t i = 0; i < pos; i++) {
        current = current->next;
    }
    return current->value;
}

template <typename T>
void DoubleList<T>::erase(std::size_t pos) {
    assert(pos < size());
    
    if (pos == 0) {
        pop_front();
        return;
    }
    
    if (pos == size() - 1) {
        pop_back();
        return;
    }
    
    DoubleNode<T>* current = head;
    for (std::size_t i = 0; i < pos; i++) {
        current = current->next;
    }
    
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
}

template <typename T>
int DoubleList<T>::index(const T& item) {
    DoubleNode<T>* current = head;
    int idx = 0;
    while (current != nullptr) {
        if (current->value == item) {
            return idx;
        }
        current = current->next;
        idx++;
    }
    return -1;
}

template <typename T>
void DoubleList<T>::insert(std::size_t pos, const T& item) {
    assert(pos <= size());
    
    if (pos == 0) {
        push_front(item);
        return;
    }
    
    if (pos == size()) {
        push_back(item);
        return;
    }
    
    DoubleNode<T>* current = head;
    for (std::size_t i = 0; i < pos; i++) {
        current = current->next;
    }
    
    DoubleNode<T>* newNode = new DoubleNode<T>(item, current, current->prev);
    current->prev->next = newNode;
    current->prev = newNode;
}

template <typename T>
void DoubleList<T>::insert(std::size_t pos, T&& item) {
    assert(pos <= size());
    
    if (pos == 0) {
        push_front(std::move(item));
        return;
    }
    
    if (pos == size()) {
        push_back(std::move(item));
        return;
    }
    
    DoubleNode<T>* current = head;
    for (std::size_t i = 0; i < pos; i++) {
        current = current->next;
    }
    
    DoubleNode<T>* newNode = new DoubleNode<T>(std::move(item), current, current->prev);
    current->prev->next = newNode;
    current->prev = newNode;
}

#endif

// EOF