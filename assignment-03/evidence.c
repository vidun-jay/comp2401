#include "defs.h"

/**
 * Performs a deep copy of the evidence found in the oldEv parameter into the evidence structure in the newEv parameter
 * @param newEV: the EvidenceType to copy TO
 * @param oldEV: the EvidenceType to copy FROM
 */
void copyEvidence(EvidenceType* newEv, EvidenceType* oldEv) {
    /* deep copy the evidence found in the oldEv parameter into the evidence
    structure in the newEv parameter */
    initEvidence(oldEv->id, oldEv->room, oldEv->device, oldEv->value, oldEv->timestamp, newEv);
}

/**
 * Doubles the capacity of the evidence collection
 * @param arr: pointer of notebook to double in capacity
 */
void growNotebook(NotebookType* arr) {
    // temporarily store a new collection
    NotebookType newNoteBook;

    /* initialize the newNotebook collection with an existing function,
    using double the capacity of the given collection in parameter arr */
    initNotebook(&newNoteBook, arr->capacity * 2);

    /* loop over the given collection in arr, and make a deep copy of every piece
    of evidence from the old elements array in arr into the new elements array in
    newNotebook */
    for (int i = 0; i < arr->size; i++) {
        copyEvidence(&(newNoteBook.elements[i]), &(arr->elements[i]));
    }

    // deallocate arr’s old elements array
    free(arr->elements);

    /* set arr’s elements pointer to newNotebook’s elements array,
    which points to a new, increased array in the heap */
    arr->elements = newNoteBook.elements;
    arr->capacity *= 2;
}

/**
 * Makes a copy of the given evidence directly into its correct
 * position in the given Notebook collection
 * @param arr: NotebookType to add to
 * @param ev: EvidenceType to add
 */
void addEvidence(NotebookType* arr, EvidenceType* ev) {

    int index = -1;
    int comparison;

    // if not enough space, grow array
    if (arr->size == arr->capacity) {
        growNotebook(arr);
    }

    // find index
    for (int i = 0; i < arr->size; i++) {
        comparison = strcmp(ev->room, arr->elements[i].room);

        // if letter is same, check timestamps
        if (comparison == 0) {
            if (arr->elements[i].timestamp > ev->timestamp) {
                index = i;
                break;
            }
        } else if (comparison > 0) {
            index = i;
            break;
        }
    }

    if (index == -1)
        copyEvidence(&(arr->elements[arr->size]), ev);
    else {
        // move everything after index down by 1 to make space for new ev
        for (int i = arr->size-1; i >= index; i--) {
            // move down by 1 by copying
            copyEvidence(&(arr->elements[i+1]), &(arr->elements[i]));
        }

        // if reach end of array, then add bottom OR if arr is empty, add to bottom
        copyEvidence(&(arr->elements[index]), ev);
    }

    arr->size++; // increase size to reflect new addition
}

/**
 * Removes from the given collection the evidence with the given id
 * @param arr: NoteBook to remove from
 * @param id: id of EvidenceType to remove
 */
int delEvidence(NotebookType* arr, int id) {
    int index;
    int found = FALSE;

    // loop through NotebookType and try to find id
    for (int i = arr->size; i >= index; i--) {
        if (arr->elements[i].id == id) {
            found = TRUE; // if id found, set success flag
            index = i;
        }
    }

    if (found) {
        // loop every EvidenceType in NotebookType
        for (int i = index; i < arr->size; i++) {
            arr->elements[i] = arr->elements[i+1];
        }
        arr->size--; // decrease size to reflect new addition
        return C_OK; // success flag
    } else
        return C_NOK;
}

/**
 * Prints all of the evidence in the given collection
 * @param arr: NoteBook to print
 */
void printNotebook(NotebookType* arr) {
    printf("%-7s%-20s%-10s%-17s%-9s\n", "ID", "ROOM", "DEVICE", "VALUE", "TIMESTAMP");
    for (int i = 0; i <= 63; i++) printf("#");
    printf("\n");
    for (int i = 0; i < arr->size; i++) {
        printHelper(&(arr->elements[i]));
    }
}

/**
* Deallocates the dynamically allocated memory in the given collection
* @param arr: NoteBook to deallocate
*/
void cleanupNotebook(NotebookType* arr) {
    free(arr->elements);
}

/**
* Helper function to format EvidenceTypes
* @param ev: EvidenceType to process
*/
void printHelper(EvidenceType* ev) {
    char* thermal_reading;
    int sound_reading;

    int hours, minutes, seconds;
    seconds = ev->timestamp % 60;
    minutes = (ev->timestamp % 3600) / 60;
    hours = ev->timestamp / 3600;

    /* Any EMF device data should have at most 1 number after the decimal
    An EMF reading above 4.0 should have “(HIGH)” written beside it */
    if (strcmp(ev->device, "EMF") == 0) {
        if (ev->value > 4)
            printf("%-7d%-20s%-10s%-1.1f (HIGH)       %02d:%02d:%02d\n", ev->id, ev->room, ev->device, ev->value, hours, minutes, seconds);
        else
            printf("%-7d%-20s%-10s%-17.1f%02d:%02d:%02d\n", ev->id, ev->room, ev->device, ev->value, hours, minutes, seconds);
    }

    /* Any THERMAL device data should have at most 2 numbers after the decimal
    A THERMAL reading below 0.0 should have “(COLD)” written beside it */
    if (strcmp(ev->device, "THERMAL") == 0)  {
        if (ev->value < 0)
            printf("%-7d%-20s%-10s%-1.2f (COLD)     %02d:%02d:%02d\n", ev->id, ev->room, ev->device, ev->value, hours, minutes, seconds);
        else
            printf("%-7d%-20s%-10s%-17.1f%02d:%02d:%02d\n", ev->id, ev->room, ev->device, ev->value, hours, minutes, seconds);
    }

    /* Any SOUND device data should have at most 1 number after the decimal
    A SOUND reading below 35.0 should have “(WHISPER)” written beside it
    A SOUND reading above 70.0 should have “(SCREAM)” written beside it */
    if (strcmp(ev->device, "SOUND") == 0) {
        if (ev->value < 35)
            printf("%-7d%-20s%-10s%-1.2f (WHISPER)  %02d:%02d:%02d\n", ev->id, ev->room, ev->device, ev->value, hours, minutes, seconds);
        else if (ev->value > 70)
            printf("%-7d%-20s%-10s%-1.2f (SCREAM)   %02d:%02d:%02d\n", ev->id, ev->room, ev->device, ev->value, hours, minutes, seconds);
        else
            printf("%-7d%-20s%-10s%-17.1f%02d:%02d:%02d\n", ev->id, ev->room, ev->device, ev->value, hours, minutes, seconds);
    }
}