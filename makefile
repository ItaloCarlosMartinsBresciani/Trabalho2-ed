# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -g

# Arquivos do projeto
SRC = arvore.c lista.c main_funcoes.c main.c
HEADERS = arvore.h erro.h lista.h main_funcoes.h
OBJ = $(SRC:.c=.o)

# Nome do executável
TARGET = programa

# Regra padrão: compila tudo
all: $(TARGET)

# Regra para compilar o programa principal
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os arquivos objeto
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos temporários
clean:
	rm -f $(OBJ) $(TARGET)

# Regra para recompilar do zero
rebuild: clean all
