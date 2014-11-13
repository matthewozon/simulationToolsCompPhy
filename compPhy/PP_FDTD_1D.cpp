#include <PP_FDTD_1D.h>

PP_FDTD_1D::PP_FDTD_1D()
{
    dt = 1.0;
    DT = 10.0;
    dz = 1.0;
    DZ = 10.0;
    R = 0.0;
    L = 1.0;
    C = 1.0;
    G = 0.0;
    Nt = (unsigned long) (DT/dt);
    Nz = (unsigned long) (DZ/dz);
    V = myAllocator.allocateDouble(Nt,Nz);
    I = myAllocator.allocateDouble(Nt,Nz);
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
    V = myAllocator.allocateDouble(Nt,Nz);
    I = myAllocator.allocateDouble(Nt,Nz);
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
    myAllocator.dealocate(V,Nt);
    myAllocator.dealocate(I,Nt);
}


void PP_FDTD_1D::calculateCoefficients(void)
{
    c1 = -2.0*dt/((dt*dz*R)+(2.0*dz*L));
    c2 = ((2*L)-(dt*R))/((2*L)+(dt*R));

    c3 = -2.0*dt/((dt*dz*G)+(2.0*dz*C));
    c4 = ((2*C)-(dt*G))/((2*C)+(dt*G));
    return;
}



bool PP_FDTD_1D::run(bool shortCircuit, bool borderExcitationON)
{
    //determine the coefficient of numerical iteration equations
    calculateCoefficients();

    //at t=0 initialize the whole space
    intialState();

    //iterations
    for(unsigned long n=1 ; n<Nt ; n++) //loop over time
    {
        //determine the next current over the whole space
        for(unsigned long k=1 ; k<Nz ; k++) //loop over space : may be multithread
        {
            //I[n][k] stands for i(k*dz, (n+0.5)*dt)
            //V[n][k] stands for v((k+0.5)*dz, n*dt)
            I[n][k] = c1*(V[n-1][k]-V[n-1][k-1]) + c2*I[n-1][k];

        }
        //border conditions for current: on the left because it is the state that cannot be calculated (correct me if I am wrong)
        if(shortCircuit)
        {
            I[n][0] = I[n][1];
        }
        else
        {
            I[n][0] = 0.0;
        }

        //deternmine the next voltage state
        if(borderExcitationON) //if we apply an excitation (input voltage)
        {
            borderExcitation(n);
            for(unsigned long k=1 ; k<(Nz-1) ; k++)
            {
                V[n][k] = c3*(I[n][k+1]-I[n][k]) + c4*V[n-1][k];
            }
        }
        else
        {
            for(unsigned long k=0 ; k<(Nz-1) ; k++)
            {
                V[n][k] = c3*(I[n][k+1]-I[n][k]) + c4*V[n-1][k];
            }
        }
        //boundary conditions on voltage: either 0 to simulate a short circuit or a miror condition for an open circuit
        if(shortCircuit)
        {
            V[n][Nz-1] = 0.0;
        }
        else
        {
            V[n][Nz-1] = V[n][Nz-2];
        }

    }

    return true;
}


void PP_FDTD_1D::intialState(void)
{
    V[0][0] = 1.0;
    /*for(unsigned long k=0 ; k<Nz ; k++)
    {
        //V[0][k] = cos(2*3.14161*4*k/Nz);
        //I[0][k] = cos(2*3.14161*4*k/Nz);
        if((10*k)>(Nz) && (10*k)<(2*Nz))
        {
            V[0][k] = 1.0;
            I[0][k] = 1.0;
        }
        else
        {
            V[0][k] = 0.0;
            I[0][k] = 0.0;
        }
    }*/
    return;
}

void PP_FDTD_1D::borderExcitation(unsigned long n)
{
    if(n<25) V[n][0] = 1.0;//sin(2*3.14161*6*n/Nt);
    else V[n][0] = 0.0;
    return;
}
