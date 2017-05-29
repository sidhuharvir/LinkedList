//
//  @file LinkedListAPI.c
//  @author Harvir Sidhu
//  @date May 29 2017
//  @brief File containing the implementation of a doubly linked listed
//
//

#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second)) {
    List *listPtr = (List *)malloc(sizeof(List));
    
    listPtr->head = NULL;
    listPtr->printData = printFunction;
    listPtr->deleteData = deleteFunction;
    listPtr->compare = compareFunction;
    
    return listPtr;
}

Node *initializeNode(void *data) {
    Node * nodePtr = malloc(sizeof(Node));
    
    nodePtr->data = data;
    nodePtr->next = NULL;
    nodePtr->previous = NULL;
    
    return nodePtr;
}

void insertFront(List *list, void *toBeAdded) {
    if(list == NULL) {
        return;
    }
    
    if (list->head == NULL) {
        Node * newNode = malloc(sizeof(Node));
        newNode->data = toBeAdded;
        list->head = newNode;
        return;
    }
    
    Node * newNode = malloc(sizeof(Node));
    newNode->data = toBeAdded;
    newNode->next = list->head;
    list->head->previous = newNode;
    list->head = newNode;
}

void insertBack(List *list, void *toBeAdded) {
    
    if (list == NULL) {
        return;
    }
    
    if (list->head == NULL) {
        Node * newNode = malloc(sizeof(Node));
        newNode->data = toBeAdded;
        list->head = newNode;
        return;
    }
    
    Node * temp = malloc(sizeof(Node));
    temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    Node * newNode = malloc(sizeof(Node));
    newNode->data = toBeAdded;
    temp->next = newNode;
    newNode->previous = temp;
}

void deleteList(List *list) {
    if (list == NULL) {
        return;
    }
    
    while(list->head != NULL) {
        Node *temp = list->head;
        list->head = temp->next;
        
        temp->next = NULL;
        temp->previous = NULL;
        free(temp->data);
        free(temp);
    }
}

void insertSorted(List *list, void *toBeAdded) {
    if(list == NULL || toBeAdded == NULL) {
        return;
    }
    
    Node * newNode = malloc(sizeof(Node));
    newNode->data = toBeAdded;
    
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    
    Node * temp = malloc(sizeof(Node));
    temp = list->head;
    Node *temp1 = malloc(sizeof(Node));
    
    while(temp->next != NULL) {
        if (list->compare(temp->data, newNode->data) == 0 || list->compare(temp->data, newNode->data) < 0) {
            temp1 = temp->next;
            temp->next = newNode;
            newNode->next = temp1;
        }
        else if (list->compare(temp->data, newNode->data) > 0) {
            temp1 = temp->previous;
            temp->previous = newNode;
            newNode->previous = temp1;
        }
    }
}

int deleteDataFromList(List *list, void *toBeDeleted) {
    if (list == NULL || toBeDeleted == NULL) {
        return 0;
    }
    
    Node * temp = malloc(sizeof(Node));
    temp = list->head;
    while(temp != NULL) {
        if (temp->data == toBeDeleted) {
            
            if (temp == list->head) {
                list->head = temp->next;
                if (list->head != NULL) {
                    temp->previous = NULL;
                }
            }
            else if (temp == list->tail) {
                if (temp->previous) {
                    temp->previous->next = NULL;
                }
            }
            else {
                temp->previous->next = temp->next;
                temp->next->previous = temp->previous;
            }
        }
        free(temp->data);
        free(temp);
        return 0;
    }
    return -1;
}

void *getFromFront(List *list) {
    if (list == NULL) {
        return  NULL;
    }
    return list->head;
}

void *getFromBack(List *list) {
    if (list == NULL) {
        return NULL;
    }
    
    Node * prev = malloc(sizeof(Node));
    prev = list->head;
    Node * curr = malloc(sizeof(Node));
    curr = list->head->next;
    
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
    }
    return prev;
}

void printForward(List *list) {
    if (list == NULL) {
        return;
    }
    Node * temp = malloc(sizeof(Node));
    temp = list->head;
    while(temp != NULL) {
        list->printData(temp->data);
        temp = temp->next;
    }
}

void printBackwards(List *list) {
    if (list != NULL) {
        return;
    }
    Node * temp = malloc(sizeof(Node));
    temp = list->tail;
    while(temp != list->head) {
        list->printData(temp->data);
        temp = temp->previous;
    }
}
