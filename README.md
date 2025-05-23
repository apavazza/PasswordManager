# Password Manager

[![Build](https://github.com/apavazza/PasswordManager/actions/workflows/build-and-release.yml/badge.svg)](https://github.com/apavazza/PasswordManager/actions/workflows/build-and-release.yml)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](LICENSE)

A command line password manager

## Download

Here you can download x86_64 binaries

**[DOWNLOAD](https://github.com/apavazza/PasswordManager/releases)**

## Command line arguments

There are two optional command line arguments that you can use.  
Use of these arguments skips the start menu.  
`-n <filename>` creates a new password database  
`-o <filename>` opens an existing password database

## Compiling

Clone the repository using `git clone --recurse-submodules`

### Using Make (Linux, Windows w/ MSYS2, macOS)

1. To compile, run `$ make`
1. On Linux, to install, run `# make install`
1. On Linux, to launch the installed program, run `$ PasswordManager`

**Requirements**

- `g++`
- `glibc-devel-static`

### Using CMake (Linux, Windows w/ MSYS2, macOS)

```shell
mkdir build
cd build
cmake ..
make
```

**Requirements**

- `glibc-devel-static`

### Using Visual Studio (Windows)

1. Launch Visual Studio and open the `cryptlib.vcxproj` project located inside the `lib\cryptopp` directory
1. Go to `Build->Batch Build...`
1. For the project `cryptlib` select the `Release` configuration and build it
1. Launch Visual Studio and open the `PasswordManager.sln` solution located in the main directory
1. Select the `Release` configuration and build it

## Encryption

Password databases are encrypted with AES-256-CBC.  
Key derivation function is PKCS5 PBKDF2 HMAC with SHA3-256 hashing.

## License

This software is provided under the terms of the [GNU General Public License v3.0](LICENSE).
