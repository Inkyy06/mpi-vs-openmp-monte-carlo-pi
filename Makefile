CXX_GCC  = /opt/homebrew/bin/g++-16
CXXFLAGS = -O2 -std=c++17 -g -fdiagnostics-color=always

.PHONY: all clean

all: MPI_MonteCarloPi OMP_MonteCarloPi

OMP_MonteCarloPi: OMP_MonteCarloPi.cpp
	$(CXX_GCC) $(CXXFLAGS) -fopenmp OMP_MonteCarloPi.cpp -o OMP_MonteCarloPi

MPI_MonteCarloPi: MPI_MonteCarloPi.cpp
	OMPI_CXX=$(CXX_GCC) mpicxx $(CXXFLAGS) MPI_MonteCarloPi.cpp -o MPI_MonteCarloPi

clean:
	rm -rf MPI_MonteCarloPi OMP_MonteCarloPi *.dSYM