#include <bidon.h>

bidon::bidon():PP_EULER()
{
    //
}

void bidon::solveEquationAndSaveToFile(double x0, double y0, double z0, double t0, double dt, std::string fileName)
{
    std::ofstream f;
    f.open(fileName.data(), std::ios::out);
    double t = t0;
    double x = x0;
    double y = y0;
    double z = z0;
    double* dr;
    f << t << ", " << x << ", " << y << ", " << z << std::endl;
    for(unsigned long i=0 ; i<10000 ; i++)
    {
         dr = EULERstep(x, y, z, t, dt);
         t+=dt;
         x+=dr[0];
         y+=dr[1];
         z+=dr[2];
         delete dr;
         f << t << ", " << x << ", " << y << ", " << z << std::endl;
    }
    f.close();
    return;
}


double* bidon::F(double x, double y, double z, double t) const
{
    double r = sqrt(SQR(x) + SQR(y));
    double cosTheta = x/r;
    double sinTheta = y/r;
    double* v = new double[3];
    v[0] = -0.005*t*r*sinTheta;
    v[1] = r*cosTheta;
    v[2] = 0.5;
    return v;
}
