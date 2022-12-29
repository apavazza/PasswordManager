# Password Manager

A command line password manager

## Download
Here you can download binaries

**[DOWNLOAD](https://github.com/apavazza/PasswordManager/releases)**

## Compiling

1. clone the repository using `git clone --recurse-submodules`
2. open `cryptlib.vcxproj` inside the `cryptopp` folder
3. select the `cryptlib` project
4. go to `Build->Batch Build...`
5. select the `Release` configuration for the platform that you require, optionally you can also select the `Debug` configuration
6. click on build
7. now open `PasswordManager.sln`
8. select the `Release` configuration and compile it
9. You are done. If you installed the `cryptlib` library in a different location or got any linker errors continue with these steps:
10. go to `Project->Properties->Configuration Properties->C/C++->General`, in the field `Additional Include Directories` add `$(ProjectDir)\cryptopp\`
11. go to `Project->Properties->Configuration Properties->C/C++->Code Generation`, set the field `Runtime Library` to `Multi-threaded (/MT)` for the `Release` configuration and `Multi-threaded Debug (/MTd)` for the `Debug` configuration
12. go to `Project->Properties->Configuration Properties->Linker->General`, in the field `Additional Library Directories` add  `$(ProjectDir)\cryptopp\x64\Output\Debug\`
13. go to `Project->Properties->Configuration Properties->Linker->Input`, in the field `Additional Dependencies` add `$(ProjectDir)\cryptopp\x64\Output\Debug\cryptlib.lib`

If you are having trouble compiling you can watch this helpful [video](https://www.youtube.com/watch?v=glFHKB8Y10Y) I found online.

Alternatively, you can build the project using CMake.

## Encryption
Password databases are encrypted with AES-256-CBC.  
Key derivation algorithm is PKCS5 PBKDF2 HMAC with SHA3-256 hashing.

## License
This software is provided under the terms of the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.txt).
