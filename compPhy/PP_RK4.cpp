#include <PP_RK4.h>

PP_RK4::PP_RK4()
{
}

PP_RK4::PP_RK4(PP_RK4 const &other)
{
    //
}

PP_RK4::PP_RK4(PP_RK4 &other)
{
    //
}

PP_RK4::~PP_RK4()
{
    //
}

double* PP_RK4::F(double x, double y, double z, double t) const
{
    return 0;
}

double* PP_RK4::RK4step(double x, double y, double z, double t, double dt)
{
    double* K1 = RK4K1(x, y, z, t, dt);
    double* K2 = RK4K2(x, y, z, K1[0], K1[1], K1[2], t, dt);
    double* K3 = RK4K3(x, y, z, K2[0], K2[1], K2[2], t, dt);
    double* K4 = RK4K4(x, y, z, K3[0], K3[1], K3[2], t, dt);
    double* dr = new double[3];
    dr[0] = (1.0/6.0)*(K1[0] + 2.0*K2[0] + 2*K3[0] + K4[0]);
    dr[1] = (1.0/6.0)*(K1[1] + 2.0*K2[1] + 2*K3[1] + K4[1]);
    dr[2] = (1.0/6.0)*(K1[2] + 2.0*K2[2] + 2*K3[2] + K4[2]);
    delete K1;
    delete K2;
    delete K3;
    delete K4;
    return dr;
}
double* PP_RK4::RK4K1(double x, double y, double z, double t, double dt)
{
    double* K1 = F(x,y,z,t);
    K1[0] *= dt;
    K1[1] *= dt;
    K1[2] *= dt;
    return K1;
}
double* PP_RK4::RK4K2(double x, double y, double z, double k1x, double k1y, double k1z, double t, double dt)
{
    double* K2 = F(x+0.5*k1x,y+0.5*k1y,z+0.5*k1z,t+0.5*dt);
    K2[0] *= dt;
    K2[1] *= dt;
    K2[2] *= dt;
    return K2;
}
double* PP_RK4::RK4K3(double x, double y, double z, double k2x, double k2y, double k2z, double t, double dt)
{
    double* K3 = F(x+0.5*k2x,y+0.5*k2y,z+0.5*k2z,t+0.5*dt);
    K3[0] *= dt;
    K3[1] *= dt;
    K3[2] *= dt;
    return K3;
}
double* PP_RK4::RK4K4(double x, double y, double z, double k3x, double k3y, double k3z, double t, double dt)
{
    double* K4 = F(x+k3x,y+k3y,z+k3z,t+dt);
    K4[0] *= dt;
    K4[1] *= dt;
    K4[2] *= dt;
    return K4;
}
