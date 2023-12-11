CXX = g++
CXXFLAGS = -Wall -DNDEBUG -O2
TARGET = PasswordManager
PREFIX = /usr/local
LIBDIR = ./cryptopp

.PHONY: cryptopp

default: $(TARGET)

all: $(TARGET)

PasswordManager: cryptopp PasswordManager.o AVLTree.o AES-CBC.o KDF.o
	$(CXX) $(CXXFLAGS) PasswordManager.o AVLTree.o AES-CBC.o KDF.o -L$(LIBDIR) -lcryptopp -o $(TARGET)

cryptopp:
	$(MAKE) -C $(LIBDIR)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm *.o $(TARGET)

install:
	cp $(TARGET) $(PREFIX)/bin/$(TARGET)

uninstall:
	rm $(PREFIX)/bin/$(TARGET)
