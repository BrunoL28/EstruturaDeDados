CC = g++
LDFLAGS =
CFLAGS = -Wall -Wextra -pedantic -std=c++11 -g
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
EXEC = $(BIN_DIR)/bucket_sort

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

test: $(EXEC)
	@echo "Testando Bucket Sort com 10k de elementos desordenados."
	@./$(EXEC) 10000 3 --desordenado
	@echo ""
	@echo "Testando Bucket Sort com 10k de elementos ordenados."
	@./$(EXEC) 10000 3 --ordenado
	@echo ""
	@echo "Testando Bucket Sort com 10k de elementos inversamente ordenados."
	@./$(EXEC) 10000 3 --inversamente-ordenado
	@echo ""
	@echo "Testando Bucket Sort com 10k de elementos parcialmente ordenados."
	@./$(EXEC) 10000 3 --parcialmente-ordenado
	@echo ""
	@echo "Testando Bucket Sort com 100k de elementos desordenados."
	@./$(EXEC) 100000 5 --desordenado
	@echo ""
	@echo "Testando Bucket Sort com 100k de elementos ordenados."
	@./$(EXEC) 100000 5 --ordenado
	@echo ""
	@echo "Testando Bucket Sort com 100k de elementos inversamente ordenados."
	@./$(EXEC) 100000 5 --inversamente-ordenado
	@echo ""
	@echo "Testando Bucket Sort com 100k de elementos parcialmente ordenados."
	@./$(EXEC) 100000 5 --parcialmente-ordenado
	@echo ""
	@echo "Testando Bucket Sort com 1.000.000 de elementos desordenados."
	@./$(EXEC) 1000000 8 --desordenado
	@echo ""
	@echo "Testando Bucket Sort com 1.000.000 de elementos ordenados."
	@./$(EXEC) 1000000 8 --ordenado
	@echo ""
	@echo "Testando Bucket Sort com 1.000.000 de elementos inversamente ordenados."
	@./$(EXEC) 1000000 8 --inversamente-ordenado
	@echo ""
	@echo "Testando Bucket Sort com 1.000.000 de elementos parcialmente ordenados."
	@./$(EXEC) 1000000 8 --parcialmente-ordenado
	@echo ""
	@echo "Testando Bucket Sort com 10k de elementos inversamente ordenados."
	@./$(EXEC) 10000 3 --inversamente-ordenado

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)