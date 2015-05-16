#include <glib.h>

#ifndef ELEVATOR_H
#define ELEVATOR_H

struct INFO
{
        gint current;

        GQueue dest_up;
        GQueue dest_down;

        GQueue guest_up;
        GQueue guest_down;

        gint state;
        gboolean door;
};

typedef struct INFO info;

void init(info *elev);
#endif // ELEVATOR_H

