#include "PP_particle.h"

PP_particle::PP_particle():PP_object()
{
    m=0.0;
    e=0.0;
}

PP_particle::PP_particle(PP_COORD p, PP_COORD _v, double _R, double _m, double _e):PP_object(p, _v,_R)
{
    m=_m;
    e=_e;
}

PP_particle::PP_particle(PP_COORD p, double _R, double _m, double _e):PP_object(p,_R)
{
    m=_m;
    e=_e;
}

PP_particle::PP_particle(PP_particle const &p)
{
    coord=p.coord;
    v=p.v;
    R=p.R;
    m=p.m;
    e=p.e;
}

PP_particle::PP_particle(PP_particle &p)
{
    coord=p.coord;
    v=p.v;
    R=p.R;
    m=p.m;
    e=p.e;
}

PP_COORD PP_particle::force()
{
    PP_COORD F;
    F=0.0;
    return F;
}


PP_particle PP_particle::operator= (PP_particle & c)
{
    coord=c.coord;
    v=c.v;
    R=c.R;
    m=c.m;
    e=c.e;
    return *this;
}

PP_particle PP_particle::operator= (PP_particle const& c)
{
    coord=c.coord;
    v=c.v;
    R=c.R;
    m=c.m;
    e=c.e;
    return *this;
}
