# Robot Factory - Corewar Assembler in C

`robot-factory` converts a Corewar source file (`.s`) into a valid Corewar bytecode file (`.cor`).

This project focuses on correctness, deterministic output, and clear internal architecture:
- strict header parsing (`.name`, `.comment`)
- instruction and parameter decoding
- label storage and relative resolution
- big-endian binary encoding (`header_t` + instruction stream)

## Why this project is useful

- It provides a complete assembler workflow from raw text to binary output.
- It is testable with both unit tests and functional binary comparisons.
- It includes tooling to debug memory safety (`valgrind`) and quality (`coverage`).

## Quick start

```sh
make
./robot-factory Utilities/G-CPE-200_champions/abel.s
```

Generated output:
- input: `abel.s`
- output: `abel.cor`

## Features

- Parse full source content via `openator` and tokenization helpers.
- Validate required header fields and length constraints.
- Build internal representation using:
  - `robotfactory_t` as root context
  - `instr_t` linked list for ordered instructions
  - `node_t` list of `label_t` for label positions
- Encode instructions with proper coding byte rules.
- Write Corewar header and instruction payload in big-endian format.

## Project structure

```text
Robot_Factory/
├── Makefile
├── Src/
│   ├── main.c
│   ├── op.c
│   ├── Headers/
│   │   ├── op.h
│   │   └── robotfactory.h
│   ├── Parser/
│   │   ├── parser.c
│   │   ├── parser_body.c
│   │   ├── is_header_line.c
│   │   ├── get_opcode.c
│   │   ├── get_instr_size.c
│   │   └── free_robotfactory.c
│   ├── Encoder/
│   │   └── encoder.c
│   └── Tools/
│       └── shifter.c
├── lib/my/
├── tests/
│   ├── Makefile
│   ├── unit_tests_lib.c
│   ├── unit_tests_robotfactory.c
│   └── run_tests.sh
└── Doc/
    ├── README.md
    ├── schem.mmd
    └── POLICY/
```

## Build and utility commands

Use:

```sh
make help
```

Main targets:
- `make` / `make all`: build `robot-factory`
- `make run`: run with default `ARGUMENTS`
- `make run ARGUMENTS="path/to/file.s"`: run custom source
- `make debug`: debug build + valgrind
- `make valgrind`: memory analysis on current `ARGUMENTS`
- `make unit_tests`: build Criterion unit tests
- `make tests_run`: run unit tests
- `make functional_tests`: run functional shell tests
- `make coverage`: coverage report
- `make clean`, `make fclean`, `make re`

## Internal flow summary

1. `main` validates CLI and calls `parse`.
2. `parse` reads file, tokenizes lines, fills header, then parses body.
3. `get_body` stores labels and instructions in `robotfactory_t`.
4. `write_cor` serializes header + instructions to `.cor`.
5. `free_robotfactory` releases all dynamic parser structures.

Detailed architecture graph is in `Doc/schem.mmd`.

## Quality checks

- Unit tests: `make tests_run`
- Functional tests: `make functional_tests`
- Valgrind: `make valgrind`

## Policies

- `Doc/POLICY/COMMIT_POLICY.md`
- `Doc/POLICY/STRUCTURE_POLICY.md`
