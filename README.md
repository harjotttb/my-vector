# My Vector

Built my own version of `std::vector` from scratch in C++. Wanted to actually understand what's happening under the hood instead of just using the built-in one — memory management, resizing, all of it.

## What it does

- Grows on its own as you add elements (dynamic resizing)
- Works with any data type (templates)
- Has the core stuff you'd expect:
  - `push_back`, `pop_back`
  - `size()`, `capacity()`
  - `operator[]` for indexing
  - Copy constructor / assignment operator that actually deep-copy correctly
  - Destructor that cleans up memory properly

## What I got out of it

- How `std::vector` actually manages memory (allocation, reallocation, growth strategy)
- Rule of Three/Five in C++
- Manual memory management with `new`/`delete`, pointer arithmetic
- Writing generic code with templates

## Run it

```bash
g++ -std=c++17 -o my_vector main.cpp
./my_vector
```

## Notes

Built this for CPSC 131 (Data Structures) at CSUF.
