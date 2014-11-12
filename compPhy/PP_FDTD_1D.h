#ifndef PP_FDTD_1D_H
#define PP_FDTD_1D_H

#include <stdlib.h>

//http://www.phys.ubbcluj.ro/~emil.vinteler/nanofotonica/FDTD/FDTD_Nagel.pdf

class PP_FDTD_1D
{
public:
    PP_FDTD_1D();
    PP_FDTD_1D(double _dt, double _DT, double _dz, double _DZ, double _R=1.0, double _L=1.0, double _C=1.0, double _G=1.0);
    PP_FDTD_1D(PP_FDTD_1D const &other);
    PP_FDTD_1D(PP_FDTD_1D &other);
    virtual ~PP_FDTD_1D();


    double R; //linear resitance
    double L; //linear inductance
    double C; //linear capacitance
    double G; //linear conductance

    unsigned long getTimeLength(void){return Nt;}
    unsigned long getSpatialLength(void){return Nz;}

    double getv0(unsigned long i);
    double geti0(unsigned long i);

    void setv0(unsigned long i, double myValue);
    void seti0(unsigned long i, double myValue);



private:
    double* v0; //initial voltage at time t0 over the whole line
    double* i0; //initial current at time t0 over the whole line
    double * allocate(unsigned long N);
    void dealocate(double* X);
    unsigned long Nt; //discrete temporal length
    unsigned long Nz; //discrete spatial length

    double dt; //temporal integration step
    double DT; //temporal length of the signal
    double dz; //spatial integration step
    double DZ; //spatial length

    double c1;
    double c2;
    double c3;
    double c4;

    void calculateCoefficients(void);

    double computeStepCurrent(unsigned long n, unsigned long k);
    double computeStepVoltage(unsigned long n, unsigned long k);

};

#endif // PP_FDTD_1D_H
