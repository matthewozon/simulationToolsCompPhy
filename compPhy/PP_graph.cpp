#include <PP_graph.h>

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
            if(D<=R)
            {
                PP_edge tmp(&(P.at(i)),  &(P.at(j)));
                P.at(i).e.push_back(tmp);
                P.at(j).e.push_back(tmp);
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
