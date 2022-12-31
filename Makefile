PasswordManager: PasswordManager.o AVLTree.o AES-CBC.o KDF.o
	g++ PasswordManager.o AVLTree.o AES-CBC.o KDF.o -l:libcryptopp.a -o PasswordManager

PasswordManager.o: PasswordManager.cpp PasswordManager.h
	g++ -DNDEBUG -c PasswordManager.cpp

AVLTree.o: AVLTree.cpp AVLTree.h
	g++ -DNDEBUG -c AVLTree.cpp

AES-CBC.o: AES-CBC.cpp AES-CBC.h
	g++ -DNDEBUG -c AES-CBC.cpp

KDF.o: KDF.cpp KDF.h
	g++ -DNDEBUG -c KDF.cpp

clean:
	rm PasswordManager.o AVLTree.o AES-CBC.o KDF.o

install:
	cp PasswordManager /usr/bin/PasswordManager
