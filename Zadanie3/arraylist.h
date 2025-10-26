// arraylist.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()
#include <algorithm>

template <typename T>
class ArrayList {
    T* tab;
    std::size_t msize; // najwieksza mozliwa liczba elementow
    std::size_t last; // pierwsza wolna pozycja
public:
    ArrayList(std::size_t s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor
    ~ArrayList() { delete [] tab; } // destruktor

    // copy constructor
    ArrayList(const ArrayList& other) : msize(other.msize), last(other.last) {
        tab = new T[msize];
        for (std::size_t i = 0; i < last; ++i) {
            tab[i] = other.tab[i];
        }
    }
    // move constructor
    ArrayList(ArrayList&& other) : tab(other.tab), msize(other.msize), last(other.last) {
        other.tab = nullptr;
        other.msize = 0;
        other.last = 0;
    }
    // copy assignment operator
    ArrayList& operator=(const ArrayList& other) {
        if (this != &other) {
            delete [] tab;
            msize = other.msize;
            last = other.last;
            tab = new T[msize];
            for (std::size_t i = 0; i < last; ++i) {
                tab[i] = other.tab[i];
            }
        }
        return *this;
    }

    
    // move assignment operator
    ArrayList& operator=(ArrayList&& other) {
        if (this != &other) {
            delete [] tab;
            tab = other.tab;
            msize = other.msize;
            last = other.last;
            other.tab = nullptr;
            other.msize = 0;
            other.last = 0;
        }
        return *this;
    }

    bool empty() const { return last == 0; } // checks if the container has no elements
    bool full() const { return last == msize; } // checks if the container is full
    std::size_t size() const { return last; } // liczba elementow na liscie
    std::size_t max_size() const { return msize; } // najwieksza mozliwa liczba elementow
    
    void push_front(const T& item) {
         assert(!full());
        for (std::size_t i = last; i > 0; --i) {
            tab[i] = tab[i-1];
        }
        tab[0] = item;
        ++last;
    }; // dodanie na poczatek
    void push_front(T&& item) {
        assert(!full());
        for (std::size_t i = last; i > 0; --i) {
            tab[i] = std::move(tab[i-1]);
        }
        tab[0] = std::move(item);
        ++last;
    } // dodanie na poczatek NIEOBOWIAZKOWE
    void push_back(const T& item) {
        assert(!full());
        tab[last++] = item;
    } // dodanie na koniec
    void push_back(T&& item) {
        assert(!full());
        tab[last++] = std::move(item);
    }; // dodanie na koniec NIEOBOWIAZKOWE
    T& front() {
        assert(!empty());
        return tab[0];
    }; // zwraca poczatek, nie usuwa, error dla pustej listy
    T& back() {
        assert(!empty());
        return tab[last-1];
    }; // zwraca koniec, nie usuwa, error dla pustej listy
    void pop_front() {
        assert(!empty());
        for (std::size_t i = 0; i < last-1; ++i) {
            tab[i] = tab[i+1];
        }
        --last;
    }; // usuwa poczatek, error dla pustej listy
    void pop_back() {
        assert(!empty());
        --last;
    }; // usuwa koniec, error dla pustej listy
    void clear() {
        last = 0;
    }; // czyszczenie listy z elementow
    void display() {
        std::cout << *this << std::endl;
    }; // lepiej zdefiniowac operator<<
    void reverse() {
        for (std::size_t i = 0; i < last/2; ++i) {
            std::swap(tab[i], tab[last-1-i]);
        }
    }; // odwracanie kolejnosci
    void sort() {
        if (last > 1) {
            std::sort(tab, tab + last);
        }
    }; // sortowanie listy
    void merge(ArrayList& other) {
    
    if (this == &other) {
        return;
    }
    
    
    if (size() + other.size() > max_size()) {
        std::cerr << "Error: Not enough space to merge lists!" << std::endl;
        return;
    }
    
    
    for (std::size_t i = 0; i < other.size(); ++i) {
        push_back(other.tab[i]);
    }
    other.clear();
    sort();
    }; //  merges two sorted lists into one NIEOBOWIAZKOWE

    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator
    T& operator[](std::size_t pos) {
        assert(pos < last);
        return tab[pos];
    }; // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](std::size_t pos) const {
        assert(pos < last);
        return tab[pos];
    }; // dostep do obiektu const
    void erase(std::size_t pos) {
        assert(pos < last);
        for (std::size_t i = pos; i < last-1; ++i) {
            tab[i] = tab[i+1];
        }
        --last;
    }; // usuniecie elementu na pozycji pos
    int index(const T& item) {
        for (std::size_t i = 0; i < last; ++i) {
            if (tab[i] == item) {
                return i;
            }
        }
        return -1;
    }; // jaki index na liscie (-1 gdy nie ma)
    void insert(std::size_t pos, const T& item) {
        assert(!full() && pos <= last);
        for (std::size_t i = last; i > pos; --i) {
            tab[i] = tab[i-1];
        }
        tab[pos] = item;
        ++last;
    }; // inserts item before pos
    void insert(std::size_t pos, T&& item) {
        assert(!full() && pos <= last);
        for (std::size_t i = last; i > pos; --i) {
            tab[i] = std::move(tab[i-1]);
        }
        tab[pos] = std::move(item);
        ++last;
    }; // inserts item before pos
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (std::size_t i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif

// EOF
