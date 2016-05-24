#include "PP_particle_set.h"

PP_particle_set::PP_particle_set()
{
    alpha=1.0;
}

//generates a set of N defaulft particles
PP_particle_set::PP_particle_set(int N)
{
    alpha=1.0;
    PP_particle p_default;
    for(int i=0 ; i<N ; i++)
        S.push_back(p_default);
}


//generates a set of N similar particules all concentrated at the origin and with no speed
PP_particle_set::PP_particle_set(int N, double _R, double _m, double _e)
{
    alpha=1.0;
    PP_particle p_default;
    p_default.R=_R;
    p_default.m=_m;
    p_default.e=_e;
    for(int i=0 ; i<N ; i++)
        S.push_back(p_default);
}

//generates a set of particles with given characteristics
PP_particle_set::PP_particle_set(std::vector<PP_COORD> COORD, std::vector<PP_COORD> _V, std::vector<double> _R, std::vector<double> _m, std::vector<double> _e)
{
    alpha=1.0;
    if(COORD.size()!=_V.size() || _V.size()==_R.size() || _R.size()!=_m.size() || _m.size()!=_e.size()) throw "error: the dimensions of charateristics do not match";
    int N=COORD.size();
    for(int i=0 ; i<N ; i++)
    {
        PP_particle p(COORD.at(i), _V.at(i), _R.at(i), _m.at(i), _e.at(i));
        S.push_back(p);
    }
}

//generates a set of particles with given characteristics with no initial speed
PP_particle_set::PP_particle_set(std::vector<PP_COORD> COORD, std::vector<double> _R, std::vector<double> _m, std::vector<double> _e)
{
    alpha=1.0;
    if(COORD.size()!=_R.size() || _R.size()!=_m.size() || _m.size()!=_e.size()) throw "error: the dimensions of charateristics do not match";
    int N=COORD.size();
    for(int i=0 ; i<N ; i++)
    {
        PP_particle p(COORD.at(i), _R.at(i), _m.at(i), _e.at(i));
        S.push_back(p);
    }
}

//generates a set of particles from a set of particles
PP_particle_set::PP_particle_set(std::vector<PP_particle> _S)
{
    alpha=1.0;
    int N=_S.size();
    for(int i=0 ; i<N ; i++)
    {
        S.push_back(_S.at(i));
    }
}

//copy a particle set from another
PP_particle_set::PP_particle_set(PP_particle_set &pS)
{
    alpha=1.0;
    int N=pS.S.size();
    for(int i=0 ; i<N ; i++)
    {
        S.push_back(pS.S.at(i));
    }
}

PP_particle_set::PP_particle_set(PP_particle_set const &pS)
{
    alpha=1.0;
    int N=pS.S.size();
    for(int i=0 ; i<N ; i++)
    {
        S.push_back(pS.S.at(i));
    }
}


PP_particle_set PP_particle_set::operator= (PP_particle_set & c)
{
    alpha=c.alpha;
    int N=c.S.size();
    for(int i=0 ; i<N ; i++)
    {
        S.push_back(c.S.at(i));
    }
    return *this;
}

PP_particle_set PP_particle_set::operator= (PP_particle_set const& c)
{
    alpha=c.alpha;
    int N=c.S.size();
    for(int i=0 ; i<N ; i++)
    {
        S.push_back(c.S.at(i));
    }
    return *this;
}

double PP_particle_set::aggregationProbability(double v /*norm of the speed at the beginning of the collision*/)
{
    return (v < 0.0) ? exp(alpha*v) : exp(-alpha*v);
}

PP_COORD PP_particle_set::interactionForce(int idxP1, int idxP2) //action of P1 over P2
{
    if( idxP1<0 || idxP1>=S.size() || idxP2<0 || idxP2>=S.size())
    {
        PP_COORD F;
        F=0.0;
        return F;
    }
    else
    {
        PP_COORD F;
        if((S.at(idxP2).coord-S.at(idxP1).coord).norm()>(S.at(idxP2).R+S.at(idxP1).R) )
        {
            //apply distant forces
            F=(S.at(idxP1).coord-S.at(idxP2).coord)/(S.at(idxP2).coord-S.at(idxP1).coord).normSQR();
        }
        else
        {
            //apply contact force
            //determine the unitary vector between the center of P2 and the center of P1
            PP_COORD u=(S.at(idxP2).coord-S.at(idxP1).coord);
            u/=u.norm();
            //calculate the speed difference
            PP_COORD dv=(S.at(idxP2).v-S.at(idxP1).v);
            //estimate the force
            F=u*(dv.inner(u)*(-2.0*S.at(idxP1).m*S.at(idxP2).m / (S.at(idxP1).dt*(S.at(idxP1).m+S.at(idxP2).m))  ));
        }
        return F;
    }
}
