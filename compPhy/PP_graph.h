#ifndef PP_GRAPH_H
#define PP_GRAPH_H

#include <stdlib.h>
#include <vector>
#include <MACRO.h>
#include <math.h>



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

    PP_point* p1;
    PP_point* p2;

    //here can add a physical property: attraction forces, repulsion, transmitance... depending on two points (interaction)
    double distp1p2;
};

class PP_graph //set of points and edges
{
public:
    PP_graph();//do nothing, points would be added afterward
    PP_graph( const PP_graph& other );
    PP_graph( PP_graph& other );

    //void addPoint(PP_point & p); would be P.push_back(p)
    void bindClosestNeighbors(double R);
    double euclideanDistance(PP_point* p1, PP_point* p2);

    //set of points (contains all edges)
    std::vector<PP_point> P;
};

#endif // PP_GRAPH_H
