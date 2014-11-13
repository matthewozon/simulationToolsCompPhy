#ifndef PP_FDTD_1D_H
#define PP_FDTD_1D_H

#include <PP_smartAlloc.h>

#include <math.h>


//http://www.phys.ubbcluj.ro/~emil.vinteler/nanofotonica/FDTD/FDTD_Nagel.pdf

class PP_FDTD_1D
{
public:
    PP_FDTD_1D();
    PP_FDTD_1D(double _dt, double _DT, double _dz, double _DZ, double _R=0.0, double _L=1.0, double _C=1.0, double _G=0.0);
    PP_FDTD_1D(PP_FDTD_1D const &other);
    PP_FDTD_1D(PP_FDTD_1D &other);
    virtual ~PP_FDTD_1D();


    double R; //linear resitance
    double L; //linear inductance
    double C; //linear capacitance
    double G; //linear conductance

    unsigned long getTimeLength(void){return Nt;}
    unsigned long getSpatialLength(void){return Nz;}

    double getI(unsigned long n, unsigned long k){return I[n][k];}
    double getV(unsigned long n, unsigned long k){return V[n][k];}

    bool run(bool shortCircuit=true, bool borderExcitationON=true);

    virtual void intialState(void);
    virtual void borderExcitation(unsigned long n);



private:
    PP_smartAlloc myAllocator;

    unsigned long Nt; //discrete temporal length
    unsigned long Nz; //discrete spatial length

    double** I; //I[n][k] stands for i(k*dz, (n+0.5)*dt)
    double** V; //V[n][k] stands for v((k+0.5)*dz, n*dt)


    double dt; //temporal integration step
    double DT; //temporal length of the signal
    double dz; //spatial integration step
    double DZ; //spatial length

    double c1;
    double c2;
    double c3;
    double c4;

    void calculateCoefficients(void);

};

#endif // PP_FDTD_1D_H
