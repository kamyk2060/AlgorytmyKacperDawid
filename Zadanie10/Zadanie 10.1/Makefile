# Kompilator g++.
CXX = g++
# Mozliwe dodatkowe zmienne.
# LIBS = -ll -lm
LIBS =
# Flagi dla kompilatora C++.
# Standardy: -std=c++11 -std=c++14 -std=c++17 -std=c++20 -std=c++23 -std=c++26
CXXFLAGS = -Wall -Wextra -std=c++11 -g
# Pliki obiektowe - powstaja z plikow *.cpp.
OBJECTS = main.o
# Pliki naglowkowe - sa wlaczane do plikow *.cpp.
HFILES = 
# Koncowy plik wykonywalny.
TARGET = main.out

# Definicja domyslnej reguly wzorcowej.
# $< oznacza nazwe pliku pierwszej zaleznosci reguly.
# $@ oznacza nazwe pliku celu w regule.
# Wszystkie pliki obiektowe zaleza od wszystkich plikow naglowkowych.
# WCIĘCIA MUSZĄ BYĆ TABULATORAMI!
%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBS) -o $(TARGET)

# Okreslenie celow sztucznych.
.PHONY : clean run all

# Cel domyslny
all: $(TARGET)

# Uruchom program
run: $(TARGET)
	./$(TARGET)

clean :
	$(RM) $(TARGET) *.o core

# Cel do debugowania (pokazuje zmienne)
debug:
	@echo "CXX: $(CXX)"
	@echo "CXXFLAGS: $(CXXFLAGS)"
	@echo "OBJECTS: $(OBJECTS)"
	@echo "HFILES: $(HFILES)"
	@echo "TARGET: $(TARGET)"