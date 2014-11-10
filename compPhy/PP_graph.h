#ifndef PP_GRAPH_H
#define PP_GRAPH_H

#include <stdlib.h>
#include <vector>
#include <MACRO.h>
#include <math.h>

#include <iostream> //for the method "show" in graph

//class PP_point;
class PP_edge;

class PP_point
{
    friend class PP_edge;
public:
    PP_point(double _x=0.0, double _y=0.0, double _z=0.0, bool attachable=true)
    {
        x=_x;
        y=_y;
        z=_z;
        canBePartOfGraph = attachable;
        e.clear();
    }

    PP_point( const PP_point& other )
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->e.clear();
        for(unsigned int i=0 ; i<other.e.size() ; i++)
            this->e.push_back(other.e.at(i));
        this->canBePartOfGraph = other.canBePartOfGraph;
    }

    PP_point( PP_point& other )
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->e.clear();
        for(unsigned int i=0 ; i<other.e.size() ; i++)
            this->e.push_back(other.e.at(i));
        this->canBePartOfGraph = other.canBePartOfGraph;
    }

    virtual ~PP_point()
    {
        e.clear();
    }

    //operators
    PP_point& operator= (PP_point const& c)
    {
        this->x = c.x;
        this->y = c.y;
        this->z = c.z;
        this->e.clear();
        for(unsigned int i=0 ; i<c.e.size() ; i++)
        {
            this->e.push_back(c.e.at(i));
        }
        this->canBePartOfGraph = c.canBePartOfGraph;
    }

    PP_point& operator= (PP_point & c)
    {
        this->x = c.x;
        this->y = c.y;
        this->z = c.z;
        this->e.clear();
        for(unsigned int i=0 ; i<c.e.size() ; i++)
        {
            this->e.push_back(c.e.at(i));
        }
        this->canBePartOfGraph = c.canBePartOfGraph;
    }

    bool operator== (PP_point const& c) //only based on spatial position
    {
        //if( (ABS(this->x-c.x)<0.001) && (ABS(this->y-c.y)<0.001) && (ABS(this->z-c.z)<0.001)) return true;
        //else return false;
        return (this->x==c.x) && (this->y==c.y) && (this->z==c.z);
    }

    bool operator== (PP_point & c) //only based on spatial position
    {
        //if( (ABS(this->x-c.x)<0.001) && (ABS(this->y-c.y)<0.001) && (ABS(this->z-c.z)<0.001)) return true;
        //else return false;
        return (this->x==c.x) && (this->y==c.y) && (this->z==c.z);
    }

    //for debug
    void show(void)
    {
        std::cout << "(x,y,z) = (" << x << "," << y << "," << z << ")" << std::endl;
    }

    //points coordinates
    double x;
    double y;
    double z;

    //binding properties
    bool canBePartOfGraph;
    std::vector<PP_edge> e;

    //here you can add physical properties: scalar, vector, matrix...
};

class PP_edge
{
    friend class PP_point;
public:
    PP_edge()
    {
        distp1p2 = -1.0;
    }

    PP_edge(PP_point _p1, PP_point _p2)
    {
        p1=_p1;
        p2=_p2;
        distp1p2 = sqrt(SQR(p1.x-p2.x) + SQR(p1.y-p2.y) + SQR(p1.z-p2.z));
    }
    PP_edge( const PP_edge& other )
    {
        this->p1 = other.p1;
        this->p2 = other.p2;
        this->distp1p2 = other.distp1p2;
    }
    PP_edge( PP_edge& other )
    {
        this->p1 = other.p1;
        this->p2 = other.p2;
        this->distp1p2 = other.distp1p2;
    }

    virtual ~PP_edge(){}


    PP_edge& operator= (PP_edge const& c)
    {
        this->p1 = c.p1;
        this->p2 = c.p2;
        this->distp1p2 = c.distp1p2;
    }

    PP_edge& operator= (PP_edge & c)
    {
        this->p1 = c.p1;
        this->p2 = c.p2;
        this->distp1p2 = c.distp1p2;
    }

    bool operator== (PP_edge const& c) //only based on spatial position
    {
        return (( (this->p1)==(c.p1)) && ((this->p2)==(c.p2))) || (((this->p1)==(c.p2)) && ((this->p2)==(c.p1)));
    }

    bool operator== (PP_edge & c) //only based on spatial position
    {
        return (( (this->p1)==(c.p1)) && ((this->p2)==(c.p2))) || (((this->p1)==(c.p2)) && ((this->p2)==(c.p1)));
    }

    bool operator== (PP_point const& c) //only based on spatial position
    {
        return ( ((this->p1)==c) || ((this->p2)==c) );
    }

    bool operator== (PP_point & c) //only based on spatial position
    {
        return ( ((this->p1)==c) || ((this->p2)==c) );
    }

    PP_point p1;
    PP_point p2;

    //here can add a physical property: attraction forces, repulsion, transmitance... depending on two points (interaction)
    double distp1p2;
};









class PP_graph //set of points and edges
{
public:
    PP_graph();//do nothing, points would be added afterward
    PP_graph( const PP_graph& other );
    PP_graph( PP_graph& other );

    PP_point& operator() (const unsigned int i);
    const PP_point& operator() (const unsigned int i) const;

    //void addPoint(PP_point & p); would be P.push_back(p)
    void bindClosestNeighbors(double R);
    //void bindLastPoint(double R);
    double euclideanDistance(PP_point* p1, PP_point* p2);
    //may add a remove point that handle removing a point in the whole graph
    void removePoint(unsigned int ii);

    //add method show: for debug
    void show(void);

    //set of points (contains all edges)
    std::vector<PP_point> P;
};

PP_graph::PP_graph()
{
}

PP_graph::PP_graph( const PP_graph& other )
{
    for(unsigned int i=0 ; i<other.P.size() ; i++)
        this->P.push_back(other.P.at(i));
}

PP_graph::PP_graph( PP_graph& other )
{
    for(unsigned int i=0 ; i<other.P.size() ; i++)
        this->P.push_back(other.P.at(i));
}

PP_point& PP_graph::operator() (const unsigned int i)
{
    return P.at(i);
}

const PP_point& PP_graph::operator() (const unsigned int i) const
{
    return P.at(i);
}

void PP_graph::bindClosestNeighbors(double R)
{
    double D;
    //for all point
    for(unsigned int i=0 ; i<P.size() ; i++)
    {
        //go through all points
        for(unsigned int j=i+1 ; j<P.size() ; j++)
        {
            //calculate the distance
            D = euclideanDistance(&(P.at(i)),  &(P.at(j)));
            //D = euclideanDistance(&((*this)(i)),  &((*this)(j)));
            if(D<=R)
            {
                PP_edge tmp(P.at(i),  P.at(j));
                //PP_edge tmp(&((*this)(i)),  &((*this)(j)));
                P.at(i).e.push_back(tmp);
                //(*this)(i).e.push_back(tmp);
                P.at(j).e.push_back(tmp);
                //(*this)(j).e.push_back(tmp);
            }
        }
    }
    return;
}

double PP_graph::euclideanDistance(PP_point* p1, PP_point* p2)
{
    if(p1==NULL || p2==NULL) throw "null pointer in PP_graph::euclideanDistance";
    return sqrt(SQR(p1->x-p2->x) + SQR(p1->y-p2->y) + SQR(p1->z-p2->z));
}


void PP_graph::removePoint(unsigned int ii)
{
    //remove edges that contain P.at(ii)
    for(unsigned int i=0 ; i<P.size() ; i++)
    {
        if(i!=ii)
        {
            //test each edge of current point
            for(unsigned int j=0 ; j<P.at(i).e.size() ; j++)
            {
                if(P.at(i).e.at(j)==P.at(ii))//check if P.at(ii) is one of the points in edge P.at(i).e.at(j)
                {
                    P.at(i).e.erase(P.at(i).e.begin()+j);
                    j = P.at(i).e.size();
                }
            }
        }
    }

    //remove the point from graph
    P.erase(P.begin()+ii);
    return;
}


void PP_graph::show(void)
{
    PP_point otherPoint;
    for(unsigned int i=0 ; i<P.size() ; i++)
    {
        std::cout << "Point " << i << "(x,y,z) = (" << P.at(i).x << "," << P.at(i).y << "," << P.at(i).z << ")" << std::endl;
        for(unsigned int j=0 ; j<P.at(i).e.size() ; j++)
        {
            if(P.at(i)==(P.at(i).e.at(j).p1))
            {
                otherPoint = P.at(i).e.at(j).p2;
            }
            else
            {
                otherPoint = P.at(i).e.at(j).p1;
            }
            std::cout << "\tPoint bound to: (x,y,z) = (" << otherPoint.x << "," << otherPoint.y << "," << otherPoint.z << ") by edge " << j << std::endl;
        }
    }

    std::cout << std::endl;
}

#endif // PP_GRAPH_H









/*
class PP_edge
{
    friend class PP_point;
public:
    PP_edge()
    {
        p1=NULL;
        p2=NULL;
        distp1p2 = -1.0;
    }

    PP_edge(PP_point* _p1, PP_point* _p2)
    {
        p1=_p1;
        p2=_p2;
        distp1p2 = sqrt(SQR(p1->x-p2->x) + SQR(p1->y-p2->y) + SQR(p1->z-p2->z));
    }
    PP_edge( const PP_edge& other )
    {
        this->p1 = other.p1;
        this->p2 = other.p2;
        this->distp1p2 = other.distp1p2;
    }
    PP_edge( PP_edge& other )
    {
        this->p1 = other.p1;
        this->p2 = other.p2;
        this->distp1p2 = other.distp1p2;
    }

    virtual ~PP_edge(){}


    PP_edge& operator= (PP_edge const& c)
    {
        this->p1 = c.p1;
        this->p2 = c.p2;
        this->distp1p2 = c.distp1p2;
    }

    PP_edge& operator= (PP_edge & c)
    {
        this->p1 = c.p1;
        this->p2 = c.p2;
        this->distp1p2 = c.distp1p2;
    }

    bool operator== (PP_edge const& c) //only based on spatial position
    {
        return ((*(this->p1)==*(c.p1)) && (*(this->p2)==*(c.p2))) || ((*(this->p1)==*(c.p2)) && (*(this->p2)==*(c.p1)));
    }

    bool operator== (PP_edge & c) //only based on spatial position
    {
        return ((*(this->p1)==*(c.p1)) && (*(this->p2)==*(c.p2))) || ((*(this->p1)==*(c.p2)) && (*(this->p2)==*(c.p1)));
    }

    PP_point* p1;
    PP_point* p2;

    //here can add a physical property: attraction forces, repulsion, transmitance... depending on two points (interaction)
    double distp1p2;
};
*/
