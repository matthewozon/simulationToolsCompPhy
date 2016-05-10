//it is convenient to manipulates sets of particles instead of each individual particle.
//here, you can define some particle-particle interactions

#ifndef PP_PARTICLE_SET_H
#define PP_PARTICLE_SET_H

#include "PP_particle.h"
#include <vector>
#include<cmath>


class PP_particle_set
{
public:
    //ctor
    PP_particle_set(); //generates an empty set
    PP_particle_set(int N); //generates a set of N defaulft particles
    PP_particle_set(int N, double _R, double _m, double _e); //generates a set of N similar particules all concentrated at the origin
    PP_particle_set(std::vector<PP_COORD> COORD, std::vector<PP_COORD> _V, std::vector<double> _R, std::vector<double> _m, std::vector<double> _e);
    PP_particle_set(std::vector<PP_COORD> COORD, std::vector<double> _R, std::vector<double> _m, std::vector<double> _e);
    PP_particle_set(std::vector<PP_particle> _S);
    PP_particle_set(PP_particle_set &pS);
    PP_particle_set(PP_particle_set const &pS);

    //operator =
    PP_particle_set operator= (PP_particle_set & c);
    PP_particle_set operator= (PP_particle_set const& c);

    //dtor?
    ~PP_particle_set(){S.clear();}

    //a vector containing all the particles of the set
    std::vector<PP_particle> S;
    //may add the neighborhood of each particle?

    //probability of agglomeration if two individuals meet
    double alpha;
    double aggregationProbability(double v /*norm of the speed at the beginning of the collision*/);

    //pair distant interaction
    PP_COORD interactionForce(int idxP1, int idxP2);
};

#endif // PP_PARTICLE_SET_H
