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
    //a pointer on the targeted player
    targetID=-1;
    //set ID
    ID=-RAND_MAX;
}
PP_player::PP_player(int _ID):PP_particle()
{
    //generate a random player in the allowed area, a null speed
    coord=randomPosition();
    //weight \in[0.5,1.5]
    m=1.0+randomCoordinate();
    //and an attitude more or less positive...
    e=randomCoordinate();
    R=0.2+0.2*randomCoordinate();
    onTheBoard=true;
    //a pointer on the targeted player
    targetID=-1;
    //set ID
    ID=_ID;
}

PP_player::PP_player(PP_player &p):PP_particle(p)
{
    onTheBoard=p.isPlaying();
    ID=p.getID();
    targetID=p.getTargetID();
}

PP_player::PP_player(const PP_player &p):PP_particle(p)
{
    onTheBoard=((PP_player &) p).isPlaying();
    ID=((PP_player &) p).getID();
    targetID=((PP_player &) p).getTargetID();
}

PP_COORD PP_player::force()
{
    //for now, let not add constraints
    PP_COORD F;
    F.x=0.0*coord.x;
    F.y=0.0*coord.y;
    F.z=0.0*coord.z;
    if(F.norm()<0.001)
    {
        F*=0.0;
    }
    else
    {
        F/=F.norm();
    }
    return F;
}

bool PP_player::isPlaying()
{
    if(onTheBoard)
    {
        if((ABS(coord.x)>0.5) || (ABS(coord.y)>0.5))
        {
            onTheBoard=false;
        }
    }
    return onTheBoard;
}

void PP_player::playerStatus()
{
    if(isPlaying())
    {
        std::cout << "I am still on the board." << std::endl;
        std::cout << "My loaction is: (" << coord.x << "," << coord.y << ")" << std::endl;
        std::cout << "weight: " << m << ", attitude: " << e << ", hit box radius: " << R << std::endl;
    }
    else
    {
        std::cout << "I am out of the board, I am no longer playing." << std::endl;
        std::cout << "My loaction is: (" << coord.x << "," << coord.y << ")" << std::endl;
    }
}

void PP_player::absorbPower(PP_player &p)
{
    if(targetID==p.getID())
    {
        //I can increase my hitbox
        if(p.R>R) R=p.R;
        //and gain a little weight
        if(p.m>m) m=(m+0.1*p.m)/1.1;
    }
    else
    {
        //does it mean your cheating? You should be punished for that
        if(randomCoordinate()>0.0)
        {
            //bad luck, you get your hit box radius devided by 10 and your weight by 2
        }
        else
        {
            std::cout << "you lucky bastard, you didn't get caught this time!" << std::endl;
        }
    }
}

void PP_player::stealID(PP_player &p)
{
    ID=p.getID();
    return;
}

void PP_player::become(PP_player &p)
{
    //copy characteristics (location, weight, attitude and hitbox)
    R=p.R;
    coord.x=p.coord.x; coord.y=p.coord.y;
    m=p.m;
    e=p.e;
    return;
}

double PP_player::hitStrength()
{
    return (0.5+randomCoordinate())*e;
}

void PP_player::gotHit(double f, PP_COORD direction)
{
    //modulation factor depending on the weight if m=1.5, eta\in[0.0,1.0], if m=0.5, eta=1.0
    double eta = 1.0-(m-0.5)*(randomCoordinate()+0.5);
    //actual strength
    eta*=f;
    //compute the unite direction
    PP_COORD u;
    if(direction.norm()<0.000000000001)
    {
        u.x=randomCoordinate();
        u.y=sqrt(1.0-SQR(u.x));
    }
    else
    {
        u=(direction/direction.norm());
    }
    coord+=(u*eta);
    return;
}


bool PP_player::operator ==(PP_player &p)
{
    return ID==p.getID();
}

void PP_player::acquireTarget(int N)
{
    targetID= rand() % N;
    if(targetID==ID) targetID= rand() % N; //well, you really want to kill yourself... go ahead!
    return;
}

int PP_player::getID(void)
{
    return ID;
}

int PP_player::getTargetID()
{
    return targetID;
}

double PP_player::randomCoordinate()
{
    return (((double) rand())/((double) RAND_MAX))-0.5;
}

PP_COORD &PP_player::randomPosition()
{
    return *(new PP_COORD(randomCoordinate(),randomCoordinate(),0.0));
}
