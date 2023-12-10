CXX = g++
CXXFLAGS = -Wall -DNDEBUG -O2
TARGET = PasswordManager
PREFIX = /usr/local

default: $(TARGET)

all: $(TARGET)

PasswordManager: PasswordManager.o AVLTree.o AES-CBC.o KDF.o
	$(CXX) $(CXXFLAGS) PasswordManager.o AVLTree.o AES-CBC.o KDF.o -l:libcryptopp.a -o $(TARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm *.o $(TARGET)

install:
	cp $(TARGET) $(PREFIX)/bin/$(TARGET)

uninstall:
	rm $(PREFIX)/bin/$(TARGET)
