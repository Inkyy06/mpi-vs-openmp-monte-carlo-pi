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

| Points | Processes/Threads | MPI Time (s) | OpenMP Time (s) |
|---|---|---|---|
| - | 8 | - | - |

*To be filled in after benchmarking.*

## Author

[Inkyy06](https://github.com/Inkyy06)
