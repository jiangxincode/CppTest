#include "elevator.h"

void init(info *elev)
{
        elev->current = 1;
        elev->door = 0; //closed
        elev->state = 0; //stop
}
