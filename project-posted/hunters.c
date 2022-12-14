#include "defs.h"

void move() {
    /**
     * randomly select a room from the connected rooms to the current room of the ghost
     * change current room to that room
     */
}

void* hunterAction(void* arg) {
    HunterType* hunter = ((HunterType*) arg);
    int choice;

    printf("%s started in %s", hunter->name, hunter->curr_room->name);
    // while(hunter->bored_timer > 0 && hunter->fear_integer < MAX_FEAR && )
}

int ghostFound(HunterType* hunter) {
    // int to_share = FALSE;
}