#ifndef PP_EULER_H
#define PP_EULER_H

class PP_EULER
{
public:
    PP_EULER();
    PP_EULER(PP_EULER const &other);
    PP_EULER(PP_EULER &other);
    ~PP_EULER();

    virtual double* F(double x, double y, double z, double t) const;
    double* EULERstep(double x, double y, double z, double t, double dt);
};

#endif // PP_EULER_H
