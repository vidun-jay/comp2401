#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "t06defs.h"

/* Implement StudentNode type */
typedef struct StudentNode {
  StudentType* data;
  struct StudentNode* next;
} StudentNode;


typedef struct {
  StudentNode *head;
} StudentList;


/* Implement the following functions */
void addStudent(StudentList *, StudentNode *);
void printList(const StudentList *);



int main(void) {
  int i;

  StudentType matilda, joe, timmy;
  StudentNode matildaNode, joeNode, timmyNode;

  initStudent("Matilda", "Mallister", 22, "123444555",
              9.0, &matilda);
  initStudent("Joe", "The Plumber", 24, "567888999",
              8.7, &joe);
  initStudent("Timmy", "Tortoise", 99, "345667788",
              11.5, &timmy);

  matildaNode.data = &matilda;
  joeNode.data = &joe;
  timmyNode.data = &timmy;

  StudentList comp2401;

  comp2401.head = NULL;

/*  Uncomment the following lines once addStudent is implemented  */

 addStudent(&comp2401, &matildaNode);
 addStudent(&comp2401, &joeNode);
 addStudent(&comp2401, &timmyNode);

/*  Uncomment the following line once printList is implemented  */

 printList(&comp2401);

  return 0;
}

/*   Function:  addStudent                                  */
/*         in:  Location of StudentList to be modified      */
/*         in:  Location of StudentType to be added         */
/*        out:  StudentList with added StudentType          */
/*    Purpose:  adds stu to stuList at the head of the list */
void addStudent(StudentList *stuList, StudentNode *stuNode) {
    StudentNode* curr = stuList->head;
    stuNode->next = curr;
    stuList->head = stuNode;
}

/**
 * Prints list of students' info
 * @param stuList: student list to print
 */
void printList(const StudentList *stuList) {
    StudentNode* curr = stuList->head;
    StudentNode* prev = NULL;

    while (curr != NULL){
        prev = curr;
        curr = curr->next;

        printf("First Name: %s\nLast Name: %s\nAge: %d\nStudent Number: %s\nGPA: %f\n\n",
        prev->data->basicInfo.first,
        prev->data->basicInfo.last,
        prev->data->basicInfo.age,
        prev->data->stuNumber,
        prev->data->gpa);
    }
}

void appendStudent(StudentList* stuList, StudentNode* a) {
    StudentNode* curr = stuList->head;
    StudentNode* prev = NULL;

    if(curr == NULL) {
        stuList->head = a;
        a->next = NULL;
    } else {
        while(curr != NULL) {
            prev = curr;
            curr = curr->next;
        }

        prev->next = a;
        a->next = NULL;
    }
}