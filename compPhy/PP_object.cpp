#include "PP_object.h"

PP_object::PP_object()
{
    R=0.0;
}

PP_object::PP_object(PP_COORD p, PP_COORD _v, double _R)
{
    coord=p;
    v=_v;
    R=_R;
}

PP_object::PP_object(PP_COORD p, double _R)
{
    coord=p;
    v=0.0;
    R=_R;
}

PP_object::PP_object(PP_object const &p)
{
    coord=p.coord;
    v=p.v;
    R=p.R;
}

PP_object::PP_object(PP_object &p)
{
    coord=p.coord;
    v=p.v;
    R=p.R;
}

//PP_object PP_object::operator= (PP_object & c)
//{
//    coord=c.coord;
//    v=c.v;
//    R=c.R;
//    return *this;
//}

//PP_object PP_object::operator= (PP_object const& c)
//{
//    coord=c.coord;
//    v=c.v;
//    R=c.R;
//    return *this;
//}
