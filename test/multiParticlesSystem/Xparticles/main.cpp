#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

#include <PP_COORD.h>
#include <PP_particle.h>
#include <PP_particle_set.h>



#define PI 3.14159265359L


int main()
{
    //first particle
    PP_COORD p1(0.0,0.0,0.0);
    PP_COORD v1(0.05,-0.05*sqrt(3.0),0.0);
    double R1=0.005, m1=1.0, e1=0.0;
    PP_particle P1(p1,v1,R1,m1,e1);
    std::cout << "initial position and speed of particle 1" << std::endl;
    std::cout << "\t";p1.show();
    std::cout << "\t";v1.show();

    //second particle
    PP_COORD p2(1.0,0.0,0.0);
    PP_COORD v2(0.05,0.05*sqrt(3.0),0.0);
    double R2=0.005, m2=1.0, e2=0.0;
    PP_particle P2(p2,v2,R2,m2,e2);
    std::cout << "initial position and speed of particle 2" << std::endl;
    std::cout << "\t";p2.show();
    std::cout << "\t";v2.show();

    //third particle
    PP_COORD p3(0.5,0.5*sqrt(3.0),0.0);
    PP_COORD v3(-0.1,0.0,0.0);
    double R3=0.005, m3=1.0, e3=0.0;
    PP_particle P3(p3,v3,R3,m3,e3);
    std::cout << "initial position and speed of particle 3" << std::endl;
    std::cout << "\t";p3.show();
    std::cout << "\t";v3.show();

    //create a set of paricles with P1, P2 and P3
    std::vector<PP_particle> _S;
    _S.push_back(P1);
    _S.push_back(P2);
    _S.push_back(P3);
    PP_particle_set S(_S);
    //std::cout << "initial forces applied on eachother: " << std::endl;
    //std::cout << "\t1->2: ";S.interactionForce(0,1).show();
    //std::cout << "\t2->1: ";S.interactionForce(1,0).show();

    //save the positions of the system
    std::ofstream myfile;
    myfile.open ("sys3points", std::ios::out);
    if(myfile.is_open())
    {
        myfile << p1.x << "\t" << p1.y << "\t" << p1.z << "\t" << p2.x << "\t" << p2.y << "\t" << p2.z << "\t" << p3.x << "\t" << p3.y << "\t" << p3.z << std::endl;

        //make the system evolve
        int i1=0, i2=1, i3=2;
        double dt=0.001;
        //all time resolution should be the same, so, all particles should have the same time resolution
        S.S.at(i1).dt=dt; S.S.at(i2).dt=dt; S.S.at(i3).dt=dt;
        int N=20000;
        for(int i=0 ; i<N ; i++)
        {
            //compute the forces applied in the system
            PP_COORD F21=S.interactionForce(i2,i1);//force de la particule 2 sur la particule 1
            PP_COORD F12=S.interactionForce(i1,i2);//force de la particule 1 sur la particule 2

            PP_COORD F32=S.interactionForce(i3,i2);//force de la particule 3 sur la particule 2
            PP_COORD F23=S.interactionForce(i2,i3);//force de la particule 2 sur la particule 3

            PP_COORD F13=S.interactionForce(i1,i3);//force de la particule 1 sur la particule 3
            PP_COORD F31=S.interactionForce(i3,i1);//force de la particule 3 sur la particule 1

            //update the positions of the system
            S.S.at(i1).coord+=S.S.at(i1).v*dt;
            S.S.at(i2).coord+=S.S.at(i2).v*dt;
            S.S.at(i3).coord+=S.S.at(i3).v*dt;
            //write the coordinates of the two particles in an output file
            myfile << S.S.at(i1).coord.x << "\t" << S.S.at(i1).coord.y << "\t" << S.S.at(i1).coord.z << "\t" << S.S.at(i2).coord.x << "\t" << S.S.at(i2).coord.y << "\t" << S.S.at(i2).coord.z << "\t" << S.S.at(i3).coord.x << "\t" << S.S.at(i3).coord.y << "\t" << S.S.at(i3).coord.z << std::endl;

            //update the speed of the system
            S.S.at(i1).v+=(F21*(dt/S.S.at(i1).m) + F31*(dt/S.S.at(i1).m));
            S.S.at(i2).v+=(F12*(dt/S.S.at(i2).m) + F32*(dt/S.S.at(i2).m));
            S.S.at(i3).v+=(F13*(dt/S.S.at(i3).m) + F23*(dt/S.S.at(i3).m));
        }

        myfile.close();
    }
    else
    {
        std::cout << "could not run the experiment because of the file stream." << std::endl;
    }
    std::cout<< std::endl;
    std::cout << "If you are an octave user, you can run the following command to visualize the results:" << std::endl;
    std::cout<< std::endl;
    std::cout << "\tload sys3points; plot(sys3points(:,1),sys3points(:,2)); hold on; plot(sys3points(:,4),sys3points(:,5),'r'); plot(sys3points(:,7),sys3points(:,8),'g'); hold off" << std::endl;
    std::cout<< std::endl;
    return 0;
}
