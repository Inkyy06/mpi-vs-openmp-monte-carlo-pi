MonteCarloPi: MonteCarloPi.cpp
	/opt/homebrew/bin/g++-16 -fdiagnostics-color=always -g MonteCarloPi.cpp -o MonteCarloPi -fopenmp
MPI_MonteCarloPi: MPI_MonteCarloPi.cpp
	mpicxx -g MPI_MonteCarloPi.cpp -o MPI_MonteCarloPi