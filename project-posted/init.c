#include "defs.h"

/**
 * Initializes every field of the given EvidenceType structure, using the given parameters
 * @param evidence_type: type of evidence
 * @param reading: measurement of the evidence
 * @param evidence: evidence object to set values for
 * @return initialized EvidenceType, evidence
 */
void initEvidence(EvidenceClassType evidence_type, float reading, EvidenceType* evidence) {
    evidence->evidence_type = evidence_type;
    evidence->reading = reading;
}

/**
 * Initializes evidence list to null
 * @param evidence_list: evidence list to initialize
 * @return initialized evidence list
 */
void initEvidenceList(EvidenceListType* evidence_list) {
    evidence_list->head = NULL;
    evidence_list->tail = NULL;
}

/**
 * Initializes hunter array
 * @param name: hunter name
 * @param evidence_type: type of equiment
 * @param hunter: hunter to initialize
 * @return initialized hunter
 */
void initHunter(char name[], EvidenceClassType evidence_type, HunterType* hunter) {
    hunter->curr_room = NULL;
    strcpy(hunter->name, name);
    hunter->evidence_type = evidence_type;

    hunter->evidence = calloc(1, sizeof(EvidenceListType));
    initEvidenceList(hunter->evidence);

    hunter->fear_integer = 0;
    hunter->bored_timer = BOREDOM_MAX;

    hunter->ghostly[0] = FALSE;
    hunter->ghostly[1] = FALSE;
    hunter->ghostly[2] = FALSE;
    hunter->ghostly[3] = FALSE;
}

/**
 * Initializes an array of hunters
 * @param hunter_arr: hunter array to initialize
 * @return an initialized hunter array
 */
void initHunters(BuildingType* building) {
    // allocate memory for 4 hunters
    HunterType* hunter1 = calloc(1, sizeof(HunterArrayType));
    HunterType* hunter2 = calloc(1, sizeof(HunterArrayType));
    HunterType* hunter3 = calloc(1, sizeof(HunterArrayType));
    HunterType* hunter4 = calloc(1, sizeof(HunterArrayType));
    char name1[MAX_STR], name2[MAX_STR], name3[MAX_STR], name4[MAX_STR];
    RoomType* van = building->rooms->head->data; // start at van

    // prompt the user for hunter names
    printf("Enter the name of the first hunter: ");
    scanf("%s", &name1);
    printf("Enter the name of the second hunter: ");
    scanf("%s", &name2);
    printf("Enter the name of the third hunter: ");
    scanf("%s", &name3);
    printf("Enter the name of the fourth hunter: ");
    scanf("%s", &name4);

    // initialize the hunters using the names
    initHunter(name1, POLTERGEIST, hunter1);
    initHunter(name2, BANSHEE, hunter2);
    initHunter(name3, BULLIES, hunter3);
    initHunter(name4, PHANTOM, hunter4);

    // add the hunters to the buildings' list of hunters
    building->all_hunters.hunters[0] = hunter1;
    building->all_hunters.hunters[1] = hunter2;
    building->all_hunters.hunters[2] = hunter3;
    building->all_hunters.hunters[3] = hunter4;

    // add the hunters to the van's list of hunters
    van->hunters->hunters[0] = hunter1;
    van->hunters->hunters[1] = hunter2;
    van->hunters->hunters[2] = hunter3;
    van->hunters->hunters[3] = hunter4;

    // set the current room of each hunter to the van
    hunter1->curr_room = van;
    hunter2->curr_room = van;
    hunter3->curr_room = van;
    hunter4->curr_room = van;

    // set the number of hunters in the van to 4
    van->hunters->size = 4;
}

void initGhost(GhostType* ghost, BuildingType* building) {
   // set the ghost class to one of the four classes randomly
   ghost->type = randInt(0, 3);

   switch (ghost->type) {
    case POLTERGEIST:
        ghost->evidence_types[0] = EMF;
        ghost->evidence_types[1] = TEMPERATURE;
        ghost->evidence_types[1] = FINGERPRINTS;
        break;
    case BANSHEE:
        ghost->evidence_types[0] = EMF;
        ghost->evidence_types[1] = TEMPERATURE;
        ghost->evidence_types[1] = SOUND;
    case BULLIES:
        ghost->evidence_types[0] = EMF;
        ghost->evidence_types[1] = FINGERPRINTS;
        ghost->evidence_types[1] = SOUND;
    case PHANTOM:
        ghost->evidence_types[0] = TEMPERATURE;
        ghost->evidence_types[1] = FINGERPRINTS;
        ghost->evidence_types[1] = SOUND;
   default:
    break;
   }

   // spawn the ghost in one of the rooms randomly
   ghost->current_room = generateRandomRoom(building);

   ghost->boredom_timer = BOREDOM_MAX;
}

/**
 * Initialize room list
 * @param room_list: room list to initialize
 * @return initialized room list
 */
void initRoomList(RoomListType* room_list) {
    room_list->size = 0;
    room_list->head = NULL;
    room_list->tail = NULL;
}

/**
 * Initialize room
 * @param room: room to initialie with
 * @param name: name to initialize room with
 * @return initialized room
 */
void initRoom(RoomType* room, char name[]) {
    strcpy(room->name, name);
    room->size = 0;

    room->connected_rooms = calloc(1, sizeof(RoomListType));
    initRoomList(room->connected_rooms);
    room->evidence_list = calloc(1, sizeof(EvidenceListType));
    initEvidenceList(room->evidence_list);

    if (sem_init(&room->mutex, 0, 1) < 0) {
        printf("[INIT]: semaphor error");
        exit(1);
    }
}