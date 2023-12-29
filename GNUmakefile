CXX := g++
CXXFLAGS := -Wall -DNDEBUG -O2 -static
TARGET := PasswordManager
PREFIX := /usr/local/bin
BIN_DIR := ./bin
BLD_DIR := ./build
INC_DIR := ./lib
LIB_DIR := ./lib/cryptopp
OBJ_DIR := ./obj
SRC_DIR := ./src

.PHONY: cryptopp

default: $(TARGET)

all: $(TARGET)

$(TARGET): cryptopp $(OBJ_DIR)/PasswordManager.o $(OBJ_DIR)/AVLTree.o $(OBJ_DIR)/AES-CBC.o $(OBJ_DIR)/KDF.o
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_DIR)/PasswordManager.o $(OBJ_DIR)/AVLTree.o $(OBJ_DIR)/AES-CBC.o $(OBJ_DIR)/KDF.o -L$(LIB_DIR) -lcryptopp -o $(BIN_DIR)/$(TARGET)

cryptopp:
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(BIN_DIR) $(BLD_DIR) $(OBJ_DIR)

install:
	cp $(BIN_DIR)/$(TARGET) $(PREFIX)/$(TARGET)

uninstall:
	rm -f $(PREFIX)/$(TARGET)
