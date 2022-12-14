#include "defs.h"

/**
 * Move ghost from one room to a connected room
 * @param ghost: ghost to move
 */
void move(GhostType* ghost) {
    // randomly select a room from the connected rooms
    RoomType* new_room = generateRandomRoom(ghost->current_room->connected_rooms);

    // update the current room to that room
    ghost->current_room = new_room;
}

/**
 * Puts a random piece of evidence in a room
 * @param room: room to put the evidence in
 */
void putEvidence(RoomType* room) {
    // generate a random piece of evidence
    EvidenceType* evidence = generateRandomEvidence(room);

    // put that random evidence in the given room
    addEvidence(evidence, room);
}