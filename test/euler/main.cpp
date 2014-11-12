#include <iostream>
#include <stdio.h>
#include <sstream>


#include <bidon.h>


#define PI 3.14159265359L


int main()
{
    bidon euler;
    euler.solveEquationAndSaveToFile(1.0, 0.0, 0.0, 0.0, 0.02, "results");
    return 0;
}

