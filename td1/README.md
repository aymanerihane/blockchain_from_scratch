# Blockchain Concepts in C++

This directory contains C++ implementations of fundamental blockchain concepts as part of a series of exercises.

## Exercises

### Exercise 1: Merkle Tree (`ex1_merkle_tree.cpp`)

Implements a basic Merkle Tree from scratch. It takes a list of transactions (as strings), hashes them, and constructs the tree to find the Merkle root.

### Exercise 2: Proof of Work (`ex2_proof_of_work.cpp`)

Demonstrates a simple Proof of Work (PoW) algorithm. It includes a `Block` class and a `mineBlock` function that finds a hash satisfying a given difficulty (i.e., starting with a certain number of zeros). The time taken to mine the block is measured.

### Exercise 3: Proof of Stake (`ex3_proof_of_stake.cpp`)

Implements a basic Proof of Stake (PoS) consensus mechanism. It simulates selecting a validator from a pool based on their stake. The time taken for selection is measured to contrast with PoW's mining time.

### Exercise 4: Mini Blockchain (`ex4_mini_blockchain.cpp`)

Integrates the concepts from the previous exercises into a simple, functional blockchain. It includes `Transaction`, `Block`, and `Blockchain` classes. It demonstrates adding blocks using both PoW and PoS and compares their performance.

## Prerequisites

- A C++ compiler (like g++)
- OpenSSL library for SHA-256 hashing.

### Installing OpenSSL

**On Debian/Ubuntu:**
```bash
sudo apt-get update
sudo apt-get install libssl-dev
```

**On macOS (using Homebrew):**
```bash
brew install openssl
```

**On Windows:**
You can use a package manager like Chocolatey:
```powershell
choco install openssl
```
Or download pre-compiled binaries from a source like [Shining Light Productions](https://slproweb.com/products/Win32OpenSSL.html). Make sure to add the OpenSSL `bin` directory to your system's PATH and configure your compiler to find the `include` and `lib` directories.

## How to Compile and Run

Open a terminal in this directory.

### Compiling
You need to link against the OpenSSL libraries (`-lssl -lcrypto`).

```bash
# Exercise 1
g++ -o ex1_merkle_tree ex1_merkle_tree.cpp -lssl -lcrypto

# Exercise 2
g++ -o ex2_proof_of_work ex2_proof_of_work.cpp -lssl -lcrypto

# Exercise 3
g++ -o ex3_proof_of_stake ex3_proof_of_stake.cpp

# Exercise 4
g++ -o ex4_mini_blockchain ex4_mini_blockchain.cpp -lssl -lcrypto
```
*Note: On Windows, the output files will have a `.exe` extension (e.g., `ex1_merkle_tree.exe`).*

### Running
```bash
# Exercise 1
./ex1_merkle_tree

# Exercise 2
./ex2_proof_of_work

# Exercise 3
./ex3_proof_of_stake

# Exercise 4
./ex4_mini_blockchain
```
