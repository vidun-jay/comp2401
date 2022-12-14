#include "defs.h"

int main(int argc, char *argv[]) {
    // Initialize a random seed for the random number generators
    srand(time(NULL));
    int fear_counter = 0;
    int bored_counter = 0;
    // create threads
    pthread_t hunter1, hunter2, hunter3, hunter4, ghost;

    // You may change this code; this is for demonstration purposes
    BuildingType building;
    initBuilding(&building);
    populateRooms(&building);

    initHunters(&building);
    initBuilding(&building);

    // Note: there is no hunterAction function but if there was this is what I'd do
    pthread_create(&ghost, NULL, hunterAction, building.all_hunters.hunters[0]);
    pthread_create(&ghost, NULL, hunterAction, building.all_hunters.hunters[1]);
    pthread_create(&ghost, NULL, hunterAction, building.all_hunters.hunters[2]);
    pthread_create(&ghost, NULL, hunterAction, building.all_hunters.hunters[3]);

    pthread_join(hunter1, NULL);
    pthread_join(hunter2, NULL);
    pthread_join(hunter3, NULL);
    pthread_join(hunter4, NULL);
    pthread_join(ghost, NULL);

    for (int i = 0; i < 4; i++) {
        if (building.all_hunters.hunters[i]->fear_integer >= MAX_FEAR) {
            fear_counter++;
            printf("%s got too scared. Left building.", building.all_hunters.hunters[i]->name);
        } else if (building.all_hunters.hunters[i]->bored_timer <= 0){
            bored_counter++;
            printf("%s is bored. Left the building", building.all_hunters.hunters[i]->name);
        } else {
            printf("%s gained enough evidence. Left the building", building.all_hunters.hunters[i]->name);
        }
    }

    freeBuilding(&buildling);
    return 0;
}


/*
  Function:  randInt
  Purpose:   returns a pseudo randomly generated number,
             in the range min to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [min, max-1)
*/
int randInt(int min, int max)
{
    return rand() % (max - min) + min;
}

/*
  Function:  randFloat
  Purpose:   returns a pseudo randomly generated number,
             in the range min to max, inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1)
*/
float randFloat(float a, float b) {
    // Get a percentage between rand() and the maximum
    float random = ((float) rand()) / (float) RAND_MAX;
    // Scale it to the range we want, and shift it
    return random * (b - a) + a;
}