#ifndef PP_PLAYER_H
#define PP_PLAYER_H

#include <stdlib.h>
#include "PP_particle.h"

#define ABS(x) ((x<0.0)?(-x):(x))
#define SQR(x) ((x)*(x))

/* rules
 * 1) players must stay in the allowed area, otherwise they are eliminated (if only one stays, this is the winner)
 * 2) the weight of the player determines how difficult it is to make them move
 *    m=0.5 mean no resistance incuduced by another player,
 *    m=1.5 means it is impossible to make it move... almost ;-)
 *    in any cases, they undergo the force due to the field
 * 3) the hit box defined by the radius determines how far you can reach someone and it evolves with time (you get the radius of the player you kick out of the box)
 * 4) the attitude, the number e (charge), determinines how the player can hit another player e=0.5: a strong repulsion, e=-0.5 a strong attraction, e=0.0 you cannot hit!
 * 5) the players play sequentially, but randomly drawn (for now) and may choose one oponent at a time (if the oponent dos not ly in the hit box, nothing happen)
 * 6) the players may keep track of the frequence others hit them, and may team up (for later)
 */

class PP_player : public PP_particle
{
public:
    PP_player();
    PP_player(int _ID);
    PP_player(PP_player &p);
    PP_player(PP_player const &p);

    // the players tend to slowly go out of the allowed area but when then are close enough to the center
    virtual PP_COORD force();

    //what a player can do
    bool isPlaying(void);
    void playerStatus(void);
    void absorbPower(PP_player &p); //if the target has been defeated, you may absord its power
    void stealID(PP_player &p); //you may play identity theft
    void become(PP_player &p);  //you may copy the characteristics of another player (but the ID)
    double hitStrength(void); //how strong a player can hit
    void gotHit(double f, PP_COORD direction); //how the player get hit

    //operators
    bool operator ==(PP_player &p); //check if players are the same


    //player identification system
    void acquireTarget(int N/**size of the player set*/); //TODO: improve this function so that the target is acquired according to some criteria
    int getID(void);
    int getTargetID(void);

private:
    int targetID;
    int ID;
    double randomCoordinate(void);
    PP_COORD &randomPosition(void);
    bool onTheBoard;
};

#endif // PP_PLAYER_H
