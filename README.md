# GarbageCollector

A minimal mark-and-sweep garbage collector in C (demo project).

## Files
- `main.c` – full GC implementation + demo tests.
- `Makefile` – build & run helper.
- `.vscode/` – VS Code task & debug configs.

## Build & Run (terminal)
```bash
# build
gcc main.c -o gc

# or using make
make

# run
./gc
