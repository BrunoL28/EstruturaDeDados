CC = g++
LDFLAGS =
CFLAGS = -Wall -Wextra -pedantic -std=c++11 -g
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
EXEC = $(BIN_DIR)/radix_sort

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

test: $(EXEC)
	@echo "Testando Radix Sort com 10k de elementos desordenados."
	@./$(EXEC) 10000 --desordenado
	@echo ""
	@echo "Testando Radix Sort com 10k de elementos ordenados."
	@./$(EXEC) 10000 --ordenado
	@echo ""
	@echo "Testando Radix Sort com 10k de elementos inversamente ordenados."
	@./$(EXEC) 10000 --inversamente-ordenado
	@echo ""
	@echo "Testando Radix Sort com 10k de elementos parcialmente ordenados."
	@./$(EXEC) 10000 --parcialmente-ordenado
	@echo ""
	@echo "Testando Radix Sort com 100k de elementos desordenados."
	@./$(EXEC) 100000 --desordenado
	@echo ""
	@echo "Testando Radix Sort com 100k de elementos ordenados."
	@./$(EXEC) 100000 --ordenado
	@echo ""
	@echo "Testando Radix Sort com 100k de elementos inversamente ordenados."
	@./$(EXEC) 100000 --inversamente-ordenado
	@echo ""
	@echo "Testando Radix Sort com 100k de elementos parcialmente ordenados."
	@./$(EXEC) 100000 --parcialmente-ordenado
	@echo ""
	@echo "Testando Radix Sort com 1.000.000 de elementos desordenados."
	@./$(EXEC) 1000000 --desordenado
	@echo ""
	@echo "Testando Radix Sort com 1.000.000 de elementos ordenados."
	@./$(EXEC) 1000000 --ordenado
	@echo ""
	@echo "Testando Radix Sort com 1.000.000 de elementos inversamente ordenados."
	@./$(EXEC) 1000000 --inversamente-ordenado
	@echo ""
	@echo "Testando Radix Sort com 1.000.000 de elementos parcialmente ordenados."
	@./$(EXEC) 1000000 --parcialmente-ordenado
	@echo ""
	@echo "Testando Radix Sort com 10k de elementos inversamente ordenados."
	@./$(EXEC) --verbose 10000 --inversamente-ordenado

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)