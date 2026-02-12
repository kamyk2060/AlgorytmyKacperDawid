#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <cmath>

// Szablon klasy reprezentujacej wielomian
// T - typ wspolczynnikow (np. int, double, float)
template<typename T>
class Poly {
private:
    T* coeffs;       // Tablica wspolczynnikow
    int capacity;    // Rozmiar zaalokowanej tablicy
    int deg;         // Stopien wielomianu (-1 dla wielomianu zerowego)

    // Zmienia rozmiar tablicy wspolczynnikow
    void resize(int new_capacity);
    
    // Aktualizuje stopien wielomianu (znajduje najwyzsza potege)
    void update_degree();

public:
    // Konstruktor domyslny - tworzy wielomian zerowy
    Poly();
    
    // Konstruktor z podanym rozmiarem
    Poly(int size);
    
    // Konstruktor z tablicy wspolczynnikow
    // arr[0] to wyraz wolny, arr[1] to wspolczynnik przy x, itd.
    Poly(const T* arr, int size);
    
    // Konstruktor kopiujacy
    Poly(const Poly& other);
    
    // Destruktor - zwalnia pamiec
    ~Poly();
    
    // Operator przypisania
    Poly& operator=(const Poly& other);
    
    // Czysci wielomian (ustawia wszystkie wspolczynniki na 0)
    void clear();
    
    // Sprawdza czy wielomian jest zerowy
    bool is_zero() const;
    
    // Zwraca stopien wielomianu
    int degree() const;
    
    // Operator [] - zwraca wspolczynnik przy x^index (tylko odczyt)
    T operator[](int index) const;
    
    // Metoda do modyfikacji wspolczynnika
    T& at(int index);
    
    // Oblicza wartosc wielomianu w punkcie x (algorytm Hornera)
    T evaluate(T x) const;
    
    // Operator dodawania
    Poly operator+(const Poly& other) const;
    
    // Operator odejmowania
    Poly operator-(const Poly& other) const;
    
    // Operator mnozenia
    Poly operator*(const Poly& other) const;
    
    // Operator porownania (rownosc)
    bool operator==(const Poly& other) const;
    
    // Operator porownania (nierownosc)
    bool operator!=(const Poly& other) const;
    
    // Deklaracja operatora wyswietlania
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Poly<U>& poly);
};

// Implementacja metod 

template<typename T>
void Poly<T>::resize(int new_capacity) {
    // Tworzymy nowa tablice o wiekszym rozmiarze
    T* new_coeffs = new T[new_capacity];
    
    // Kopiujemy stare wartosci
    int copy_size = (capacity < new_capacity) ? capacity : new_capacity;
    for (int i = 0; i < copy_size; i++) {
        new_coeffs[i] = coeffs[i];
    }
    
    // Inicjalizujemy nowe elementy zerami
    for (int i = capacity; i < new_capacity; i++) {
        new_coeffs[i] = T(0);
    }
    
    // Usuwamy stara tablice
    delete[] coeffs;
    
    // Podmieniamy wskazniki
    coeffs = new_coeffs;
    capacity = new_capacity;
}

template<typename T>
void Poly<T>::update_degree() {
    // Szukamy najwyzszego niezerowego wspolczynnika
    deg = -1; // Zakladamy wielomian zerowy
    
    for (int i = capacity - 1; i >= 0; i--) {
        // Sprawdzamy czy wspolczynnik jest rozny od zera
        if (std::abs(coeffs[i]) > 1e-10) {
            deg = i;
            break;
        }
    }
}

template<typename T>
Poly<T>::Poly() : capacity(1), deg(-1) {
    // Tworzymy wielomian zerowy
    coeffs = new T[1];
    coeffs[0] = T(0);
}

template<typename T>
Poly<T>::Poly(int size) : capacity(size > 0 ? size : 1), deg(-1) {
    // Tworzymy tablice wypelniona zerami
    coeffs = new T[capacity];
    for (int i = 0; i < capacity; i++) {
        coeffs[i] = T(0);
    }
}

template<typename T>
Poly<T>::Poly(const T* arr, int size) : capacity(size > 0 ? size : 1), deg(-1) {
    // Kopiujemy wspolczynniki z tablicy
    coeffs = new T[capacity];
    for (int i = 0; i < size; i++) {
        coeffs[i] = arr[i];
    }
    // Obliczamy stopien wielomianu
    update_degree();
}

template<typename T>
Poly<T>::Poly(const Poly& other) : capacity(other.capacity), deg(other.deg) {
    // Kopiujemy wszystkie dane z innego wielomianu
    coeffs = new T[capacity];
    for (int i = 0; i < capacity; i++) {
        coeffs[i] = other.coeffs[i];
    }
}

template<typename T>
Poly<T>::~Poly() {
    // Zwalniamy pamiec
    delete[] coeffs;
}

template<typename T>
Poly<T>& Poly<T>::operator=(const Poly& other) {
    // Sprawdzamy czy nie przypisujemy do samego siebie
    if (this != &other) {
        // Zwalniamy stara pamiec
        delete[] coeffs;
        
        // Kopiujemy dane
        capacity = other.capacity;
        deg = other.deg;
        coeffs = new T[capacity];
        for (int i = 0; i < capacity; i++) {
            coeffs[i] = other.coeffs[i];
        }
    }
    return *this;
}

template<typename T>
void Poly<T>::clear() {
    // Ustawiamy wszystkie wspolczynniki na 0
    for (int i = 0; i < capacity; i++) {
        coeffs[i] = T(0);
    }
    deg = -1;
}

template<typename T>
bool Poly<T>::is_zero() const {
    // Wielomian zerowy ma stopien -1
    return deg == -1;
}

template<typename T>
int Poly<T>::degree() const {
    return deg;
}

template<typename T>
T Poly<T>::operator[](int index) const {
    // Zwracamy wspolczynnik lub 0 jesli poza zakresem
    if (index < 0 || index >= capacity) {
        return T(0);
    }
    return coeffs[index];
}

template<typename T>
T& Poly<T>::at(int index) {
    // Powiekszamy tablice jesli trzeba
    if (index >= capacity) {
        resize(index + 1);
    }
    return coeffs[index];
}

template<typename T>
T Poly<T>::evaluate(T x) const {
    // Algorytm Hornera: oblicza wartosc wielomianu wydajnie
    // Dla wielomianu a0 + a1*x + a2*x^2 + ... + an*x^n
    // Oblicza: a0 + x*(a1 + x*(a2 + x*(...)))
    
    if (is_zero()) {
        return T(0);
    }
    
    // Zaczynamy od najwyzszego wspolczynnika
    T result = coeffs[deg];
    
    // Idziemy w dol poteg
    for (int i = deg - 1; i >= 0; i--) {
        result = result * x + coeffs[i];
    }
    
    return result;
}

template<typename T>
Poly<T> Poly<T>::operator+(const Poly& other) const {
    // Dodajemy dwa wielomiany wspolczynnik po wspolczynniku
    
    // Wynikowy wielomian musi miec rozmiar wiekszego z dwoch
    int max_size = (capacity > other.capacity) ? capacity : other.capacity;
    Poly result(max_size);
    
    // Dodajemy odpowiednie wspolczynniki
    for (int i = 0; i < max_size; i++) {
        T a = (i < capacity) ? coeffs[i] : T(0);
        T b = (i < other.capacity) ? other.coeffs[i] : T(0);
        result.at(i) = a + b;
    }
    
    // Aktualizujemy stopien
    result.update_degree();
    return result;
}

template<typename T>
Poly<T> Poly<T>::operator-(const Poly& other) const {
    // Odejmujemy dwa wielomiany wspolczynnik po wspolczynniku
    
    int max_size = (capacity > other.capacity) ? capacity : other.capacity;
    Poly result(max_size);
    
    for (int i = 0; i < max_size; i++) {
        T a = (i < capacity) ? coeffs[i] : T(0);
        T b = (i < other.capacity) ? other.coeffs[i] : T(0);
        result.at(i) = a - b;
    }
    
    result.update_degree();
    return result;
}

template<typename T>
Poly<T> Poly<T>::operator*(const Poly& other) const {
    // Mnozymy dwa wielomiany
    // (a0 + a1*x + ...) * (b0 + b1*x + ...) = suma wszystkich ai*bj*x^(i+j)
    
    if (is_zero() || other.is_zero()) {
        return Poly(); // Zwracamy wielomian zerowy
    }
    
    // Stopien iloczynu to suma stopni
    int result_size = deg + other.deg + 1;
    Poly result(result_size);
    
    // Mnozymy kazdy wspolczynnik z kazdym
    for (int i = 0; i <= deg; i++) {
        for (int j = 0; j <= other.deg; j++) {
            // ai * bj dodajemy do wspolczynnika przy x^(i+j)
            result.at(i + j) = result.at(i + j) + coeffs[i] * other.coeffs[j];
        }
    }
    
    result.update_degree();
    return result;
}

template<typename T>
bool Poly<T>::operator==(const Poly& other) const {
    // Dwa wielomiany sa rowne, gdy ich roznica jest zerem
    Poly diff = *this - other;
    return diff.is_zero();
}

template<typename T>
bool Poly<T>::operator!=(const Poly& other) const {
    return !(*this == other);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Poly<T>& poly) {
    // Wyswietlamy wielomian w czytelnej formie
    
    if (poly.is_zero()) {
        os << "0";
        return os;
    }
    
    bool first = true; // Czy to pierwszy wyraz?
    
    // Przechodzimy od najwyzszej potegi do najnizszej
    for (int i = poly.deg; i >= 0; i--) {
        // Pomijamy zerowe wspolczynniki
        if (std::abs(poly.coeffs[i]) > 1e-10) {
            
            // Wyswietlamy znak
            if (!first && poly.coeffs[i] > 0) {
                os << " + ";
            } else if (poly.coeffs[i] < 0) {
                os << (first ? "-" : " - ");
            }
            
            T coeff = std::abs(poly.coeffs[i]);
            
            // Wyswietlamy wspolczynnik
            if (i == 0) {
                // Dla wyrazu wolnego zawsze pokazujemy wartosc
                os << coeff;
            } else if (std::abs(coeff - 1.0) > 1e-10) {
                // Dla innych - tylko jesli rozny od 1
                os << coeff;
            }
            
            // Wyswietlamy zmienna i potege
            if (i > 0) {
                os << "x";
                if (i > 1) {
                    os << "^" << i;
                }
            }
            
            first = false;
        }
    }
    
    return os;
}

#endif // POLY_H