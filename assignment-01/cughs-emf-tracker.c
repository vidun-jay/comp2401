/**
 * Author: Vidun Jayakody [101224988]
 * Purpose: Sort EMF data from rooms in a building
 * Usage:
 * - Run program (./cughs-emf-tracker)
 * - Enter 8-digit room UUID, followed by a space then EMF value (i.e. “32850021 4.2214”)
 * - When done inputting rooms, enter "-1" followed by any number or letter at the prompt to sort data
 * Changelog:
 * - Fixed stack smashing bug
 */

#include <stdio.h>

#define MAX_SIZE  32

#define C_OK             0	// Success flag
#define C_ERR_ARR_FULL  -1	// Error code for array is full
#define C_ERR_BAD_EMF   -2	// Error code for an invalid EMF value
#define C_ERR_BAD_UUID  -3	// Error code for an invalid UUID value
#define C_ERR_BAD_ARR   -4	// Error code for an array error

int  getEmfData(int*, float*);
void printEmfData(int*, float*, int);
int  orderEmfData(int*, float*, int);

int  validateUUID(int);
int  validateEMF(float);
void printErrorMsg(int);        // Hint: Write modular code using helper functions for repeated functionality
int  findMaxIndex(float*, int);


int main() {
  float emf_data[MAX_SIZE];
  int uuid_data[MAX_SIZE];

  int num = getEmfData(uuid_data, emf_data);

  // print error message using helper function
  if (num < 0) {
    printErrorMsg(num);
    return C_OK;
  }

  // print original array
  printf("\nOriginal array:");
  printEmfData(uuid_data, emf_data, num);

  // order it from greatest to least by EMF
  orderEmfData(uuid_data, emf_data, num);

  // print sorted array
  printf("\nSorted array:");
  printEmfData(uuid_data, emf_data, num);
}


/**
 * Checks if EMF value is between 0.0 - 5.0 inclusively
 * @param emf : float value to check
 * @return    : C_OK if EMF value is valid
 *              C_ERR_BAD_EMF if EMF invalid
 */
int validateEMF(float emf) {
  if (emf >= 0.0 && emf <= 5.0)
    return C_OK;
  else
    return C_ERR_BAD_EMF;
}


/**
 * Checks if UUID is between 32850000 - 32859999 inclusively
 * @param uuid : uuid value to check
 * @return     : C_OK if UUID value is valid
 *               C_ERR_BAD_UUID if UUID is invalid
 */
int validateUUID(int uuid) {
  if (uuid >= 32850000 && uuid <= 32859999)
    return C_OK;
  else
    return C_ERR_BAD_UUID;
}


/**
 * Prompt user for UUID and EMF pair until -1 is inputted and store in respective arrays
 * @param uuid : array of integer UUID values
 * @param emf  : array of floating point EMF values
 * @return     : number of data pairs entered by the user
 *               C_ERR_ARR_FULL if maximum size of array is reached
 */
int getEmfData(int *uuid, float *emf) {
  int size = 0;
  int current_uuid;
  float current_emf;

  while (1) {

    // prompt the user to enter in data pair and store the UUID in current_uuid variable
    printf("Enter an 8-digit room UUID, followed by a space then EMF value (i.e. “32850021 4.2214”): ");
    scanf("%d %f", &current_uuid, &current_emf);

    // if the UUID or EMF is -1, leave the loop
    if (current_uuid == -1 || current_emf == -1)
      break;

    if (size < MAX_SIZE) {
      // validate the UUID
      if (validateUUID(current_uuid) == C_OK)
        uuid[size] = current_uuid;
        // uuid[MAX_SIZE - (MAX_SIZE - size)] = current_uuid;
      else
        return C_ERR_BAD_UUID;

      // validate the EMF
      if (validateEMF(current_emf) == C_OK)
        emf[size] = current_emf;
        // emf[MAX_SIZE - (MAX_SIZE - size)] = current_emf;
      else
        return C_ERR_BAD_EMF;

      // increment the size counter of the array
      ++size;
    } else {
      return C_ERR_ARR_FULL;
    }
  }
  return size;
}


/**
 * Formats and prints the UUID and EMF values, and the number of pairs entered
 * @param uuid : uuid values array
 * @param emf  : emf values array
 * @param int  : number of pairs entered
 */
void printEmfData(int *uuid, float *emf, int num) {
  printf("\n");

  printf("------------------\n");
  printf("|   UUID   | EMF |\n");
  printf("------------------\n");
  for (int i = 0; i < num; ++i)
    printf("| %-8d | %-2.1f |\n", uuid[i], emf[i]);
  printf("------------------\n");

  printf("Total entries: %d\n", num);
}


/**
 * Finds the index of the highest value in a given array
 * @param arr : floating point array of values to search
 * @param num : number of valid elements in array
 * @return    : the index of the highest value of arr
 */
int findMaxIndex(float *arr, int num) {

  if (num != 0) {
    float max = arr[0]; // start with the first element in the array
    int index = 0;

    // go through array; if current element is bigger than current max, set new max
    for (int i = 1; i < num; ++i) {
      if (arr[i] > max) {
        max = arr[i];
        index = i;
      }
    }
    return index;
  } else
      return C_ERR_BAD_ARR;
}


/**
 * Order an array by EMF values in descending order
 * @param uuid : array of UUID values to sort
 * @param emf  : array of emf values to sort
 * @param num  : size of arrays
 * @return     : C_OK if sorting completes successfully
 *               C_ERR_BAD_ARR if array is empty
 */
int orderEmfData(int *uuid, float *emf, int num) {

  // if array isn't empty
  if (num > 0) {
    // create and populate deep copies of uuid and emf arrays
    int new_uuid[num];
    float new_emf[num];

    for (int i = 0; i < num; ++i) {
      new_uuid[i] = uuid[i];
      new_emf[i] = emf[i];
    }

    /*
     * find current highest EMF, update the in/out array so that
     * the highest value is at the current index i, then replace
     * index at copied array with -1 so it isn't considered again
     * in the next iteration
     */
    for (int i = 0; i < num; ++i) {
      int max_index = findMaxIndex(new_emf, num);
      uuid[i] = new_uuid[max_index];
      emf[i] = new_emf[max_index];
      new_uuid[max_index] = -1;
      new_emf[max_index] = -1;
    }

    return C_OK;
  } else
      return C_ERR_BAD_ARR;
}


/**
 * Print the appropriate error message to the screen
 * @param error_code : integer exit code value
 */
void printErrorMsg(int error_code) {
  switch (error_code) {
  case C_ERR_ARR_FULL:
    printf("\nError: C_ERR_ARR_FULL\n");
    break;
  case C_ERR_BAD_EMF:
    printf("\nError: C_ERR_BAD_EMF\n");
    break;
  case C_ERR_BAD_UUID:
    printf("\nError: C_ERR_BAD_UUID\n");
  case C_ERR_BAD_ARR:
    printf("\nError: C_ERR_BAD_ARR\n");
  default:
    break;
  }
}