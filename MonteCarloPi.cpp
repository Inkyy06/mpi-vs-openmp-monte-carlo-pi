#include <iostream>
#include <random>
#include <omp.h>

int main(){

    int N;
    double Total_Points_Inside_Circle = 0;
    double MonteCarloPi;

    //accepts user input
    do{
        std::cout << "Enter the amount of points: ";
        std::cin >> N;

        if(N <= 0){
            std::cout << "Please enter a positive value!\n";
        }
    
    }while(N <= 0);

    /*  generates random N(user input) points, 
        and keeps track of total number of points and number of points inside the circle */
    #pragma omp parallel
    {

        //Random number engine
        std::mt19937 engine(std::random_device{}() + omp_get_thread_num());
        //random number distribution X
        std::uniform_real_distribution<double> distX(-1.0, 1.0);
        //random number distribution Y
        std::uniform_real_distribution<double> distY(-1.0, 1.0);

        #pragma omp for reduction(+:Total_Points_Inside_Circle)    
        for(int count = 0; count < N; count++){
            //generates a point
            double x = distX(engine);
            double y = distY(engine);

            //checks if the point is in circle
            if(x * x + y * y <= 1){
                Total_Points_Inside_Circle++;
            }
        }
    }

    //prints the estimated pi
    MonteCarloPi = 4 * (Total_Points_Inside_Circle/N);
    std::cout << "ESTIMATED PI = " << MonteCarloPi << '\n'; 
    
    return 0;
}