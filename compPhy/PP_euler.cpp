#include <PP_euler.h>

PP_EULER::PP_EULER()
{
}
PP_EULER::PP_EULER(PP_EULER const &other)
{
    //
}

PP_EULER::PP_EULER(PP_EULER &other)
{
    //
}

PP_EULER::~PP_EULER()
{
    //
}

double* PP_EULER::F(double x, double y, double z, double t) const
{
    return 0;
}

double* PP_EULER::EULERstep(double x, double y, double z, double t, double dt)
{
    double* dr = F(x,y,z,t);
    dr[0] *= dt;
    dr[1] *= dt;
    dr[2] *= dt;
    return dr;
}
