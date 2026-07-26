#include <iostream>
#include <random>
#include <mpi.h>

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;
    double Points_Inside_Circle = 0;
    double Local_Points_Inside_Circle = 0;
    int Total_Points, Points_Per_Rank;
    double PI_ESTIMATE;
    double start_time, end_time, elapsed_time;

    //Get this procces's id
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //get the total amount of procceses
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //rank 0(root) prompts user for input, checks if the input is a positive number
    if(rank == 0){
        do{
            std::cout << "Enter the amount of points: " << std::endl;
            std::cin >> Total_Points;

            if(Total_Points <= 0){
            std::cout << "Please enter a positive number!" << std::endl;
            }

        }while(Total_Points <= 0);
    }

    //Broadcasts(sends) the Total_points value from rank 0(root) to other ranks
    MPI_Bcast(&Total_Points, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //random number engine
    std::mt19937 engine(std::random_device{}() + rank);
    //X coordiante distribution
    std::uniform_real_distribution<double> distX(-1.0, 1.0);
    //Y coordinate distribution
    std::uniform_real_distribution<double> distY(-1.0, 1.0);

    //synchronize the processes
    MPI_Barrier(MPI_COMM_WORLD);

    start_time = MPI_Wtime();

    //Shares the total amount of points that will be generated, between each process equally
    Points_Per_Rank = Total_Points/size;

    //Adds the remainder of Total_Points/size to the last rank
    if(rank == size - 1){
        Points_Per_Rank += Total_Points % size;
    }

    for(int count = 0; count < Points_Per_Rank; count++){

        //generates a random point
        double x = distX(engine); 
        double y = distY(engine);

        //checks if the point is in circle
        if(x * x + y * y <= 1){
            Local_Points_Inside_Circle++;
        }
    }

    // Sum up Local_Points_Inside_Circle from all ranks into Points_Inside_Circle on rank 0
    MPI_Reduce(&Local_Points_Inside_Circle, &Points_Inside_Circle, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();

    //calculates the spent time
    elapsed_time = end_time - start_time;

    //rank 0(root) calculates the estimated pi and prints both estimated pi and elapsed time
    if(rank == 0){

        PI_ESTIMATE = 4 * (Points_Inside_Circle/Total_Points);

        std::cout << "ESTIMATED PI = " << PI_ESTIMATE << '\n';
        std::cout << "Passed Time = " << elapsed_time << '\n';
    }

    MPI_Finalize();

    return 0;
}