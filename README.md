# Mini File Search Engine (C)

A small command-line utility that searches a text file for a keyword and prints matching lines with line numbers. Built to practice C strings, pointers, file handling, loops, and basic testing.

## Features

- Search a text file for an exact keyword
- Print line numbers and the number of matches per line
- Report total matching lines and total occurrences
- Handle missing files and empty keywords with helpful error messages
- Support long lines using POSIX `getline()`

## Technologies and design

- **C11** and POSIX `getline()` — tested on macOS/Linux style environments
- Standard C `fopen()`, `fclose()`, `strstr()`, `strlen()`, and pointer arithmetic
- Shell-based smoke tests, no external dependencies

The code processes one line at a time rather than loading the entire file into memory. `count_matches()` uses `strstr()` to locate each occurrence. Matching is **case-sensitive** and counts **non-overlapping** occurrences.

## Run in VS Code (Mac)

1. Install Apple's command-line tools if needed: `xcode-select --install`.
2. Open the `c-mini-file-search` folder in VS Code.
3. Open **Terminal → New Terminal** and compile:

   ```bash
   cc -std=c11 -Wall -Wextra main.c -o mini-search
   ```

4. Search the included example file:

   ```bash
   ./mini-search sample.txt Python
   ```

Expected output:

```text
Searching for "Python" in sample.txt
Line 1 (1 match): Python is fun.
Line 3 (2 matches): Python can process text. Python is powerful.
Matching lines: 2 | Total matches: 3
```

Search for two-word phrases by using quotes: `./mini-search sample.txt "is fun"`.

## Run tests

```bash
sh tests/test_search.sh
```

The script compiles the application, verifies the matching counts, and checks two invalid-input cases.

## Project structure

```text
c-mini-file-search/
├── main.c                 # Search logic and command-line interface
├── sample.txt             # Public demonstration text
├── tests/test_search.sh   # Basic automated smoke tests
├── README.md              # Setup, design and limitations
└── .gitignore             # Ignore compiled binaries
```

## Limitations and next steps

- Case-sensitive matching only; add a case-insensitive option later.
- Searches **one text file at a time**, not entire directories.
- Non-overlapping occurrences only; binary files aren't a supported input format.
- `getline()` requires a POSIX environment; the program is not portable to all Windows C compilers without changes.

## What I learned / interview discussion

- Why do we use `FILE *` and close files when done?
- How does `strstr()` find a keyword?
- Why do we call `free(line)` after `getline()`?
- What happens if the requested file doesn't exist?

> If you used AI or tutorials, study the implementation, verify the output, and implement a small original improvement before describing your own contribution.
