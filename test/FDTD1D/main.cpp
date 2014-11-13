#include <iostream>
#include <stdio.h>
#include <sstream>

#include <fstream>
#include <math.h>

#include <PP_FDTD_1D.h>


#define PI 3.14159265359L


int main()
{
    double dt = 0.02;
    double DT = 2.0;
    double dz = 0.05;
    double DZ = 1.0;
    PP_FDTD_1D rk(dt, DT, dz, DZ);

    rk.R = 2.0;
    rk.G = 2.0;
    rk.run(false,true);

    std::ofstream fI, fV;
    fI.open("resultsI", std::ios::out);
    fV.open("resultsV", std::ios::out);
    for(unsigned long k=0 ; k<rk.getSpatialLength() ; k++)
    {
        for(unsigned long n=0 ; n<rk.getTimeLength() ; n++)
        {
            fI << rk.getI(n,k) << " ";
            fV << rk.getV(n,k) << " ";
        }
        fI << "\n";
        fV << "\n";
    }

    fI.close();
    fV.close();

    return 0;
}

