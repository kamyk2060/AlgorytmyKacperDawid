# Kompilator g++.
CXX = g++
# Mozliwe dodatkowe zmienne.
# LIBS = -ll -lm
LIBS =
# Flagi dla kompilatora C++.
# Standardy: -std=c++11 -std=c++14 -std=c++17 -std=c++20 -std=c++23 -std=c++26
CXXFLAGS = -Wall -std=c++11
# Pliki obiektowe - powstaja z plikow *.cpp.
OBJECTS = bubblesort.o 
# Pliki naglowkowe - sa wlaczane do plikow *.cpp.
HFILES = atrapa.h
# Koncowy plik wykonywalny.
TARGET = main.out

# Definicja domyslnej reguly wzorcowej.
# $< oznacza nazwe pliku pierwszej zaleznosci reguly.
# $@ oznacza nazwe pliku celu w regule.
# Wszystkie pliki obiektowe zaleza od wszystkich plikow naglowkowych.
# WCIÊCIA MUSZ¥ BYÆ TABULATORAMI!
%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

# Okreslenie celow sztucznych.
.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core