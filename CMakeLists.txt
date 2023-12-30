cmake_minimum_required(VERSION 3.10)

project(PasswordManager)

# Set compiler
set(CMAKE_CXX_COMPILER g++)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DNDEBUG -O2 -static")

# Directories
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(BLD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/cryptopp)
set(OBJ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/obj)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Executable
set(TARGET PasswordManager)

# Source files
set(SOURCE_FILES
    ${SRC_DIR}/PasswordManager.cpp
    ${SRC_DIR}/AVLTree.cpp
    ${SRC_DIR}/AES-CBC.cpp
    ${SRC_DIR}/KDF.cpp
)

# Include directories
include_directories(${INC_DIR} ${LIB_DIR})

# Custom target to build Crypto++
add_custom_target(cryptopp_build
    COMMAND ${CMAKE_MAKE_PROGRAM} -C ${LIB_DIR}
    COMMENT "Building Crypto++"
)

# Add the Crypto++ library
add_library(cryptopp STATIC IMPORTED)
set_target_properties(cryptopp PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/libcryptopp.a)

# Create target executable
add_executable(${TARGET} ${SOURCE_FILES})

# Link Crypto++ library
target_link_libraries(${TARGET} cryptopp)

# Set output directories
set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${BLD_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BLD_DIR}
)

# Add dependency to ensure Crypto++ is built before PasswordManager
add_dependencies(${TARGET} cryptopp_build)
