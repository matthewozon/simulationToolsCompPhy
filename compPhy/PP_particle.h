//example of use of the class object for a particle characterized by two scalar values (m,e) (e.g. charged particle)
//you may introduce interaction with an external field, but no interaction between particles

#ifndef PP_PARTICLE_H
#define PP_PARTICLE_H

#include "PP_object.h"

class PP_particle : public PP_object
{
public:
    //ctor
    PP_particle();
    PP_particle(PP_COORD p, PP_COORD _v, double _R, double _m, double _e);
    PP_particle(PP_COORD p, double _R, double _m, double _e);
    PP_particle(PP_particle const &p);
    PP_particle(PP_particle &p);

    //operator =
    PP_particle operator= (PP_particle & c);
    PP_particle operator= (PP_particle const& c);

    //dtor
    ~PP_particle(){}//nothing to do?

    //mass
    double m;
    //electrical charge
    double e;

    virtual PP_COORD force();
};

#endif // PP_PARTICLE_H
