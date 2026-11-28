*This project has been created as part of the 42 curriculum by ymoubtas, mamehri.*

# push_swap

## Description

**push_swap** sorts a stack of integers using two stacks (`a` and `b`) and a limited set of operations, while trying to use as few operations as possible.

The program reads a list of integers (the first argument is the top of stack `a`), computes a sequence of Push_swap operations that sorts `a` in ascending order (smallest number on top, `b` empty), and prints that sequence on `stdout`, one operation per line.

Allowed operations: `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`.

The binary embeds four strategies:

| Strategy   | Flag         | Algorithm                  | Complexity (in operations) |
|------------|--------------|----------------------------|----------------------------|
| Simple     | `--simple`   | Selection sort adaptation  | O(n²)                      |
| Medium     | `--medium`   | Chunk-based sort           | O(n√n)                     |
| Complex    | `--complex`  | LSD radix sort adaptation  | O(n log n)                 |
| Adaptive   | `--adaptive` | Picks one of the above from the measured disorder (default) | O(n²) / O(n√n) / O(n log n) per regime |

A `--bench` flag prints statistics on `stderr` after sorting. A bonus `checker` program verifies that a sequence of operations sorts a given stack.

### Contributions

Both learners contributed meaningfully to the project and can explain every part of the code.

- **ymoubtas**: contributions to the sorting strategies, the operations, the argument parsing, and the checker (bonus).
- **mamehri**: contributions to the sorting strategies, the operations, the flag handling / benchmark mode, and the checker (bonus).

## Instructions

### Compilation

The project is written in C and compiled with `cc -Wall -Wextra -Werror`.

```bash
make          # builds ./push_swap
make bonus    # builds ./checker
make clean    # removes object files
make fclean   # removes object files and binaries
make re       # full rebuild
```

The Makefile does not relink when nothing changed.

### Execution

```bash
./push_swap [strategy] [--bench] <list of integers>
```

- `strategy` is one of `--simple`, `--medium`, `--complex`, `--adaptive`. If none is given, `--adaptive` is used.
- `--bench` can be combined with a strategy flag.
- Integers can be given as separate arguments or as a single quoted string (`"4 67 3 87 23"`).
- With no arguments, nothing is displayed.
- On error (non-integer argument, value outside the `int` range, duplicate, invalid flag), `Error\n` is written on `stderr`.

```bash
$> ./push_swap 2 1 3 6 5 8
$> ./push_swap --simple 5 4 3 2 1
$> ./push_swap --complex 4 67 3 87 23 | wc -l
$> ./push_swap --adaptive --bench 4 67 3 87 23 >/dev/null
$> ./push_swap 0 one 2 3
Error
```

### Benchmark mode

With `--bench`, the following is printed on `stderr` (the operations stay on `stdout`):

- the computed disorder (percentage with two decimals),
- the strategy used and its theoretical complexity class,
- the total number of operations,
- the count of each operation type.

### Checker (bonus)

```bash
$> ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker $ARG
OK
```

`checker` reads operations from `stdin` (one per line), applies them to stack `a`, and prints `OK` if `a` is sorted and `b` is empty, `KO` otherwise. Invalid arguments or unknown/badly formatted instructions print `Error` on `stderr`.

### Testing

```bash
ARG=$(shuf -i 0-9999 -n 500 | tr '\n' ' ')
./push_swap $ARG | wc -l
./push_swap $ARG | ./checker $ARG
```

Performance targets from the subject:

| Input size | Pass    | Good    | Excellent |
|------------|---------|---------|-----------|
| 100        | < 2000  | < 1500  | < 700     |
| 500        | < 12000 | < 8000  | < 5500    |

## Algorithms

### Disorder metric

Before any move, the disorder of stack `a` is computed as:

```
disorder = mistakes / total_pairs
```

where `total_pairs` is the number of pairs `(i, j)` with `i < j` and `mistakes` is the number of those pairs with `a[i] > a[j]` (inversions). The value is `0` for a sorted stack and `1` for a reversed one. The computation costs O(n²) comparisons but generates **no** Push_swap operation, so it does not count in the operation model.

### Preprocessing: index normalization

Each number receives an `index` equal to its rank among all values (0 for the smallest, n − 1 for the largest). Radix and chunk sorts work on these ranks, so negative numbers and large values need no special handling. This costs O(n²) CPU time and O(n) memory, and generates no operations.

### Simple: selection sort adaptation, O(n²)

1. While `a` has more than one element: find the smallest element, bring it to the top of `a` using `ra` or `rra` (whichever direction is shorter), then `pb`.
2. Push everything back with `pa`. Since the smallest values were pushed first, they end up on top of `a` in ascending order.

**Justification:** each of the n extractions needs at most n/2 rotations plus one push, so the total is at most about n²/2 + 2n operations: O(n²). Auxiliary space is O(1) (a few integers); the two stacks always hold exactly n nodes in total. If the stack is already sorted, nothing is printed.

### Medium: chunk-based sort, O(n√n)

1. **Phase 1 (a → b):** the window size is `offset ≈ √n`. Every element whose index is within `pushed + offset` is pushed to `b`; if it is among the smallest already-covered values (index < `pushed`), `rb` sends it to the bottom of `b`. If the top of `a` is outside the window, `a` is rotated (shortest direction) until an element inside the window is on top.
2. **Phase 2 (b → a):** repeatedly find the maximum of `b`, bring it to the top (shortest direction), and `pa`.

**Justification:** the sliding window of about √n values means that, at any time, an element inside the window is within about √n positions of the top of `a`, so each push costs O(√n) operations, for a total of O(n√n) in phase 1. After phase 1, `b` is roughly ordered by block, so the next maximum is always within about √n positions of one end of `b`, and phase 2 also costs O(√n) per element: O(n√n) in total. Auxiliary space is O(1) beyond the stacks and the O(n) indexes.

### Complex: LSD radix sort adaptation, O(n log n)

Radix sort is applied to the normalized indexes, one bit at a time, from the least significant bit:

1. For each element of `a`: if the current bit is `1`, `ra`; otherwise `pb`.
2. Push everything from `b` back to `a` with `pa`.
3. Repeat for the next bit.

**Justification:** the number of passes is ⌈log₂ n⌉ (the number of bits of the largest index). Each pass performs at most n `ra`/`pb` operations and at most n `pa` operations, i.e. at most 2n per pass, so the total is at most 2n⌈log₂ n⌉ = O(n log n). Auxiliary space is O(1) beyond the stacks and the O(n) indexes. The sort is stable per pass, which makes it correct.

### Adaptive: custom strategy based on disorder

| Disorder (d)       | Strategy         | Complexity (operations) |
|--------------------|------------------|-------------------------|
| d < 0.2            | Selection sort   | O(n²)                   |
| 0.2 ≤ d < 0.5      | Chunk sort       | O(n√n)                  |
| d ≥ 0.5            | Radix sort       | O(n log n)              |

**Rationale for the thresholds:**

- The thresholds `0.2` and `0.5` are the regime boundaries required by the subject.
- A random permutation has an expected disorder of about `0.5`, so inputs at or above this value are treated as "random-like" and sent to the algorithm with the best worst-case guarantee, radix sort, whose cost does not depend on the initial order.
- Between `0.2` and `0.5`, the input still has some structure. The chunk sort works with a window of about √n values, which keeps rotations short, and gives a good balance between operation count and simplicity.
- Below `0.2`, the stack is close to sorted. Selection sort stops immediately if the stack is already sorted and always uses the shortest rotation direction, which keeps the O(n²) bound with a small constant.

**Complexity of the adaptive strategy:** its cost is the cost of the selected method, so it is bounded by O(n²), O(n√n) or O(n log n) in the respective regime, plus zero operations for the disorder measurement. Space is O(1) auxiliary beyond the stacks and indexes (O(n) in total).

## Resources

### References

- Donald E. Knuth, *The Art of Computer Programming, Vol. 3: Sorting and Searching*.
- Cormen, Leiserson, Rivest, Stein, *Introduction to Algorithms* (sorting chapters: selection sort, radix sort, complexity analysis).
- Wikipedia: [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation), [Radix sort](https://en.wikipedia.org/wiki/Radix_sort), [Selection sort](https://en.wikipedia.org/wiki/Selection_sort), [Inversion (discrete mathematics)](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)).
- The 42 Norm (version 4.1) and the push_swap subject (version 1.2).

### Use of AI

AI tools were used as an assistant, not as a replacement for understanding:

- **Documentation:** to help draft and structure this README from the subject requirements and the source code.
- **Testing and review:** to brainstorm test cases (edge cases for parsing, duplicates, integer limits) and to review the code for norm and robustness issues.

All AI-generated content was reviewed, tested, and discussed between both learners, and both can explain every part of the code.
