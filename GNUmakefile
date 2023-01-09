PasswordManager: PasswordManager.o AVLTree.o AES-CBC.o KDF.o
	g++ PasswordManager.o AVLTree.o AES-CBC.o KDF.o -l:libcryptopp.a -o PasswordManager

PasswordManager.o: PasswordManager.cpp PasswordManager.h
	g++ -DNDEBUG -O2 -c PasswordManager.cpp

AVLTree.o: AVLTree.cpp AVLTree.h
	g++ -DNDEBUG -O2 -c AVLTree.cpp

AES-CBC.o: AES-CBC.cpp AES-CBC.h
	g++ -DNDEBUG -O2 -c AES-CBC.cpp

KDF.o: KDF.cpp KDF.h
	g++ -DNDEBUG -O2 -c KDF.cpp

clean:
	rm PasswordManager.o AVLTree.o AES-CBC.o KDF.o

install:
	cp PasswordManager /usr/bin/PasswordManager

uninstall:
	rm /usr/bin/PasswordManager
