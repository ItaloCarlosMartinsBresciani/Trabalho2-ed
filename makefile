# Variáveis para compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = arvore.o lista.o main_funcoes.o main.o
TARGET = programa

# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    EXE_EXT = .exe
else
    RM = rm -f
    EXE_EXT =
endif

# Regra principal (compilar tudo)
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@$(EXE_EXT) $^

# Regra para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	$(RM) $(OBJ) $(TARGET)$(EXE_EXT)
