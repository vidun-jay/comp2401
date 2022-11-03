#include <stdio.h>
#include <string.h>

#include "defs.h"

int main() {
  // initialize variables
  int choice = -1;
  int type = 0;
  int id;
  char room_name[MAX_STR];
  EvidenceType ev;
  NotebookType new_notebook;
  initNotebook(&new_notebook, 2);
  loadEvidenceData(&new_notebook);

  while (choice != 0) {
    printMenu(&choice);

    switch (choice) {
      // Add evidence
      case 1:
        printf("Enter evidence ID: ");
        scanf("%d", &ev.id);
        getchar(); // clear input buffer
        printf("Enter room name: ");
        fgets(room_name, MAX_STR, stdin);

        room_name[strlen(room_name) - 1] = NULL; // remove newline
        strcpy(ev.room, room_name);

        // ask what type
        while (TRUE) {
          printf("Enter evidence type [1 - EMF, 2 - THERMAL, 3 - SOUND]: ");
          scanf("%d", &type);
            switch (type) {
            case 1:
              strcpy(ev.device, "EMF");
              break;
            case 2:
              strcpy(ev.device, "THERMAL");
              break;
            case 3:
              strcpy(ev.device, "SOUND");
              break;
            default:
              break;
            }
            break;
        }

        printf("Enter value: ");
        scanf("%f", &ev.value);

        printf("Enter timestamp: ");
        scanf("%d", &ev.timestamp);

        addEvidence(&new_notebook, &ev);
        break;

      // Delete Evidence
      case 2:
        printf("Enter the ID of the evidence to delete: ");
        scanf("%d", &id);
        delEvidence(&new_notebook, id);
        break;

      // Print NoteBook
      case 3:
        printNotebook(&new_notebook);
        break;

    default:
      break;
    }
  }
  cleanupNotebook(&new_notebook);
  return(0);
}

void printMenu(int *choice) {
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Add evidence\n");
  printf("  (2) Delete evidence\n");
  printf("  (3) Print evidence\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}