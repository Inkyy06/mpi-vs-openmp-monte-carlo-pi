#include <iostream>
#include <random>
#include <omp.h>

int main(){

    int Total_Points;
    double Points_Inside_Circle = 0;
    double PI_ESTIMATE;
    double start_time, end_time, elapsed_time;

    //reads user input if the value is positive
    do{
        std::cout << "Enter the amount of points: ";
        std::cin >> Total_Points;

        if(Total_Points <= 0){
            std::cout << "Please enter a positive value!\n";
        }
    
    }while(Total_Points <= 0);

    start_time = omp_get_wtime();

    /*  generates random N(user input) points, 
        and keeps track of total number of points and number of points inside the circle */
    #pragma omp parallel
    {

        //Random number engine
        std::mt19937 engine(std::random_device{}() + omp_get_thread_num());
        //X coordiante distribution
        std::uniform_real_distribution<double> distX(-1.0, 1.0);
        //Y coordinate distribution
        std::uniform_real_distribution<double> distY(-1.0, 1.0);

        #pragma omp for reduction(+:Total_Points_Inside_Circle)    
        for(int count = 0; count < Total_Points; count++){
            //generates a random point
            double x = distX(engine);
            double y = distY(engine);

            //checks if the point is in circle
            if(x * x + y * y <= 1){
                Points_Inside_Circle++;
            }
        }
    }

    end_time = omp_get_wtime();

    //time spent on parallel region
    elapsed_time = end_time - start_time;

    //The estimated pi
    PI_ESTIMATE = 4 * (Points_Inside_Circle/Total_Points);

    std::cout << "ESTIMATED PI = " << PI_ESTIMATE << '\n'; 
    std::cout << "Passed Time = " << elapsed_time << " seconds" << '\n';
    
    return 0;
}