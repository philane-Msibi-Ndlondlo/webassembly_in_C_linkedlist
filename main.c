#include <stdlib.h>
#include <stdio.h>

typedef struct Node_T {
    int data;
    struct Node_T* next;
} Node;

typedef struct LinkedList_T {
    struct Node_T* head;
    struct Node_T* curr;
    struct Node_T* prev;
    int size;
} LinkedList;

LinkedList* createLinkedList(void) {

    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
        
    if (list == NULL) {
        printf("Failed to create Linked List. Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    list->head = NULL;
    list->curr = NULL;
    list->prev = NULL;
    list->size = 0;

    return list;
}

void tranverseLinkedList(LinkedList* list) {

    list->curr = NULL;
    list->prev = NULL;

    if (list->head == NULL) {
        printf("Failed to tranverse Linked List.\n");
       exit(EXIT_FAILURE); 
    }
   
    list->curr = list->head;

    while (list->curr->next != NULL) {
        list->prev = list->curr;
        list->curr = list->curr->next;
    }
}



void addNodeToLinkedList(LinkedList* list, int data) {

    if (list == NULL) {
        printf("Failed to add node. List is NULL\n");
        exit(EXIT_FAILURE);
    }

    Node* node = (Node*)malloc(sizeof(Node));

    if (node == NULL) {
        printf("Failed to add node. List is NULL\n");
        exit(EXIT_FAILURE);
    }

    node->data = data;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        tranverseLinkedList(list);
        list->prev = NULL;
        list->curr->next = node;
        list->curr = NULL;
    }

    node = NULL;
    list->size++;
}

void printLinkedList(LinkedList* list) {

    list->curr = NULL;
    list->prev = NULL;

    list->curr = list->head;

    while (list->curr != NULL) {
        printf("Node  %d\n", list->curr->data);
        list->curr = list->curr->next;
    }
}


void removeNodeFromLinkedList(LinkedList* list, int data) {

    if (list == NULL) {
        printf("Failed to remove node. Linked List is NULL");
        exit(EXIT_FAILURE);
    }

    if (list->head == NULL) {
        printf("Failed to remove node. Linked List is Empty.");
        exit(EXIT_FAILURE);
    }

    if (list->head->next == NULL && list->head->data == data) {
        free(list->head);
        list->head = NULL;
        printf("Item removed from LinkedList");
        return;
    }

    list->curr = NULL;
    list->prev = NULL;

    list->curr = list->head;


    while (list->curr->next != NULL && list->curr->data != data) {
        list->prev = list->curr;
        list->curr = list->curr->next;
    }

    if (list->curr->next == NULL) {
        printf("Failed to remove node. Item not found in Linked List.");
        return;
    }

    if (list->head == list->curr) {
        list->prev = list->curr; 
        list->head = list->curr->next;
        free(list->prev);
    } else {
        list->curr = list->curr->next;
        free(list->prev->next);
        list->prev->next = list->curr;
    }

    list->prev = NULL;
    list->curr = NULL;
    
    list->size--;
    printf("Item removed from LinkedList");
}

void memcleanNodes(LinkedList* list) {
    
    if (list != NULL ) {

        list->curr = list->head; 

        while(list->curr->next != NULL) {
            list->prev = list->curr;
            list->curr = list->curr->next;
            free(list->prev);
        }

        free(list->curr);
    }
}

void memcleanLinkedList(LinkedList* list) {
    
    if (list != NULL ) {

        memcleanNodes(list); 
        list->head = NULL;
        list->curr = NULL;
        list->prev = NULL;
        list->size = 0;
        free(list);
    }
}

int main(int argc,const char **argv) {

    LinkedList* list = createLinkedList();

    addNodeToLinkedList(list, 5);
    addNodeToLinkedList(list,10);
    addNodeToLinkedList(list,15);
    addNodeToLinkedList(list, 20);
    addNodeToLinkedList(list, 25);

    printLinkedList(list);

    removeNodeFromLinkedList(list, 5);

    addNodeToLinkedList(list, 50);
    addNodeToLinkedList(list, 5);

    printLinkedList(list);

    memcleanLinkedList(list);

    return 0;
}
