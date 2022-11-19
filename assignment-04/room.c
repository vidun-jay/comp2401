#include "defs.h"

/**
 * Initializes the fields of the given RoomArrayType
 * @param arr: RoomArrayType to initialize
 * @return initializes array
 */
void initRoomArray(RoomArrayType *arr) {
    for (int i = 0; i < MAX_ARR; i++) {
        arr->elements[i] = NULL;
    }
    arr->size = 0;
}

/**
 * Initializes a room room
 * @param id: room id
 * @param name: room name
 * @param room: room to initialize
 * @return initialized room
 */
void initRoom(int id, char *name, RoomType **room) {
    RoomType* new_room = (RoomType*) malloc(sizeof(RoomType));

    /* dynamically allocate a new GhostListType structure to store
    the new room’s ghost list */
    GhostListType* new_gt = (GhostListType *) malloc(sizeof(GhostListType));

    // initialize the new structure’s fields to the given parameters
    new_room->id = id;
    strcpy(&new_room->name, name);

    // initialize the new ghost linked list as empty
    initGhostList(new_gt);
    new_room->ghosts = new_gt;

    (*room) = new_room;
}

/**
 * Adds the room r to the back of the array structure
 * @param arr: room array to add room to
 * @param r: room to add to list
 */
void addRoom(RoomArrayType *arr, RoomType *r) {
    arr->elements[arr->size] = r;
    arr->size++;
}

/**
 * Deallocates the dynamically allocated memory in given room collection
 * @param arr: room to deallocate memory for
 */
void cleanupRoomArray(RoomArrayType *arr) {
    for (int i = 0; i < arr->size; i++) {
        cleanupGhostList(arr->elements[i]->ghosts);
        free(arr->elements[i]->ghosts);
        free(arr->elements[i]);
    }
}

/**
 * Prints the fields of each room structure to the screen
 * @param arr: room array whose elements to print
 */
void printRooms(RoomArrayType *arr) {
    for (int i = 0; i < arr->size; i++) {
        printf("ID: %d\nROOM NAME: %s\nGHOST LIST:", arr->elements[i]->id, arr->elements[i]->name);
        printByLikelihood(arr->elements[i]->ghosts, C_FALSE);
        printf("\n");
    }
}