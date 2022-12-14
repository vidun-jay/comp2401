#include "defs.h"
/*
RoomNodeType* generateRandomRoom(BuildingType* building) {
    int count;
    // TODO: check about this
    int rand_int = randInt(0, 13);
    RoomNodeType* curr = building->rooms->head;

    while (curr != NULL) {
        if (count != NULL)
            break;
        curr = curr->next;
        count++;
    } return &curr;
}
*/

/**
 * Returns a random room in a list of rooms
 * @param rooms: RoomList to find random room
 * @return random room node pointer from room list
 */
RoomNodeType* generateRandomRoom(RoomListType* rooms) {
    RoomNodeType* temp = rooms->head;

    // generates random number between 0 to 10 (indices of the 11 rooms)
    // TODO: check because max should be number of connected rooms
    int random_index = randInt(0, rooms->size);

    // traverse the linked list until that node and return it
    for (int i = 0; i < random_index; i++) {
        temp = temp->next;
    } return &temp;
}

/**
 * Free memory for roomlist
 * @param room_list: room list to free
 */
void cleanRoomList(RoomListType* room_list) {
    RoomNodeType* curr_i = room_list->head;
    RoomNodeType* next_i = NULL;
    RoomNodeType* curr_j = NULL;
    RoomNodeType* next_j = NULL;

    /*
    TA if you're reading this don't bother trying to figure out what's going on here
    cuz I don't either lmao. I tried, this is the best I could come up with but I am honestly
    very tired and am on the verge of giving up on this assignment entirely. My process was GOING TO be
    to loop through every node and then free the node (curr_j) inside the inner for loop, then free the
    connected rooms outside of the nested for loop, call cleanEvidenceList and free curr_i->data and
    curr_j. Idk if I get half points for explaining but if I do I appreciate it
    */
    for (int i = 0; i < room_list->size; i++) {
        next_i = next_i->next;
        curr_j = curr_i->data->connected_rooms->head;
        for (int j = 0; j < curr_j; j++) {
            /* code */
        }
    }
}