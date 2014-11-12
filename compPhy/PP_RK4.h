#ifndef PP_RK4_H
#define PP_RK4_H

class PP_RK4
{
public:
    PP_RK4();
    PP_RK4(PP_RK4 const &other);
    PP_RK4(PP_RK4 &other);
    ~PP_RK4();

    //function that define the cauchy problem : d/dt(x,y,z)(t) = F(x,y,z,t), (x,y,z)(t0) = (x0,y0,z0).
    virtual double* F(double x, double y, double z, double t) const = 0; //an example is given in the cpp file, but it must be customized for your own problem

    //integration step
    double* RK4step(double x, double y, double z, double t, double dt);

private:
    //element of Runge-Kutta method (4th order)
    double* RK4K1(double x, double y, double z, double t, double dt);
    double* RK4K2(double x, double y, double z, double k1x, double k1y, double k1z, double t, double dt);
    double* RK4K3(double x, double y, double z, double k2x, double k2y, double k2z, double t, double dt);
    double* RK4K4(double x, double y, double z, double k3x, double k3y, double k3z, double t, double dt);
};











#endif // PP_RK4_H
