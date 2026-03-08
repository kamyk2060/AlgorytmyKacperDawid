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

Po uruchomieniu zobaczysz wyniki wszystkich testów - jeśli wszystko działa, na końcu pojawi się komunikat \"WSZYSTKIE TESTY PRZESZLY POMYSLNIE!\"

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
#include \"Poly.h\"

// Wielomian zerowy (stopień 0)
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
// Dwa wielomiany są równe, gdy ich różnica jest wielomianem zerowym
if (p1 == p2) {
    cout << \"Wielomiany są równe!\" << endl;
}

if (p1 != p2) {
    cout << \"Wielomiany są różne!\" << endl;
}
```

### 5. Wyświetlanie wielomianów
```cpp
double arr[] = {1, 2, 3};
Poly<double> p(arr, 3);
cout << p << endl;  // Wyświetli: 3x^2 + 2x + 1
```

### 6. Przydatne metody pomocnicze
```cpp
// Stopień wielomianu (najwyższa potęga x z niezerowym współczynnikiem)
int stopien = p.degree();  // dla 3x² + 2x + 1 zwróci 2

// Stopień wielomianu zerowego wynosi 0
Poly<double> zero;
cout << zero.degree();  // Wypisze: 0

// Czy wielomian jest zerowy?
bool czyZerowy = p.is_zero();

// Odczyt współczynnika przy x^i (zwraca 0 jeśli brak wyrazu)
double wspolczynnik = p[2];  // współczynnik przy x²

// Wyczyść wielomian (ustaw wszystkie współczynniki na 0)
p.clear();
```

---

## Opis głównych elementów klasy

### Pola prywatne

| Pole | Typ | Opis |
|------|-----|------|
| `coeffs` | `T*` | Dynamiczna tablica przechowująca współczynniki |
| `capacity` | `int` | Aktualny rozmiar zaalokowanej tablicy |

**Uwaga:** Stopień wielomianu nie jest przechowywany jako pole - jest obliczany na żądanie przez metodę `degree()`.

### Metody publiczne

| Metoda | Opis |
|--------|------|
| `Poly()` | Konstruktor domyślny - tworzy wielomian zerowy (stopień 0) |
| `Poly(int size)` | Konstruktor tworzący wielomian o zadanym rozmiarze (wypełniony zerami) |
| `Poly(const T* arr, int size)` | Konstruktor z tablicy współczynników |
| `Poly(const Poly& other)` | Konstruktor kopiujący |
| `operator=` | Operator przypisania (podstawienie kopiujące) |
| `degree()` | Zwraca stopień wielomianu (0 dla wielomianu zerowego) |
| `is_zero()` | Sprawdza czy wszystkie współczynniki są zerowe |
| `clear()` | Czyści wielomian (ustawia wszystkie współczynniki na 0) |
| `evaluate(T x)` | Oblicza wartość wielomianu w punkcie x (algorytm Hornera) |
| `operator[](int i)` | Zwraca współczynnik przy x^i (0 jeśli poza zakresem) |
| `operator+` | Dodawanie wielomianów (współczynnik po współczynniku) |
| `operator-` | Odejmowanie wielomianów (współczynnik po współczynniku) |
| `operator*` | Mnożenie wielomianów (splot współczynników) |
| `operator==` | Porównanie - wielomiany równe gdy różnica jest wielomianem zerowym |
| `operator!=` | Porównanie - wielomiany różne gdy różnica nie jest zerem |
| `operator<<` | Wyświetlanie wielomianu w czytelnej formie (np. \"3x^2 + 2x + 1\") |

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

**Zaleta:** Mniej mnożeń = szybsze obliczenia! Algorytm wymaga tylko n mnożeń i n dodawań dla wielomianu stopnia n.

---

## Przykłady użycia

### Przykład 1: Proste działania
```cpp
// Tworzymy wielomiany: p1 = 1 + x, p2 = 1 + x
double arr1[] = {1, 1};
Poly<double> p1(arr1, 2);
Poly<double> p2(arr1, 2);

// Mnożymy: (1+x) * (1+x) = 1 + 2x + x²
Poly<double> wynik = p1 * p2;
cout << wynik << endl;  // Wypisze: x^2 + 2x + 1

// Obliczamy wartość w punkcie x=2
cout << wynik.evaluate(2) << endl;  // Wypisze: 9
```

### Przykład 2: Wielomiany całkowite
```cpp
// Wielomiany z współczynnikami całkowitymi
int arr[] = {2, 3, 1};  // 2 + 3x + x²
Poly<int> p(arr, 3);

// Oblicz p(2) = 2 + 3*2 + 4 = 12
int wartosc = p.evaluate(2);
cout << wartosc << endl;  // Wypisze: 12
```

### Przykład 3: Porównywanie przez różnicę
```cpp
double arr1[] = {1, 2, 3};
double arr2[] = {1, 2, 3};
Poly<double> p1(arr1, 3);
Poly<double> p2(arr2, 3);

// Wielomiany są równe, gdy ich różnica = 0
Poly<double> roznica = p1 - p2;
cout << roznica.is_zero() << endl;  // Wypisze: 1 (true)
cout << (p1 == p2) << endl;         // Wypisze: 1 (true)
```

---

## Szczegóły implementacji

### Przechowywanie współczynników
Wielomian `p(x) = a₀ + a₁x + a₂x² + ... + aₙxⁿ` przechowujemy jako tablicę:
```
coeffs[0] = a₀  (wyraz wolny)
coeffs[1] = a₁  (współczynnik przy x)
coeffs[2] = a₂  (współczynnik przy x²)
...
coeffs[n] = aₙ  (współczynnik przy xⁿ)
```

### Dynamiczna alokacja pamięci
- Tablica `coeffs` jest alokowana dynamicznie (operator `new`)
- Pamięć jest automatycznie zwalniana w destruktorze (operator `delete[]`)
- Klasa implementuje regułę trzech: destruktor, konstruktor kopiujący, operator przypisania

### Obliczanie stopnia wielomianu
Stopień wielomianu jest obliczany \"na żądanie\" przez przejrzenie tablicy od końca:
```cpp
// Szukamy najwyższego indeksu z niezerowym współczynnikiem
for (int i = capacity - 1; i >= 0; i--) {
    if (coeffs[i] != 0) {
        return i;  // To jest stopień
    }
}
return 0;  // Wielomian zerowy ma stopień 0
```

### Tolerancja błędu dla liczb zmiennoprzecinkowych
Przy porównywaniu współczynników typu `double`/`float` używamy małej tolerancji (`1e-10`), żeby uniknąć problemów z zaokrągleniami:
```cpp
if (std::abs(coeffs[i]) > 1e-10) {
    // Współczynnik jest niezerowy
}
```

To działa też dla typów całkowitych (`int`), bo `1e-10` jest praktycznie zerem.

---

