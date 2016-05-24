// a PP_object is an abstract object that is characterized by its coordinates, speed and radius, but it has no physical existance

#ifndef PP_OBJECT_H
#define PP_OBJECT_H

#include "PP_COORD.h"


class PP_object
{
public:
    //ctor
    PP_object();
    PP_object(PP_COORD p, PP_COORD _v, double _R);
    PP_object(PP_COORD p, double _R);
    PP_object(PP_object const &p);
    PP_object(PP_object &p);

    //dtor
    ~PP_object(){}//nothing to do

    //characteristic coordinates of the object
    PP_COORD coord;

    //characteristic speed
    PP_COORD v;

    //characteristic radius (may change)
    double R;

    //temporal resolution
    double dt;

    //forces
    virtual PP_COORD force() =0;
};

#endif // PP_OBJECT_H
