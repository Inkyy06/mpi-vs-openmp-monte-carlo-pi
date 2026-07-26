# MPI vs OpenMP Monte Carlo Pi Estimation

Estimates Pi using the Monte Carlo method, implemented in both MPI and OpenMP
to compare their performance.

## How It Works

Random points are generated inside a 2x2 square; the ratio of points falling
inside the inscribed unit circle approximates Pi/4.

## Implementation Details

**MPI version** (`MPI_MonteCarloPi.cpp`):
- Rank 0 reads the number of points and broadcasts it via `MPI_Bcast`.
- Each rank generates its own share of points (`Total_Points / size`) with a
  rank-specific random seed; any remainder is added to the last rank so the
  total matches exactly.
- Local hit counts are summed across all ranks using `MPI_Reduce` (`MPI_SUM`).
- Rank 0 computes and prints the final estimate and elapsed time.

**OpenMP version** (`OMP_MonteCarloPi.cpp`):
- The main thread reads the number of points.
- `#pragma omp parallel` spawns threads, each with its own thread-specific
  random seed.
- `#pragma omp for reduction(+:...)` splits the loop across threads and safely
  combines hit counts.
  
### Timing Methodology

Both versions measure the same two things: the point-generation loop and the
combination of partial results. Worker creation, user input and RNG engine
construction are excluded from both.

- **MPI** starts the clock after `MPI_Barrier` (all ranks ready, engines built)
  and stops it after `MPI_Reduce` returns.
- **OpenMP** starts the clock *inside* the parallel region, after an explicit
  `omp barrier` guarantees every thread has built its engine, and stops it once
  the implicit barrier at the end of `omp for` has combined all partial counts.

In both cases the measurement is bounded by the slowest worker.

## Requirements

- An MPI implementation, e.g. [Open MPI](https://www.open-mpi.org/)
- GCC with OpenMP support — macOS's default `clang` does not support
  `-fopenmp` out of the box, so this project uses Homebrew's GCC.
  
## Build & Run

```zsh
make all                               # builds both targets

mpirun -np 8 ./MPI_MonteCarloPi        # MPI
OMP_NUM_THREADS=8 ./OMP_MonteCarloPi   # OpenMP

make clean                             # removes binaries and *.dSYM
```

Both prompt for the number of points to simulate. `Total_Points` is an `int`,
so the maximum supported input is 2,147,483,647.

> Changing the compiler flags requires `make clean` first — Make compares file
> timestamps and will not rebuild if only the Makefile changed.

## Test Environment

| | |
|---|---|
| Machine | MacBook Air 13" (M5, 2026), fanless |
| CPU | Apple M5 — 10 cores (4 performance + 6 efficiency) |
| Memory | 16 GB unified |
| OS | macOS *(macOS Tahoe 26.5.1)* |
| Compiler | GCC *(g++-16 (Homebrew GCC 16.1.0) 16.1.0)* |
| MPI | Open MPI *(mpirun (Open MPI) 5.0.9)* |
| Flags | `-O2 -std=c++17` |

## Results

Measured with 8 MPI processes / 8 OpenMP threads, 100 samples per configuration.

| Points | Processes/Threads | Samples | MPI Avg (s) | MPI Std Dev | MPI Min | MPI Max | OpenMP Avg (s) | OpenMP Std Dev | OpenMP Min | OpenMP Max |
|---|---|---|---|---|---|---|---|---|---|---|
| 1,000,000 | 8 | 100 | 0.001951 | 0.000169 | 0.001788 | 0.003408 | 0.001893 | 0.000081 | 0.001480 | 0.002315 |
| 10,000,000 | 8 | 100 | 0.017994 | 0.001119 | 0.016558 | 0.024202 | 0.017840 | 0.001041 | 0.016655 | 0.025259 |
| 100,000,000 | 8 | 100 | 0.174415 | 0.005545 | 0.164379 | 0.200776 | 0.186258 | 0.008706 | 0.178027 | 0.231024 |
| 1,000,000,000 | 8 | 100 | 2.446788 | 0.544937 | 1.645890 | 3.411870 | 2.918176 | 0.117417 | 2.739760 | 3.233580 |

All times in seconds. Avg Pi at 1,000,000,000 points: 3.141589 (MPI) / 3.141596 (OpenMP).

## Author

[Inkyy06](https://github.com/Inkyy06)
