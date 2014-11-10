#include <iostream>
#include <stdio.h>
#include <sstream>

#include <PP_graph.h>

#define PI 3.14159265359L


int main()
{
    //test point
    PP_point p1, p2, p3, p4;
    p2.x = 1.0;
    p3.x = 2.0;
    p4.x = 3.0;


    //test graph
    PP_graph myGraph;
    myGraph.P.push_back(p1);
    myGraph.P.push_back(p2);
    myGraph.P.push_back(p3);
    myGraph.P.push_back(p4);

    myGraph.bindClosestNeighbors(1.5);
    myGraph.show();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    myGraph.removePoint(1);


    std::cout << std::endl;
    myGraph.show();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    //p1.show();
    myGraph(0).show();
    myGraph(1).show();
    myGraph(1).e.at(0).p1.show();
    myGraph(1).e.at(0).p2.show();

    myGraph.removePoint(1);
    std::cout << std::endl;
    myGraph.show();

    return 0;
}







/*//test point
    PP_point p1, p2, p3, p4;

    p2.x = 1.0;

    p3.x = 2.0;

    p4.x = 3.0;

    PP_point p5(p1);

    PP_point p6 = p4;
    p6.y=0.001;

    p1.show();
    p2.show();
    p3.show();
    p4.show();

    if(p1==p2) std::cout << "p1==p2" << std::endl;
    else std::cout << "p1!=p2" << std::endl;

    if(p1==p5) std::cout << "p1==p5" << std::endl;
    else std::cout << "p1!=p5" << std::endl;

    if(p4==p6) std::cout << "p4==p6" << std::endl;
    else std::cout << "p4!=p6" << std::endl;

    //test graph
    PP_graph myGraph;
    myGraph.P.push_back(p1);
    myGraph.P.push_back(p2);
    myGraph.P.push_back(p3);
    myGraph.P.push_back(p4);
    //myGraph.P.push_back(p5);
    //myGraph.P.push_back(p6);

    myGraph.bindClosestNeighbors(1.5);
    myGraph.show();

    //try
    //{
    myGraph(2).e.at(0).p1->show();
    myGraph(2).e.at(0).p2->show();
        myGraph.removePoint(0);
        //myGraph.removePoint(0);
        //myGraph.removePoint(2);

    //}
    //catch(std::out_of_range &q)
    //{
    //    std::cout << g << std::endl;
    //}
        //return 1;

    std::cout << std::endl;
    myGraph.show();
    //p1.show();
    myGraph(0).show();
    myGraph(1).show();
    myGraph(1).e.at(0).p1->show();
    myGraph(1).e.at(0).p2->show();

    myGraph.removePoint(0);
    std::cout << std::endl;
    myGraph.show();

    return 0;*/
