#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

double calc_fuel(double mass)
{
    return floor(mass / 3.0) - 2.0;
}

int main()
{
    // Calculate fuel required for the mass of the rocket
    double mass = 0;
    double fuel_for_mass = 0;
    double total_fuel_mass = 0;
    double new_total_fuel_mass = 0;
    // std::ifstream infile("test.txt");
    std::ifstream infile("modules.txt");
    while (infile >> mass)
    {
        fuel_for_mass = calc_fuel(mass);
        total_fuel_mass += fuel_for_mass;
        while (fuel_for_mass > 0.0)
        {
            new_total_fuel_mass += fuel_for_mass;
            fuel_for_mass = calc_fuel(fuel_for_mass);
        }
    }
    std::cout.precision(9);
    cout << "Fuel Required For Mass: " << total_fuel_mass << "\n";
    cout << "Total Fuel Required: " << new_total_fuel_mass << "\n";

    std::cout.precision(9);

    return 0;
}