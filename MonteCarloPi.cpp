#include <iostream>
#include <random>

int main(){

    int N;
    int count = 0;
    double Total_Points_Inside_Circle = 0;
    double MonteCarloPi;

    //Random number engine
    std::mt19937 engine(std::random_device{}());
    //random number distribution x
    std::uniform_real_distribution<double> distX(-1.0, 1.0);
    //random number distribution Y
    std::uniform_real_distribution<double> distY(-1.0, 1.0);

    //accepts user input
    do{
        std::cout << "Enter the amount of points: ";
        std::cin >> N;

        if(N <= 0){
            std::cout << "Please enter a positive value!\n";
        }
    
    }while(N <= 0);

    //generates random N(user input) points 
    while(count < N){
        //generates a point
        double x = distX(engine);
        double y = distY(engine);
        std::cout << "Point " << count + 1 << ": x = "<< x << " y = " << y << '\n';

        //checks if the point is in circle
        if(x * x + y * y <= 1){
            Total_Points_Inside_Circle++;
        }

        count++;
    }

    //prints the estimated pi
    MonteCarloPi = 4 * (Total_Points_Inside_Circle/count);
    std::cout << "ESTIMATED PI = " << MonteCarloPi << '\n'; 
    
    return 0;
}