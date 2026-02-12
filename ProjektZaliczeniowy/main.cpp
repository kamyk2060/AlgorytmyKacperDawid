#include <iostream>
#include <cassert>
#include <cmath>
#include "Poly.h"

using namespace std;

// Funkcja pomocnicza do porownywania liczb zmiennoprzecinkowych
bool isEqual(double a, double b, double epsilon = 1e-9) {
    return abs(a - b) < epsilon;
}

void testKonstruktory() {
    cout << "\n=== TEST KONSTRUKTOROW ===" << endl;
    
    // Test konstruktora domyslnego
    Poly<double> p1;
    assert(p1.is_zero());
    assert(p1.degree() == -1);
    cout << "[OK] Konstruktor domyslny dziala" << endl;
    
    // Test konstruktora z tablicy
    double arr[] = {1, 2, 3}; // 1 + 2x + 3x^2
    Poly<double> p2(arr, 3);
    assert(p2.degree() == 2);
    assert(p2[0] == 1);
    assert(p2[1] == 2);
    assert(p2[2] == 3);
    cout << "[OK] Konstruktor z tablicy dziala" << endl;
    cout << "  p2 = " << p2 << endl;
    
    // Test konstruktora kopiujacego
    Poly<double> p3(p2);
    assert(p3 == p2);
    assert(p3.degree() == 2);
    cout << "[OK] Konstruktor kopiujacy dziala" << endl;
}

void testDodawanie() {
    cout << "\n=== TEST DODAWANIA ===" << endl;
    
    // p1 = 1 + 2x
    double arr1[] = {1, 2};
    Poly<double> p1(arr1, 2);
    
    // p2 = 3 + 4x
    double arr2[] = {3, 4};
    Poly<double> p2(arr2, 2);
    
    // p1 + p2 = 4 + 6x
    Poly<double> sum = p1 + p2;
    assert(sum[0] == 4);
    assert(sum[1] == 6);
    assert(sum.degree() == 1);
    
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p1 + p2 = " << sum << endl;
    cout << "[OK] Dodawanie dziala poprawnie" << endl;
    
    // Test dodawania wielomianow roznych stopni
    double arr3[] = {1, 1, 1}; // 1 + x + x^2
    Poly<double> p3(arr3, 3);
    Poly<double> sum2 = p1 + p3;
    cout << "p1 + (1 + x + x^2) = " << sum2 << endl;
    cout << "[OK] Dodawanie roznych stopni dziala" << endl;
}

void testOdejmowanie() {
    cout << "\n=== TEST ODEJMOWANIA ===" << endl;
    
    // p1 = 5 + 3x
    double arr1[] = {5, 3};
    Poly<double> p1(arr1, 2);
    
    // p2 = 2 + 1x
    double arr2[] = {2, 1};
    Poly<double> p2(arr2, 2);
    
    // p1 - p2 = 3 + 2x
    Poly<double> diff = p1 - p2;
    assert(diff[0] == 3);
    assert(diff[1] == 2);
    
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p1 - p2 = " << diff << endl;
    cout << "[OK] Odejmowanie dziala poprawnie" << endl;
    
    // Test: wielomian - sam siebie = 0
    Poly<double> zero = p1 - p1;
    assert(zero.is_zero());
    cout << "p1 - p1 = " << zero << " (wielomian zerowy)" << endl;
    cout << "[OK] Odejmowanie daje wielomian zerowy" << endl;
}

void testMnozenie() {
    cout << "\n=== TEST MNOZENIA ===" << endl;
    
    // p1 = 1 + x
    double arr1[] = {1, 1};
    Poly<double> p1(arr1, 2);
    
    // p2 = 1 + x
    double arr2[] = {1, 1};
    Poly<double> p2(arr2, 2);
    
    // (1+x) * (1+x) = 1 + 2x + x^2
    Poly<double> product = p1 * p2;
    assert(product[0] == 1);
    assert(product[1] == 2);
    assert(product[2] == 1);
    assert(product.degree() == 2);
    
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p1 * p2 = " << product << endl;
    cout << "[OK] Mnozenie dziala poprawnie" << endl;
    
    // Test: (x-1) * (x+1) = x^2 - 1
    double arr3[] = {-1, 1}; // -1 + x
    double arr4[] = {1, 1};  // 1 + x
    Poly<double> p3(arr3, 2);
    Poly<double> p4(arr4, 2);
    Poly<double> product2 = p3 * p4;
    
    cout << "(-1 + x) * (1 + x) = " << product2 << endl;
    assert(product2[0] == -1);
    assert(product2[1] == 0);
    assert(product2[2] == 1);
    cout << "[OK] Mnozenie (x-1)(x+1) = x^2-1 dziala" << endl;
}

void testAlgorytmHornera() {
    cout << "\n=== TEST ALGORYTMU HORNERA ===" << endl;
    
    // p(x) = 1 + 2x + 3x^2
    double arr[] = {1, 2, 3};
    Poly<double> p(arr, 3);
    
    // p(0) = 1
    double val0 = p.evaluate(0);
    assert(isEqual(val0, 1.0));
    cout << "p(x) = " << p << endl;
    cout << "p(0) = " << val0 << endl;
    
    // p(1) = 1 + 2*1 + 3*1^2 = 6
    double val1 = p.evaluate(1);
    assert(isEqual(val1, 6.0));
    cout << "p(1) = " << val1 << endl;
    
    // p(2) = 1 + 2*2 + 3*4 = 1 + 4 + 12 = 17
    double val2 = p.evaluate(2);
    assert(isEqual(val2, 17.0));
    cout << "p(2) = " << val2 << endl;
    
    cout << "[OK] Algorytm Hornera dziala poprawnie" << endl;
}

void testPorownaniaRownosc() {
    cout << "\n=== TEST POROWNAN ===" << endl;
    
    // Dwa identyczne wielomiany
    double arr1[] = {1, 2, 3};
    Poly<double> p1(arr1, 3);
    Poly<double> p2(arr1, 3);
    
    assert(p1 == p2);
    assert(!(p1 != p2));
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "[OK] Rownosc dziala (p1 == p2)" << endl;
    
    // Rozne wielomiany
    double arr3[] = {1, 2, 4};
    Poly<double> p3(arr3, 3);
    
    assert(p1 != p3);
    assert(!(p1 == p3));
    cout << "p3 = " << p3 << endl;
    cout << "[OK] Nierownosc dziala (p1 != p3)" << endl;
    
    // Porownanie przez roznice
    // p1 - p2 powinno dac wielomian zerowy
    Poly<double> diff = p1 - p2;
    assert(diff.is_zero());
    cout << "[OK] Rownosc przez roznice dziala" << endl;
}

void testMetodyPomocnicze() {
    cout << "\n=== TEST METOD POMOCNICZYCH ===" << endl;
    
    double arr[] = {1, 0, 3, 0, 5}; // 1 + 3x^2 + 5x^4
    Poly<double> p(arr, 5);
    
    // Test degree()
    assert(p.degree() == 4);
    cout << "p = " << p << endl;
    cout << "Stopien wielomianu: " << p.degree() << endl;
    cout << "[OK] Funkcja degree() dziala" << endl;
    
    // Test operator[]
    assert(p[0] == 1);
    assert(p[2] == 3);
    assert(p[4] == 5);
    assert(p[1] == 0); // Wspolczynnik zerowy
    cout << "p[0] = " << p[0] << endl;
    cout << "p[2] = " << p[2] << endl;
    cout << "p[4] = " << p[4] << endl;
    cout << "[OK] Operator [] dziala" << endl;
    
    // Test clear()
    Poly<double> p2(arr, 5);
    p2.clear();
    assert(p2.is_zero());
    assert(p2.degree() == -1);
    cout << "[OK] Funkcja clear() dziala" << endl;
    
    // Test is_zero()
    Poly<double> zero;
    assert(zero.is_zero());
    cout << "[OK] Funkcja is_zero() dziala" << endl;
}

void testZlozoneOperacje() {
    cout << "\n=== TEST ZLOZONYCH OPERACJI ===" << endl;
    
    // (x+1)^3 = x^3 + 3x^2 + 3x + 1
    double arr[] = {1, 1}; // x + 1
    Poly<double> p(arr, 2);
    
    Poly<double> p2 = p * p;      // (x+1)^2
    Poly<double> p3 = p2 * p;     // (x+1)^3
    
    cout << "(x+1)^2 = " << p2 << endl;
    cout << "(x+1)^3 = " << p3 << endl;
    
    // Sprawdzamy wspolczynniki (x+1)^3
    assert(p3[0] == 1);  // 1
    assert(p3[1] == 3);  // 3x
    assert(p3[2] == 3);  // 3x^2
    assert(p3[3] == 1);  // x^3
    
    cout << "[OK] (x+1)^3 obliczone poprawnie" << endl;
    
    // Test: p(x) * 0 = 0
    Poly<double> zero;
    Poly<double> result = p * zero;
    assert(result.is_zero());
    cout << "[OK] Mnozenie przez zero dziala" << endl;
}

void testWielomianyCalkowite() {
    cout << "\n=== TEST WIELOMIANOW CALKOWITYCH ===" << endl;
    
    // Wielomiany z wspolczynnikami calkowitymi
    int arr1[] = {2, 3, 1}; // 2 + 3x + x^2
    int arr2[] = {1, -1};   // 1 - x
    
    Poly<int> p1(arr1, 3);
    Poly<int> p2(arr2, 2);
    
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    
    Poly<int> sum = p1 + p2;
    Poly<int> product = p1 * p2;
    
    cout << "p1 + p2 = " << sum << endl;
    cout << "p1 * p2 = " << product << endl;
    
    // Test ewaluacji
    int val = p1.evaluate(2); // 2 + 3*2 + 2^2 = 2 + 6 + 4 = 12
    assert(val == 12);
    cout << "p1(2) = " << val << endl;
    
    cout << "[OK] Wielomiany calkowite dzialaja" << endl;
}

int main() {
    cout << "+----------------------------------------+" << endl;
    cout << "|  PROGRAM TESTUJACY KLASE WIELOMIANOW  |" << endl;
    cout << "+----------------------------------------+" << endl;
    
    try {
        testKonstruktory();
        testDodawanie();
        testOdejmowanie();
        testMnozenie();
        testAlgorytmHornera();
        testPorownaniaRownosc();
        testMetodyPomocnicze();
        testZlozoneOperacje();
        testWielomianyCalkowite();
        
        cout << "\n+----------------------------------------+" << endl;
        cout << "|   WSZYSTKIE TESTY PRZESZLY POMYSLNIE!  |" << endl;
        cout << "+----------------------------------------+" << endl;
        
    } catch (const exception& e) {
        cout << "\n[BLAD] " << e.what() << endl;
        return 1;
        
    }
    
    return 0;
}