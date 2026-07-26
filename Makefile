OMP_MonteCarloPi: OMP_MonteCarloPi.cpp
	/opt/homebrew/bin/g++-16 -fdiagnostics-color=always -g OMP_MonteCarloPi.cpp -o OMP_MonteCarloPi -fopenmp
MPI_MonteCarloPi: MPI_MonteCarloPi.cpp
	mpicxx -g MPI_MonteCarloPi.cpp -o MPI_MonteCarloPi