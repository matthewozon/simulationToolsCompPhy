#include "PP_game.h"

PP_game::PP_game()
{
    //
}

PP_game::PP_game(int N)
{
    //generate a set of N players
    for(int n=0 ; n<N ; n++)
        players.push_back(PP_player(n));
    //set the current player
    ID=getPlayerID();
    T=0;
}

PP_game::PP_game(PP_game &pS)
{
    //copy the players
    for(int n=0 ; n<pS.size() ; n++)
        players.push_back(pS[n]);
    //player playing
    ID=pS.getCurrentPlayer();
    T=0;
}

PP_game::PP_game(const PP_game &pS)
{
    //copy the players
    for(int n=0 ; n<((PP_game &) pS).size() ; n++)
        players.push_back(((PP_game &) pS)[n]);
    //player playing
    ID=((PP_game &) pS).getCurrentPlayer();
    T=0;
}


PP_player &PP_game::operator [](int k)
{
    return players[k];
}

int PP_game::size()
{
    return players.size();
}

int PP_game::getPlayerID()
{
    ID=rand() % size();
    while (!players[ID].isPlaying())
    {
       ID=rand() % size();
    }
    return  ID;
}

int PP_game::getCurrentPlayer()
{
    return ID;
}

void PP_game::playTurn()
{
    //update number of turns
    T++;
    //std::cout << "playing turn: " << T << std::endl;

    //draw the current player
    ID=getPlayerID();
    //std::cout << "player turn: " << ID << std::endl;

    //for the current player, acquire the target
    players[ID].acquireTarget(size());
    targetID=players[ID].getTargetID();

    //std::cout << "player target: " << targetID << std::endl;

    //just because it is easier to read
    thePlayer=&players[ID];
    theTarget=&players[targetID];

    //if the target is still playing
    if(theTarget->isPlaying())
    {
        //if the target is reachable by the player
        PP_COORD dist(theTarget->coord-thePlayer->coord);
        if(dist.norm()<thePlayer->R)
        {
            //choose an action hit, steal or become
            double tmp=drawUniform01();
            if(tmp<0.001)
            {
                //you may be a thief
                thePlayer->stealID(*theTarget);
            }
            else if((tmp<0.01) && (tmp>=0.001))
            {
                //become someone else
                thePlayer->become(*theTarget);
            }
            else
            {
                //you may hit your target
                //strength of the kick (may be positive or negative or even null...)
                theTarget->gotHit(thePlayer->hitStrength(),dist);
            }
        }
    }

    //update the status of teh target
    if(!theTarget->isPlaying())
    {
        playersOut.push_back(targetID);
    }
    return;
}

bool PP_game::continuePlaying()
{
    //std::cout << "continuePlaying" << std::endl;
    int tmp=0;
    for(int i=0 ; i<size() ; i++)
    {
        if(players[i].isPlaying()) tmp++;
    }
    return tmp!=1;
    return (playersLeft()!=1);
}

int PP_game::getNbTurn()
{
    return T;
}

int PP_game::playersLeft()
{
    std::cout << "counting players left: " << size()-playersOut.size() << std::endl;
    return size()-playersOut.size();
}

double PP_game::drawUniform01()
{
    return ((double) rand())/((double) RAND_MAX);
}
