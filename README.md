*This project has been created as part of the 42 curriculum by tsaby.*

# C++ Module 09

> STL

## Description

Three small programs, each built around a different STL container.

Part of the C++ piscine of the 42 curriculum: every exercise is written in **C++98** and compiled with `-Wall -Wextra -Werror -std=c++98`.

## Exercises

| Exercise | Name | What it does |
|---|---|---|
| [`ex00`](ex00/) | Bitcoin Exchange | Reads a price database (`data.csv`) into a `std::map` and evaluates an input file of `date \| value` lines, using the closest earlier date and reporting invalid lines. |
| [`ex01`](ex01/) | Reverse Polish Notation | Evaluates an inverted Polish mathematical expression with a `std::stack`. |
| [`ex02`](ex02/) | PmergeMe | Sorts a sequence of positive integers with the Ford-Johnson merge-insertion algorithm (Jacobsthal insertion order), implemented on both `std::vector` and `std::deque`, and compares the time taken by each. |

## Instructions

Each exercise is an independent program with its own `Makefile`:

```bash
cd ex00
make
```

| Exercise | Binary | Usage |
|---|---|---|
| `ex00` | `btc` | `./btc input.txt` |
| `ex01` | `RPN` | `./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"` |
| `ex02` | `PmergeMe` | `./PmergeMe $(shuf -i 1-100000 -n 3000 \| tr "\n" " ")` |

`make clean` removes the object files, `make fclean` also removes the binary and `make re` rebuilds from scratch.

## Resources

- [cppreference.com](https://en.cppreference.com/w/cpp) — language and standard library reference
- [cplusplus.com](https://cplusplus.com/reference/) — C++98 standard library reference
