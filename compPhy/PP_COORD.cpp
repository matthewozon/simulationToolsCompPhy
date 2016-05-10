#include "PP_COORD.h"

PP_COORD::PP_COORD()
{
    x=0.0;
    y=0.0;
    z=0.0;
}

PP_COORD::PP_COORD(double _x, double _y, double _z)
{
    x=_x;
    y=_y;
    z=_z;
}



PP_COORD::PP_COORD(PP_COORD &c)
{
    x=c.x;
    y=c.y;
    z=c.z;
}


PP_COORD::PP_COORD(const PP_COORD &c)
{
    x=c.x;
    y=c.y;
    z=c.z;
}



//instanciation
PP_COORD PP_COORD::operator= (PP_COORD const& c)
{
    this->x=c.x;
    this->y=c.y;
    this->z=c.z;
    return *this;
}

PP_COORD PP_COORD::operator= (double const& a)
{
    this->x=a;
    this->y=a;
    this->z=a;
    return *this;
}







//additions
PP_COORD PP_COORD::operator+ (PP_COORD const& c)
{
    PP_COORD b(*this);
    b+=c;
    return b;
}

PP_COORD PP_COORD::operator+ (double const& a)
{
    PP_COORD b(*this);
    b+=a;
    return b;
}


void PP_COORD::operator+= (PP_COORD const& c)
{
    this->x+=c.x;
    this->y+=c.y;
    this->z+=c.z;
    return;
}

void PP_COORD::operator+= (double const& a)
{
    this->x+=a;
    this->y+=a;
    this->z+=a;
    return;
}

PP_COORD PP_COORD::operator- (PP_COORD const& c)
{
    PP_COORD b(*this);
    b-=c;
    return b;
}

PP_COORD PP_COORD::operator- (double const& a)
{
    PP_COORD b(*this);
    b-=a;
    return b;
}


void PP_COORD::operator-= (PP_COORD const& c)
{
    this->x-=c.x;
    this->y-=c.y;
    this->z-=c.z;
    return;
}

void PP_COORD::operator-= (double const& a)
{
    this->x-=a;
    this->y-=a;
    this->z-=a;
    return;
}

PP_COORD PP_COORD::operator* (double const& a)
{
    PP_COORD b(*this);
    b*=a;
    return b;
}

void PP_COORD::operator*= (double const& a)
{
    x*=a;
    y*=a;
    z*=a;
    return;
}


//other tools
double PP_COORD::inner(PP_COORD const& c)
{
    return x*c.x+y*c.y+z*c.z;
}

double PP_COORD::inner(PP_COORD & c)
{
    return inner( (PP_COORD const&) c);
}

PP_COORD PP_COORD::cross(PP_COORD const& c)
{
    PP_COORD b;
    b.x = y*c.z - z*c.y;
    b.y = z*c.x - x*c.z;
    b.z = x*c.y - y*c.x;
    return b;
}

PP_COORD PP_COORD::cross(PP_COORD & c)
{
    return cross( (PP_COORD const&) c);
}


bool PP_COORD::all(void)
{
    if(x==1.0 && y==1.0 && z==1.0) return true;
    else return false;
}

PP_COORD PP_COORD::operator== (PP_COORD const& c)
{
    PP_COORD b;//init to the null vector
    if(x==c.x) b.x=1.0;
    if(y==c.y) b.y=1.0;
    if(z==c.z) b.z=1.0;
    return b;
}

PP_COORD PP_COORD::operator== (double const& a)
{
    PP_COORD b;//init to the null vector
    if(x==a) b.x=1.0;
    if(y==a) b.y=1.0;
    if(z==a) b.z=1.0;
    return b;
}



PP_COORD PP_COORD::operator> (PP_COORD const& c)
{
    PP_COORD b;//init to the null vector
    if(x>c.x) b.x=1.0;
    if(y>c.y) b.y=1.0;
    if(z>c.z) b.z=1.0;
    return b;
}

PP_COORD PP_COORD::operator> (double const& a)
{
    PP_COORD b;//init to the null vector
    if(x>a) b.x=1.0;
    if(y>a) b.y=1.0;
    if(z>a) b.z=1.0;
    return b;
}



PP_COORD PP_COORD::operator>= (PP_COORD const& c)
{
    PP_COORD b;//init to the null vector
    if(x>=c.x) b.x=1.0;
    if(y>=c.y) b.y=1.0;
    if(z>=c.z) b.z=1.0;
    return b;
}

PP_COORD PP_COORD::operator>= (double const& a)
{
    PP_COORD b;//init to the null vector
    if(x>=a) b.x=1.0;
    if(y>=a) b.y=1.0;
    if(z>=a) b.z=1.0;
    return b;
}











PP_COORD PP_COORD::operator< (PP_COORD const& c)
{
    PP_COORD b;//init to the null vector
    if(x<c.x) b.x=1.0;
    if(y<c.y) b.y=1.0;
    if(z<c.z) b.z=1.0;
    return b;
}

PP_COORD PP_COORD::operator< (double const& a)
{
    PP_COORD b;//init to the null vector
    if(x<a) b.x=1.0;
    if(y<a) b.y=1.0;
    if(z<a) b.z=1.0;
    return b;
}



PP_COORD PP_COORD::operator<= (PP_COORD const& c)
{
    PP_COORD b;//init to the null vector
    if(x<=c.x) b.x=1.0;
    if(y<=c.y) b.y=1.0;
    if(z<=c.z) b.z=1.0;
    return b;
}

PP_COORD PP_COORD::operator<= (double const& a)
{
    PP_COORD b;//init to the null vector
    if(x<=a) b.x=1.0;
    if(y<=a) b.y=1.0;
    if(z<=a) b.z=1.0;
    return b;
}
