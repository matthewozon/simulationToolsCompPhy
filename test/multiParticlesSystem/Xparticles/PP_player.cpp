#include "PP_player.h"

PP_player::PP_player():PP_particle()
{
    //generate a random player in the allowed area, a null speed
    coord=randomPosition();
    //weight \in[0.5,1.5]
    m=1.0+randomCoordinate();
    //and an attitude more or less positive...
    e=randomCoordinate();
    R=0.2+0.2*randomCoordinate();
    onTheBoard=true;
}

PP_COORD PP_player::force()
{
    PP_COORD F;
    F.x=this->coord.x;
    F.y=this->coord.y;
    F.z=this->coord.z;
    return (F.norm()<0.001)?0.0:F/F.norm();
}

bool PP_player::isPlaying()
{
    if(onTheBoard)
    {
        if((ABS(x)>0.5) || (ABS(y)>0.5))
        {
            onTheBoard=false;
        }
    }
    return onTheBoard;
}

double PP_player::randomCoordinate()
{
    return (((double) rand())/((double) RAND_MAX))-0.5;
}

PP_COORD &PP_player::randomPosition()
{
    return *(new PP_COORD(randomCoordinate(),randomCoordinate(),0.0));
}
