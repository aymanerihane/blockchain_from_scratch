Cellular Automaton (td2)
=========================

This small C++ project demonstrates a 1D elementary cellular automaton implementation.

Files

Build (PowerShell on Windows)

Open PowerShell in this directory (`c:\Users\ayman\OneDrive\Documents\IASD\blockchain\td2`) and run:

```powershell
# compile
g++ test1.cpp automate_cellulaire.cpp -o test1 -std=c++11 -Wall -Wextra
# run
.\test1
```

What to watch for

Cellular Automaton (td2)
=========================

This small C++ collection contains an elementary 1D cellular automaton, a small hashing utility built on top of it, and two demo/test programs.

Top-level files (in this folder)
- `automate_cellulaire.h` — Class declaration for `CellularAutomaton` (header).
- `automate_cellulaire.cpp` — Method definitions (implementation).
- `test1.cpp` — Simple demo runner that exercises `CellularAutomaton` directly.
- `hash.h` — Declaration of `ac_hash` (new: 256-bit hash via CA).
- `hash.cpp` — Implementation of the hashing functions that use `CellularAutomaton`.
- `test2.cpp` — Test suite for `ac_hash` (adds full `test_hash()` + `main()`).

Build & run (PowerShell on Windows)

Open PowerShell in this directory (`c:\Users\ayman\OneDrive\Documents\IASD\blockchain\td2`) and run one of the following commands depending on which demo you want to run:

```powershell
# Build and run the automaton demo (test1)
g++ test1.cpp automate_cellulaire.cpp -o test1 -std=c++11 -Wall -Wextra
.\test1

# Build and run the hash tests (test2)
g++ test2.cpp hash.cpp automate_cellulaire.cpp -o test2 -std=c++11 -Wall -Wextra
.\test2
```

Notes & troubleshooting
- Common build issues you may encounter:
	- "redefinition" errors: these occur if the full class body is duplicated across files (for example, copying the class implementation into the header and a .cpp). Keep only the class declaration in the header (`automate_cellulaire.h`) and the implementations in `automate_cellulaire.cpp`.
	- "undefined reference" (linker) errors: these happen when functions are declared but not defined in any linked translation unit. Make sure you compile & link the corresponding .cpp (e.g., include `automate_cellulaire.cpp` and `hash.cpp` when building `test2`).

- Terminal encoding: the tests print French accented text. If accents look garbled, set PowerShell to UTF-8 before running:

```powershell
chcp 65001
# then run the compiled executable
.\test2
```

- The `ac_hash` implementation is a pedagogical hashing mechanism built from a cellular automaton. It is suitable for experiments and teaching, not for production cryptographic hashing.

What the tests cover
- `test1.cpp` demonstrates CA evolution for rules such as 30, 90 and 110.
- `test2.cpp` (hash tests) checks basic collision-sensitivity between different inputs, rule/step sensitivity, avalanche effect, and behavior for empty input.

Suggested next steps (optional)
- Add a short `build.ps1` or `Makefile` that builds `test1` and `test2` with one command.
- Move demos into an `examples/` folder and leave `automate_cellulaire.*` + `hash.*` as a small library.
- Add unit tests (Catch2 or Google Test) to automate verification.

If you'd like, I can add a `build.ps1` now — tell me whether you want the script to build both demos or just the hash test.


