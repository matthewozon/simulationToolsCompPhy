#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

//#include <PP_COORD.h>
//#include <PP_particle.h>
//#include <PP_particle_set.h>

#include "PP_game.h"

#define PI 3.14159265359L


int main()
{
    srand(time(NULL));
    PP_game myPlayers(50);

    //display the status of every player
    //for(int i=0 ; i<myPlayers.size() ; i++)
    //    myPlayers[i].playerStatus();

    while(myPlayers.continuePlaying())
    {
        //play a turn
        myPlayers.playTurn();
    }

    //show the winner
    std::cout << "The player " << myPlayers.getCurrentPlayer() << " wins in " << myPlayers.getNbTurn() << " turns! Congratulations!!!" << std::endl;
    std::cout << "The last target was: " << myPlayers[myPlayers.getCurrentPlayer()].getTargetID() << "! Sorry for this players." << std::endl;
    myPlayers[myPlayers.getCurrentPlayer()].playerStatus();

    std::cout << std::endl;
    //display the status of every player
    //for(int i=0 ; i<myPlayers.size() ; i++)
    //    myPlayers[i].playerStatus();
    return 0;
}
