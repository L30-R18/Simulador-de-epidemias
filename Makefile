# Compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -Wextra -std=c99

# Nome do executável
TARGET = epidemia

# Lista de arquivos fonte
SRCS = main.c epidemia.c

# Lista de arquivos de cabeçalho
HEADERS = epidemia.h

# Comando para compilar o programa
$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) -lm

# Comando para limpar os arquivos gerados durante a compilação
clean:
	rm -f $(TARGET)

# Comando para executar o programa
run: $(TARGET)
	./$(TARGET)
