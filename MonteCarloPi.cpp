#include <iostream>
#include <random>

int main(){

    int points;
    int count = 0;
    double Total_Points_Inside_Circle = 0;
    double MonteCarloPi;

    //Random number engine X
    std::mt19937 engine(std::random_device{}());
    //random number distribution x
    std::uniform_real_distribution<double> distX(-1.0, 1.0);
    //random number distribution Y
    std::uniform_real_distribution<double> distY(-1.0, 1.0);
    
    do{
        std::cout << "Enter the amount of points: ";
        std::cin >> points;

        if(points <= 0){
            std::cout << "Please enter a positive value!\n";
        }
    }while(points <= 0);

    while(count < points){
        double x = distX(engine);
        double y = distY(engine);
        std::cout << "Point " << count + 1 << ": x = "<< x << " y = " << y << '\n';

        if(x * x + y * y <= 1){
            Total_Points_Inside_Circle++;
        }

        count++;
    }

    MonteCarloPi = 4 * (Total_Points_Inside_Circle/count);
    std::cout << "PI = " << MonteCarloPi << '\n'; 
    
    return 0;
}