# MPI vs OpenMP Monte Carlo Pi Estimation

Estimates Pi using the Monte Carlo method, implemented in both MPI and OpenMP to compare their performance.

## How It Works

Random points are generated inside a 2x2 square; the ratio of points falling inside the inscribed unit circle approximates Pi/4.

## Implementation Details

**MPI version** (`MPI_MonteCarloPi.cpp`):
- Rank 0 reads the number of points and broadcasts it via `MPI_Bcast`.
- Each rank generates its own share of points (`Total_Points / size`) with a rank-specific random seed; any remainder is added to the last rank so the total matches exactly.
- Local hit counts are summed across all ranks using `MPI_Reduce` (`MPI_SUM`).
- Rank 0 computes and prints the final estimate and elapsed time.

**OpenMP version** (`OMP_MonteCarloPi.cpp`):
- The main thread reads the number of points.
- `#pragma omp parallel` spawns threads, each with its own thread-specific random seed.
- `#pragma omp for reduction(+:...)` splits the loop across threads and safely combines hit counts.
- Elapsed time is measured with `omp_get_wtime()`.

## Requirements

- MPI implementation (e.g. [Open MPI](https://www.open-mpi.org/))
- A GCC compiler with OpenMP support — on macOS, the default `clang` does not support `-fopenmp` out of the box, so this project uses Homebrew's GCC.

macOS setup:
```zsh
brew install open-mpi gcc
```
```zsh
brew install libomp
```

## Build & Run

```zsh
make MPI_MonteCarloPi 
mpirun -np 8 ./MPI_MonteCarloPi        # MPI

make OMP_MonteCarloPi
OMP_NUM_THREADS=8 ./OMP_MonteCarloPi   # OpenMP
```

Both prompt for the number of points to simulate.

> Note: the OpenMP target is built with `g++-16` and `-fopenmp`, while the MPI target is built with `mpicxx`. See the `Makefile` for exact build rules.

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
