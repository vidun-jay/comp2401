#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define C_TRUE     1
#define C_FALSE    0

#define MAX_ARR  128
#define MAX_STR   32

#define NEXT_ROOM_ID    9001
#define NEXT_GHOST_ID  810310

typedef enum { POLTERGEIST, WRAITH, PHANTOM, BULLIES, OTHER } GhostEnumType;

typedef struct {
  int id;
  char name[MAX_STR];
  struct GhostList *ghosts;
} RoomType;

typedef struct {
  int id;
  GhostEnumType ghostType;
  RoomType *room;
  float likelihood;
} GhostType;

/* A static array containing many rooms. The RoomArrayType contains
an elements field, which must be declared as a statically allocated array
of RoomType pointers. You will set the maximum capacity to an existing,
predefined constant, and the structure must contain a size field to track
the current number of rooms in the elements array. */
typedef struct {
/*** Define the RoomArrayType here ***/
  RoomType* elements[MAX_ARR];
  int size;
} RoomArrayType;

/*** Define the NodeType here ***/
typedef struct Node {
  GhostType* data;
  struct Node* next;
} NodeType;

/*** Complete the GhostListType here ***/
typedef struct GhostList {
  NodeType* head; // head
  NodeType* tail; // tail
} GhostListType;

/* This is a kind of “Overall Data” collection, which represents a
building in our data, and holds all of the data at a higher level for
us to reference. It contains two statically allocated fields: A linked
list of ghosts, stored as a GhostListType, and a static array of rooms,
stored as an instance of the RoomArrayType. */
typedef struct Building {
  /*** Define the BuildingType here ***/
  GhostListType ghosts;
  RoomArrayType rooms;
} BuildingType;

void printMenu(int*);

void initGhostList(GhostListType*);
void initGhost(int, GhostEnumType, RoomType*, float, GhostType**);
void addGhost(GhostListType*, GhostType*);
void addGhostByLikelihood(GhostListType*, GhostType*);
void cleanupGhostData(GhostListType*);
void cleanupGhostList(GhostListType*);
void printGhost(GhostType*);
void printGhosts(GhostListType*, int);
void printByLikelihood(GhostListType*, int);

void initRoomArray(RoomArrayType*);
void initRoom(int, char*, RoomType**);
void addRoom(RoomArrayType*, RoomType*);
void cleanupRoomArray(RoomArrayType*);
void printRoom(RoomType*);
void printRooms(RoomArrayType*);

void loadBuildingData(BuildingType*);
void initBuilding(BuildingType*);
void cleanupBuilding(BuildingType*);