#include "defs.h"

/**
 * Initializes both fields of the given list parameter to default values
 * @param list: list to initialize
 * @return initialized list
 */
void initGhostList(GhostListType *list) {
    list = (GhostListType*) malloc(sizeof(GhostListType));
    list->head = NULL;
    list->tail = NULL;
}

/**
 * Dynamically allocates memory for a GhostType structure, initializes
 * its fields to the given parameters, and “returns” this new structure
 * using the ghost parameter
 * @param id: ghost id
 * @param gt: GhostEnumType (POLTERGEIST, WRAITH, PHANTOM, BULLIES, OTHER)
 * @param r: room
 * @param like: likelihood
 * @return new, initialized GhostType structure
 */
void initGhost(int id, GhostEnumType gt, RoomType *r, float like, GhostType **ghost) {
    // dynamically allocate memory for a GhostType structure
    *ghost = malloc(sizeof(GhostType));

    // initialize its fields to the given parameters
    (*ghost)->id = id;
    (*ghost)->ghostType = gt;
    (*ghost)->room = r;
    (*ghost)->likelihood = like;
}

/**
 * Adds the ghost directly at the back (i.e. the end) of the given list
 * @param list: list to add ghost to
 * @param ghost: ghost to add to list
 * @return updated GhostList
 */
void addGhost(GhostListType *list, GhostType *ghost) {
    NodeType* curr = list->head;
    NodeType* prev = NULL;
    NodeType* new = NULL;

    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
    }

    // allocate memory for new node
    new = (NodeType*) malloc(sizeof(NodeType));
    new->data = ghost;

    // if its empty set it to the head
    if (prev == NULL)
        list->head = new;
    // if its not empty adding to the end of the list
    else
        prev->next = new;

    new->next = curr;
    list->tail = new;
}

/**
 * Adds the ghost to the given list, directly in its correct place,
 * in descending order by likelihood.
 * @param list: list to add to
 * @param ghost: ghost to add to list
 * @return updated GhostListType list
 */
void addGhostByLikelihood(GhostListType *list, GhostType *ghost) {
    NodeType* curr = list->head;
    NodeType* prev = NULL;
    NodeType* new = NULL;

    while (curr != NULL && (curr->data->likelihood > ghost->likelihood)) {
        prev = curr;
        curr = curr->next;
    }

    new = (NodeType*) malloc(sizeof(NodeType));
    new->data = ghost;

    // list is empty (new is first element)
    if (prev == NULL)
        list->head = new;
    // if new is supposed to be in the middle of list
    else
        prev->next = new;
    // if new is supposed to be at the end of the list
    if (curr == NULL)
        list->tail = new;
        // addGhost(list, ghost);

    new->next = curr;
}

/**
 * Deallocates lists' data
 * @param list: list to deallocate data of
 */
void cleanupGhostData(GhostListType *list) {
    NodeType* curr = list->head;

    while (curr != NULL) {
        free(curr->data);
        curr = curr->next;
    }
}

/**
 * Deallocates lists' Nodes
 * @param list: list to deallocate Nodes of
 */
void cleanupGhostList(GhostListType *list) {
    NodeType* curr = list->head;
    NodeType* next = NULL;

    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

/**
 * Prints every field of the given ghost to the screen
 * @param ghost: ghost whose fields to print
 */
void printGhost(GhostType *ghost) {
    char ghostType_str[MAX_STR];
    char room_str[MAX_STR];

    // determine which ghost type to print to screen
    switch (ghost->ghostType) {
    case POLTERGEIST:
        strcpy(&ghostType_str, "POLTERGEIST");
        break;
    case WRAITH:
        strcpy(&ghostType_str, "WRAITH");
        break;
    case PHANTOM:
        strcpy(&ghostType_str, "PHANTOM");
        break;
    case BULLIES:
        strcpy(&ghostType_str, "BULLIES");
        break;
    case OTHER:
        strcpy(&ghostType_str, "OTHER");
        break;
    default:
        strcpy(&ghostType_str, "UNKNOWN");
        break;
    }

    // if there is no room specified, print "unknown" as the room name
    if (ghost->room == NULL)
        strcpy(&room_str, "UNKNOWN");
    // if a room is specified, print the room name as the room name
    else
        strcpy(&room_str, ghost->room->name);

    // print every element to screen
    printf("| %6d | %-14s | %-14s | %-12f |\n",
    ghost->id,
    ghostType_str,
    room_str,
    ghost->likelihood
    );
}

/**
 * Prints every ghost in the given list to the screen
 * @param list: list to print
 * @param ends: whether or not to print head and tail
 */
void printGhosts(GhostListType *list, int ends) {
    NodeType* curr = list->head;

    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    printf("\n|   ID   |   GHOST TYPE   |      ROOM      |  LIKELIHOOD  |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    while (curr != NULL) {
        printGhost(curr->data);
        curr = curr->next;
    }
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    /* the ends parameter is set to C_TRUE, then print the two ghosts at
    the head and tail of the list a second time */
    if (ends == C_TRUE) {
        printGhost(list->head->data);
        printGhost(list->tail->data);
    }
}

/**
 * Prints every ghost in the given list to the screen in decreasing
 * order by likelihood.
 * @param origList: original list
 * @param ends: whether or not to print head and tail
 */
void printByLikelihood(GhostListType *origList, int ends) {
    // declare a temporary list as a local variable, and initialize it as empty
    GhostListType* temp = (GhostListType*) calloc(1, sizeof(GhostListType));
    initGhostList(temp);
    NodeType* curr = origList->head;

    /* traverse the given list origList, and add each of its data elements to the
    temporary list, in descending order by ghost likelihood */
    while (curr != NULL) {
        addGhostByLikelihood(temp, curr->data);
        curr = curr->next;
    }

    // print the temp list in order of likelihood (descending)
    printGhosts(temp, ends);

    /* clean up the memory for the temporary list, without deallocating the
    data because the same data is still used in the original list */
    cleanupGhostList(temp);
}