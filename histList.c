#include "histList.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertAtEnd(Node** headRef, int data) {
    Node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    Node* current = *headRef;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

void freeList(Node** headRef) {
    Node* current = *headRef;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    *headRef = NULL;
}

/*TEST for histList.c*/
/*
int main() {
    Node* head = NULL;

    // Insert nodes into the list
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 40);
    insertAtEnd(&head, 50);

    // Print the list
    printf("Linked List: \n");
    printList(head);

    // Free the list
    freeList(&head);
    printf("Linked List: \n");
    printList(head);

    return 0;
}
*/  
