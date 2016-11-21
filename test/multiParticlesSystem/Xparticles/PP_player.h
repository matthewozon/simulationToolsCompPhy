#ifndef PP_PLAYER_H
#define PP_PLAYER_H

#include <stdlib.h>
#include "PP_particle.h"

/* rules
 * 1) players must stay in the allowed area, otherwise they are eliminated (if only one stays, this is the winner)
 * 2) the weight of the player determines how difficult it is to make them move
 *    m=0.5 mean no resistance incuduced by another player,
 *    m=1.5 means it is impossible to make it move
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

    // the players tend to slowly go out of the allowed area but when then are close enough to the center
    virtual PP_COORD force();

    bool isPlaying(void);
private:
    double randomCoordinate(void);
    PP_COORD &randomPosition(void);
    bool onTheBoard;
};

#endif // PP_PLAYER_H
