#ifndef BIDON_H
#define BIDON_H

#define SQR(x) ((x)*(x))

#include <math.h>
#include <fstream>

#include <PP_RK4.h>

class bidon : public PP_RK4
{
public:
    bidon();


    void solveEquationAndSaveToFile(double x0, double y0, double z0, double t0, double dt, std::string fileName);

    virtual double* F(double x, double y, double z, double t) const;


};

#endif
