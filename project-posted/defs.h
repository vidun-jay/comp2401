#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_STR            64
#define FEAR_RATE           1
#define MAX_FEAR          100
#define MAX_HUNTERS         4
#define USLEEP_TIME     50000
#define BOREDOM_MAX        99

#define TRUE               -1
#define FALSE              -2
#define C_OK               -3
#define C_NOK              -4

// You may rename these types if you wish
typedef enum { EMF, TEMPERATURE, FINGERPRINTS, SOUND } EvidenceClassType;
typedef enum { POLTERGEIST, BANSHEE, BULLIES, PHANTOM } GhostClassType;

// init.c forward declarations
void initEvidence(EvidenceClassType, float, EvidenceType*);
void initEvidenceList(EvidenceListType*);
void initHunter(char*, EvidenceClassType, HunterType*);
void initHunters(HunterArrayType*);
void initGhost(GhostType*, RoomType*);

// room.c forward declarations
RoomNodeType* generateRandomRoom(RoomListType*);

// RoomType: Room struct
typedef struct {
    char name[MAX_STR];
    RoomListType* connected_rooms;
    struct EvidenceList* evidence_list;
    GhostType* ghost;
    struct HunterArray* hunters;
    int size;
    sem_t mutex;
} RoomType;

// Room Node: a node in the rooms LinkedList
typedef struct RoomNode {
    RoomType* data;
    struct RoomNode* next;
} RoomNodeType;

// RoomListType: linked list of rooms
typedef struct {
    RoomNodeType* head;
    RoomNodeType* tail;
    int size;
} RoomListType;

// EvidenceType
typedef struct {
    EvidenceClassType evidence_type;
    float reading;
    int ghostly;
    // the following variables keep track of the number of each type there are
    int emf_count, temp_count, finger_count, sound_count;
} EvidenceType;

// EvidenceNodeType: a node in the evidence LinkedList
typedef struct EvidenceNode {
    EvidenceType* data;
    struct EvidenceNode* next;
} EvidenceNodeType;

// EvidenceListType: evidence LinkedList
typedef struct EvidenceList {
    EvidenceNodeType* head;
    EvidenceNodeType* tail;
} EvidenceListType;

// GhostType: Ghost struct
typedef struct {
    GhostClassType type;
    RoomType* current_room;
    int boredom_timer;
    EvidenceClassType evidence_types[3];
} GhostType;

// HunterType: HunterType
typedef struct Hunter {
    RoomType* curr_room;
    char name[MAX_STR];
    EvidenceClassType evidence_type;
    EvidenceListType* evidence;
    int fear_integer;
    int bored_timer;
    // whether or not hunter has more than 3 ghostly evidence
    int ghostly[4];
} HunterType;

// Array of Hunter structs
typedef struct HunterArray {
    HunterType* hunters[MAX_HUNTERS];
    int size;
} HunterArrayType;

// BuildingType
typedef struct {
    GhostType ghost;
    RoomListType* rooms;
    HunterArrayType all_hunters;
} BuildingType;

int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters

void populateRooms(BuildingType*);   // Populates the building with sample data for rooms