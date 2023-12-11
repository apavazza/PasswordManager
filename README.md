# Password Manager

A command line password manager

## Download
Here you can download Linux and Windows x64 binaries

**[DOWNLOAD](https://github.com/apavazza/PasswordManager/releases)**

## Command line arguments

There are two optional command line arguments that you can use.  
Use of these arguments skips the start menu.  
`-n <filename>` creates a new password database  
`-o <filename>` opens an existing password database

## Compiling

### Linux

1. clone the repository using `$ git clone --recurse-submodules`
1. run `$ make`
1. run `# make install`
1. now you can run the program using `$ PasswordManager`

### Windows

1. clone the repository using `git clone --recurse-submodules`
1. open `cryptlib.vcxproj` located inside the `cryptopp` directory
1. go to `Build->Batch Build...`
1. for the project `cryptlib` select the `Release` configuration for the platform that you require, optionally you can also select the `Debug` configuration
1. click on build
1. now open `PasswordManager.sln` located in the main directory
1. select the `Release` configuration and compile it
1. You are done. If you installed the `cryptlib` library in a different location or got any linker errors continue with these steps:
1. go to `Project->Properties->Configuration Properties->C/C++->Code Generation`, set the field `Runtime Library` to `Multi-threaded (/MT)` for the `Release` configuration and `Multi-threaded Debug (/MTd)` for the `Debug` configuration
1. go to `Project->Properties->Configuration Properties->Linker->General`, in the field `Additional Library Directories` add  `$(ProjectDir)\cryptopp\x64\Output\Release\`
1. go to `Project->Properties->Configuration Properties->Linker->Input`, in the field `Additional Dependencies` add `$(ProjectDir)\cryptopp\x64\Output\Release\cryptlib.lib`

## Encryption
Password databases are encrypted with AES-256-CBC.  
Key derivation function is PKCS5 PBKDF2 HMAC with SHA3-256 hashing.

## License
This software is provided under the terms of the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.txt).
