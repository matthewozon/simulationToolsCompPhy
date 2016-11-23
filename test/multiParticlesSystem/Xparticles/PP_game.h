#ifndef PP_GAME_H
#define PP_GAME_H

#include <vector>
#include "PP_player.h"

class PP_game //TODO: change name for PP_game
{
public:
    PP_game();
    PP_game(int N);

    PP_game(PP_game &pS);
    PP_game(PP_game const &pS);

    PP_player &operator [](int k);
    int size(void);

    //select a player
    int getPlayerID(void); //draw the current player
    int getCurrentPlayer(void); //read the current player ID

    //apply interaction
    void playTurn(void);

    //check is there is at least one player left
    bool continuePlaying(void);

    //get the number of turn to get a winner
    int getNbTurn(void);

private:
    std::vector<PP_player> players;
    std::vector<int> playersOut;
    int ID;
    int targetID;
    int playersLeft(void); //count the number of player left
    int T; //count the number of turns that have been played
    double drawUniform01(void);
    PP_player *thePlayer;
    PP_player *theTarget;
};

#endif // PP_GAME_H
