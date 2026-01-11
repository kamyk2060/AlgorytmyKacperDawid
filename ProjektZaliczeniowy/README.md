# Projekt: Wielomiany w C++ (klasa Poly)

## Opis projektu

Ten projekt to implementacja klasy szablonowej `Poly<T>` reprezentującej wielomiany matematyczne. Klasa pozwala na przechowywanie wielomianów z współczynnikami dowolnego typu liczbowego (int, double, float itp.) oraz wykonywanie na nich podstawowych operacji matematycznych.

**Przykład wielomianu:**
```
p(x) = 3x² + 2x + 1
```
W programie przechowujemy go jako tablicę współczynników: `[1, 2, 3]` (od wyrazu wolnego).

---

## Jak uruchomić?

### Wymagania
- Kompilator C++ wspierający standard C++11 lub nowszy (np. g++, clang++)
- System Linux/Windows/Mac

### Kompilacja i uruchomienie

```bash
# Kompilacja
g++ -o test_poly main.cpp -std=c++17

# Uruchomienie testów
./test_poly
```

Po uruchomieniu zobaczysz wyniki wszystkich testów - jeśli wszystko działa, na końcu pojawi się komunikat "WSZYSTKIE TESTY PRZESZLY POMYSLNIE!"

---

## Struktura projektu

```
projekt/
├── Poly.h      # Główna klasa wielomianów (cała implementacja)
├── main.cpp    # Program testujący z przykładami użycia
└── README.md   # Ta dokumentacja
```

---

## Jak używać klasy Poly?

### 1. Tworzenie wielomianów

```cpp
#include "Poly.h"

// Wielomian zerowy
Poly<double> p1;

// Wielomian z tablicy współczynników
// arr[0] = wyraz wolny, arr[1] = współczynnik przy x, itd.
double arr[] = {1, 2, 3};  // reprezentuje: 1 + 2x + 3x²
Poly<double> p2(arr, 3);

// Kopia wielomianu
Poly<double> p3(p2);
```

### 2. Podstawowe operacje

```cpp
// Dodawanie wielomianów
Poly<double> suma = p1 + p2;

// Odejmowanie wielomianów
Poly<double> roznica = p1 - p2;

// Mnożenie wielomianów
Poly<double> iloczyn = p1 * p2;
```

### 3. Obliczanie wartości (algorytm Hornera)

```cpp
// p(x) = 1 + 2x + 3x²
double arr[] = {1, 2, 3};
Poly<double> p(arr, 3);

// Oblicz p(2) = 1 + 2*2 + 3*4 = 1 + 4 + 12 = 17
double wynik = p.evaluate(2);  // wynik = 17
```

### 4. Porównywanie wielomianów

```cpp
// Dwa wielomiany są równe, gdy ich różnica = 0
if (p1 == p2) {
    cout << "Wielomiany są równe!" << endl;
}

if (p1 != p2) {
    cout << "Wielomiany są różne!" << endl;
}
```

### 5. Wyświetlanie wielomianów

```cpp
Poly<double> p(arr, 3);
cout << p << endl;  // Wyświetli np.: 3x^2 + 2x + 1
```

### 6. Przydatne metody pomocnicze

```cpp
// Stopień wielomianu (najwyższa potęga x)
int stopien = p.degree();  // dla 3x² + 2x + 1 zwróci 2

// Czy wielomian jest zerowy?
bool czyZerowy = p.is_zero();

// Odczyt współczynnika przy x^i
double wspolczynnik = p[2];  // współczynnik przy x²

// Wyczyść wielomian (ustaw na zero)
p.clear();
```

---

## Opis głównych elementów klasy

### Pola prywatne

| Pole | Typ | Opis |
|------|-----|------|
| `coeffs` | `T*` | Dynamiczna tablica przechowująca współczynniki |
| `capacity` | `int` | Aktualny rozmiar tablicy |
| `deg` | `int` | Stopień wielomianu (-1 dla wielomianu zerowego) |

### Metody publiczne

| Metoda | Opis |
|--------|------|
| `Poly()` | Konstruktor domyślny - tworzy wielomian zerowy |
| `Poly(const T* arr, int size)` | Konstruktor z tablicy współczynników |
| `Poly(const Poly& other)` | Konstruktor kopiujący |
| `degree()` | Zwraca stopień wielomianu |
| `is_zero()` | Sprawdza czy wielomian jest zerowy |
| `clear()` | Czyści wielomian (ustawia na zero) |
| `evaluate(T x)` | Oblicza wartość wielomianu w punkcie x |
| `operator[]` | Zwraca współczynnik przy danej potędze |
| `operator+` | Dodawanie wielomianów |
| `operator-` | Odejmowanie wielomianów |
| `operator*` | Mnożenie wielomianów |
| `operator==` | Porównanie (równość) |
| `operator!=` | Porównanie (nierówność) |
| `operator<<` | Wyświetlanie wielomianu |

---

## Algorytm Hornera - jak to działa?

Algorytm Hornera to sprytny sposób na obliczanie wartości wielomianu. Zamiast obliczać każdą potęgę osobno, przekształcamy wielomian:

**Standardowo:**
```
p(x) = a₀ + a₁x + a₂x² + a₃x³
```

**Metodą Hornera:**
```
p(x) = a₀ + x(a₁ + x(a₂ + x·a₃))
```

**Przykład dla p(x) = 1 + 2x + 3x², obliczamy p(2):**
1. Zaczynamy od najwyższego współczynnika: `wynik = 3`
2. Mnożymy przez x i dodajemy następny: `wynik = 3*2 + 2 = 8`
3. Mnożymy przez x i dodajemy następny: `wynik = 8*2 + 1 = 17`

Zaleta: mniej mnożeń = szybsze obliczenia!

---

## Przykładowe uruchomienie

```
+----------------------------------------+
|  PROGRAM TESTUJACY KLASE WIELOMIANOW  |
+----------------------------------------+

=== TEST KONSTRUKTOROW ===
[OK] Konstruktor domyslny dziala
[OK] Konstruktor z tablicy dziala
  p2 = 3x^2 + 2x + 1
[OK] Konstruktor kopiujacy dziala

=== TEST DODAWANIA ===
p1 = 2x + 1
p2 = 4x + 3
p1 + p2 = 6x + 4
[OK] Dodawanie dziala poprawnie

=== TEST MNOZENIA ===
p1 = x + 1
p2 = x + 1
p1 * p2 = x^2 + 2x + 1
[OK] Mnozenie dziala poprawnie

... (więcej testów)

+----------------------------------------+
|   WSZYSTKIE TESTY PRZESZLY POMYSLNIE!  |
+----------------------------------------+
```

---

## Uwagi techniczne

1. **Dlaczego szablon?** - Dzięki `template<typename T>` możemy używać wielomianów z różnymi typami liczbowymi (int, double, float).

2. **Dlaczego implementacja w .h?** - Szablony w C++ wymagają, żeby implementacja była widoczna w momencie kompilacji, dlatego wszystko jest w pliku nagłówkowym.

3. **Wielomian zerowy** - Ma stopień -1 (konwencja), bo wielomian zerowy nie ma żadnego niezerowego współczynnika.

4. **Porównywanie wielomianów** - Dwa wielomiany są równe, gdy ich różnica jest wielomianem zerowym. To eleganckie rozwiązanie, bo nie musimy porównywać współczynnik po współczynniku.

---

## Autor

Projekt wykonany w ramach zajęć z programowania obiektowego.
