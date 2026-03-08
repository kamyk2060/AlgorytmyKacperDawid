#include <cassert>
#include <algorithm>
#include <vector>
#include "myset.h"

int main() {
    MySet<int> s(7);

    // --- empty / insert ---
    assert(s.empty());
    assert(s.size() == 0);

    s.insert(5); s.insert(12); s.insert(3);
    s.insert(8); s.insert(21); s.insert(14);

    assert(!s.empty());
    assert(s.size() == 6);
    s.display();

    // brak duplikatów
    s.insert(5);
    s.insert(12);
    assert(s.size() == 6);
    s.display();

    // --- contains / find ---
    assert(s.contains(5));
    assert(s.contains(21));
    assert(!s.contains(99));

    assert(s.find(8)  != nullptr);
    assert(*s.find(8) == 8);
    assert(s.find(99) == nullptr);

    // --- remove ---
    s.remove(12);
    assert(!s.contains(12));
    assert(s.size() == 5);
    s.display();

    s.remove(99); // usunięcie nieistniejącego – brak błędu
    assert(s.size() == 5);

    // --- iterator: zbieramy elementy i sprawdzamy zawartość ---
    std::vector<int> elems;
    for (const int& v : s)
        elems.push_back(v);

    assert((int)elems.size() == s.size());
    for (int v : {5, 3, 8, 21, 14})
        assert(std::find(elems.begin(), elems.end(), v) != elems.end());

    // --- clear ---
    s.clear();
    assert(s.empty());
    assert(s.size() == 0);

    // iterator na pustym zbiorze
    int cnt = 0;
    for (const int& v : s) { (void)v; ++cnt; }
    assert(cnt == 0);


    std::cout << "Wszystkie testy zaliczone.\n";
    return 0;
}