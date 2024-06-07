# Nome do executável
TARGET = manga_manager

# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra -Werror -std=c11

# Arquivos de origem
SRC = main.c manga.c

# Arquivos de cabeçalho
HEADERS = manga.h

# Regra principal
$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Limpeza dos arquivos compilados
clean:
	rm -f $(TARGET) *.o

# Regra para recompilar tudo do zero
rebuild: clean $(TARGET)
