#include <PP_FDTD_1D.h>

PP_FDTD_1D::PP_FDTD_1D()
{
    dt = 1.0;
    DT = 10.0;
    dz = 1.0;
    DZ = 10.0;
    R = 1.0;
    L = 1.0;
    C = 1.0;
    G = 1.0;
    Nt = (unsigned long) (DT/dt);
    Nz = (unsigned long) (DZ/dz);
    v0 = allocate(Nz);
    i0 = allocate(Nz);
}


PP_FDTD_1D::PP_FDTD_1D(double _dt, double _DT, double _dz, double _DZ, double _R, double _L, double _C, double _G)
{
    dt = _dt;
    DT = _DT;
    dz = _dz;
    DZ = _DZ;
    R = _R;
    L = _L;
    C = _C;
    G = _G;
    Nt = (unsigned long) (DT/dt);
    Nz = (unsigned long) (DZ/dz);
    v0 = allocate(Nz);
    i0 = allocate(Nz);
}

PP_FDTD_1D::PP_FDTD_1D(PP_FDTD_1D const &other)
{
    this->dt = other.dt;
    this->DT = other.DT;
    this->dz = other.dz;
    this->DZ = other.DZ;
    this->R = other.R;
    this->L = other.L;
    this->C = other.C;
    this->G = other.G;
    this->Nt = other.Nt;
    this->Nz = other.Nz;

    //copy initial conditions


}

PP_FDTD_1D::PP_FDTD_1D(PP_FDTD_1D &other)
{
    this->dt = other.dt;
    this->DT = other.DT;
    this->dz = other.dz;
    this->DZ = other.DZ;
    this->R = other.R;
    this->L = other.L;
    this->C = other.C;
    this->G = other.G;
    this->Nt = other.Nt;
    this->Nz = other.Nz;

    //copy initial conditions


}

PP_FDTD_1D::~PP_FDTD_1D()
{
    dealocate(v0);
    dealocate(i0);
}

double * PP_FDTD_1D::allocate(unsigned long N)
{
    return new double[N];
}

void PP_FDTD_1D::dealocate(double* X)
{
    if(X!=NULL)
    {
        delete X;
    }
    X = NULL;
}


double PP_FDTD_1D::getv0(unsigned long i)
{
    if(i<Nz && v0!=NULL) return v0[i];
    else return 0.0;
}
double PP_FDTD_1D::geti0(unsigned long i)
{
    if(i<Nz && i0!=NULL) return i0[i];
    else return 0.0;
}

void PP_FDTD_1D::setv0(unsigned long i, double myValue)
{
    if(i<Nz && v0!=NULL) v0[i]=myValue;
}
void PP_FDTD_1D::seti0(unsigned long i, double myValue)
{
    if(i<Nz && i0!=NULL) i0[i]=myValue;
}

void PP_FDTD_1D::calculateCoefficients(void)
{
    //
}

double PP_FDTD_1D::computeStepCurrent(unsigned long n, unsigned long k)
{
    //
}

double PP_FDTD_1D::computeStepVoltage(unsigned long n, unsigned long k)
{
    //
}
