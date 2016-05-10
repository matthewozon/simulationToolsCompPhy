//class that defines coordinates and the possible operation on vectors

#ifndef PP_COORD_H
#define PP_COORD_H

class PP_COORD
{
public:
    PP_COORD();

    PP_COORD(double _x, double _y, double _z);
    PP_COORD(PP_COORD &c);
    PP_COORD(const PP_COORD &c);

    ~PP_COORD(){}//nothing to do

    double x;
    double y;
    double z;

    //overload vectorial space basic operation +-*
    PP_COORD operator= (PP_COORD const& c);
    PP_COORD operator= (double const& a);
    PP_COORD operator+ (PP_COORD const& c);
    PP_COORD operator+ (double const& a);
    void operator+= (PP_COORD const& c);
    void operator+= (double const& a);
    PP_COORD operator- (PP_COORD const& c);
    PP_COORD operator- (double const& a);
    void operator-= (PP_COORD const& c);
    void operator-= (double const& a);
    PP_COORD operator* (double const& a);
    void operator*= (double const& a);

    //ohter tools
    double inner(PP_COORD const& c);
    double inner(PP_COORD & c);
    PP_COORD cross(PP_COORD const& c);
    PP_COORD cross(PP_COORD & c);
    bool all(void);
    PP_COORD operator== (PP_COORD const& c);
    PP_COORD operator== (double const& a);
    PP_COORD operator> (PP_COORD const& c);
    PP_COORD operator> (double const& a);
    PP_COORD operator>= (PP_COORD const& c);
    PP_COORD operator>= (double const& a);
    PP_COORD operator< (PP_COORD const& c);
    PP_COORD operator< (double const& a);
    PP_COORD operator<= (PP_COORD const& c);
    PP_COORD operator<= (double const& a);
};

#endif // PP_COORD_H
