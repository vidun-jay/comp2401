#include "defs.h"

/**
 * Check if evidence is in evidence list
 * @param evidence_list: evidence list to search
 * @param evidence: evidence to look for
 * @return if it was found or not (C_OK or C_NOK)
 */

int containsEvidence(EvidenceListType* evidence_list, EvidenceType* evidence) {

    EvidenceNodeType* curr = evidence_list->head;

    while (curr != NULL) {
        if (curr->data->reading == evidence->reading)
            return C_OK;
        curr = curr->next;
    } return C_NOK;
}

/**
 * Randomly generates a piece of evidence
 * @param room: current room
 * @return pointer for randomly generated evidence
 */
EvidenceType* generateRandomEvidence(RoomType* room) {
    int has_ghost;
    int ghostly_count = 0;
    float value;
    EvidenceClassType class;
    int random_int = rand() % 3; // generate random integer from 0 to 3

    // allocate memory for an evidence struct
    EvidenceType* evidence = calloc(1, sizeof(EvidenceType));

    // check if the current room has a ghost in it
    if (room->ghost == NULL)
        has_ghost = TRUE;
    else
        has_ghost = FALSE;

    switch (random_int) {
    case 0:
        class = EMF;
        if (has_ghost == TRUE) {
            value = randFloat(4.70, 5);
            evidence->ghostly = TRUE;
            evidence->emf_count += 1;
        }
        else {
            value = randFloat(0.00, 4.90);
            evidence->ghostly = FALSE;
        }
        break;
    case 1:
        class = TEMPERATURE;
        if (has_ghost == TRUE) {
            value = randFloat(-10.00, 1);
            evidence->ghostly = TRUE;
            evidence->temp_count += 1;
        }
        else {
            value = randFloat(0.00, 27);
            evidence->ghostly = FALSE;
        }
        break;
    case 2:
        class = FINGERPRINTS;
        if (has_ghost == TRUE) {
            value = 1.00;
            evidence->ghostly = FALSE;
            evidence->finger_count += 1;
        }
        else {
            value = 0.00;
            evidence->ghostly = TRUE;
        }
        break;
    case 3:
        class = SOUND;
        if (has_ghost == TRUE) {
            value = randFloat(65.00, 75.00);
            evidence->ghostly = TRUE;
            evidence->sound_count += 1;
        }
        else {
            value = randFloat(40.00, 70.00);
            evidence->ghostly = FALSE;
        }
        break;
    default:
        evidence->ghostly = FALSE;
        break;
    }
    initEvidence(class, value, evidence);
    return &evidence;
}

/**
 * Adds evidence to an evidence list
 * @param evidence: evidence to add
 * @param evidence_list: evidence list to add to
 */
void addEvidence(EvidenceType* evidence, EvidenceListType* evidence_list) {
    // allocate memory for new node
    EvidenceNodeType* new_node = calloc(1, sizeof(EvidenceNodeType));
    new_node->data = evidence;
    new_node->next = NULL;

    // if evidence list is empty, just add to back
    if (evidence_list->head == NULL || evidence_list->tail == NULL)
        evidence_list->tail = new_node;
    else
        evidence_list->tail->next;

    evidence_list->tail = new_node;
}

/**
 * Drop a piece of evidence in a random room
 * @param ghost: ghost who is dropping the evidence
 */
void dropEvidence(GhostType* ghost) {
    EvidenceType* evidence;
    EvidenceListType* evidence_list;

    if (sem_wait(&ghost->current_room->mutex) < 0) {
        printf("[WAIT]: semaphor error");
        exit(1);
    }

    // allocate memory for new evidence
    EvidenceType* evidence = calloc(1, sizeof(EvidenceType));
    evidence = generateRandomEvidence(ghost->current_room);

    // add evidence to evidence list
    addEvidence(evidence_list, evidence);

    if (sem_post(&ghost->current_room->mutex) < 0) {
        printf("[POST]: semaphor error");
        exit(1);
    }
}

void shareEvidence(HunterType* hunter1, HunterType* hunter2) {
    /**
     * check if two hunters are in the same room
     * look at the room the hunters in and check the hunters in that room
     * check if that size is greater than 1, which wolud mean theres at least 2 hunters
     * IF true, copy input parameter hunter's evidence list to the other hunter in the hunter list
        * (add a copy of the evidence nodes from one to the other)
     */
    EvidenceNodeType* curr = hunter1->evidence->head;

    while (curr != NULL) {
        // if the data is ghostly and is unique, add to hunter2s list
        if (curr->data->ghostly == TRUE && containsEvidence(hunter2->evidence, curr) == FALSE) {
            addEvidence(hunter2->evidence, curr->data);
        }
        curr = curr->next;
    }
}

/**
 * Add evidence to hunters evidence collection
 * @param hunter: hunter who collects the evidence
 */
void collectEvidence(HunterType* hunter) {
   EvidenceListType* evidence_list = hunter->curr_room->evidence_list;
   EvidenceNodeType* curr = evidence_list->head;
   EvidenceNodeType* prev = NULL;

    // if its empty
   if (evidence_list->head == NULL || evidence_list->tail == NULL)
        // TODO: multi-threading?
        return;

   while (curr != NULL) {
        if (curr->data->evidence_type == hunter->evidence_type) {
            // if its at the head
            if (curr == evidence_list->head) {
                evidence_list->head = curr->next;
                addEvidence(curr->data, evidence_list);
                free(curr);
                curr = evidence_list->head;
            }
            // if its at the tail
            else if (curr == evidence_list->tail) {
                evidence_list->tail = prev;
                evidence_list->tail->next = NULL;
                addEvidence(curr->data, evidence_list);
                free(curr);
                curr = NULL;
            // if its anywhere in the middle
            } else {
                    prev->next = curr->next;
                    addEvidence(curr->data, evidence_list);
                    free(curr);
                    curr = prev->next;
            }
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

/**
 * Free memory for evidence list
 * @param evidence_list: list to free
 */
void cleanEvidenceList(EvidenceListType* evidence_list) {
    EvidenceNodeType* curr = evidence_list->head;
    EvidenceNodeType* next = NULL;

    while (curr != NULL) {
        next = curr->next;
        free(curr->data);
        free(curr);
        curr = next;
    } free (evidence_list);
}