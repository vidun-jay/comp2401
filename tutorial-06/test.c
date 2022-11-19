void addStudent(StudentList* stuList, StudentNode *stuNode) {
    StudentNode* current = stuList->head;
    stuNode->next = current;
    stuList->head = stuNode;
}

void appendStudent(StudentList* stuList, StudentNode* a){
    StudentNode* current = stuList->head;
    StudentNode* prev = NULL;
    printf("Append the Student\n");
    if(current == NULL){ //first node
        stuList->head = a;
        a->next = NULL;
    }
    else{
        while(current != NULL){
            prev = current;
            current = current->next;
        }
        prev->next = a;
        a->next = NULL;
    }
}

void printList(const StudentList *stuList) {
    StudentNode* current = stuList->head;
    StudentNode* prev = NULL;
    while (current != NULL){
        prev = current;
        current = current->next;
        printf("First Name: %s\nLast Name: %s\nAge:%d\nStudent Number: %s\nGPA: %f\n\n", prev->data->basicInfo.first,prev->data->basicInfo.last,prev->data->basicInfo.age, prev->data->stuNumber, prev->data->gpa);
    }

}