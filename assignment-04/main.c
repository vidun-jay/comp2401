#include "defs.h"

int main() {
  BuildingType* bt = (BuildingType*) malloc(sizeof(BuildingType)); // Declare a local BuildingType variable
  initBuilding(bt); // Initialize the local BuildingType variable
  loadBuildingData(bt); // Load the building data into the local building structure
  int choice = -1;

  /* Repeatedly print out the main menu by calling the provided printMenu()
  function, and process each user selection as described below, until the user chooses
  to exit. Verify that the user enters a valid menu option. If they enter an invalid
  option, they must be prompted for a new selection. */
  while (choice != 0) {
    printMenu(&choice);

    switch (choice) {
      case 0:
        exit(0);
        break;
      case 1:
        printRooms(&(bt->rooms));
        break;
      case 2:
        printGhosts(&(bt->ghosts), C_FALSE);
        break;
      case 3:
        printByLikelihood(&(bt->ghosts), C_FALSE);
        break;

      default:
        break;
      }
  }
  cleanupBuilding(bt);
  return(0);
}

void printMenu(int *choice) {
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print rooms\n");
  printf("  (2) Print ghosts\n");
  printf("  (3) Print ghosts by likelihood\n");
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