# Nome do executável
TARGET = manga_manager

# Compilador
CXX = g++

# Flags do compilador
CXXFLAGS = -Wall -Wextra -std=c++11

# Arquivos de origem
SRC = main.cpp manga.cpp

# Arquivos de cabeçalho
HEADERS = manga.h

# Regra principal
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Limpeza dos arquivos compilados
clean:
	rm -f $(TARGET) *.o
	