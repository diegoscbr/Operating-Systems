#ifndef HISTLIST_H
#define HISTLIST_H

// Node structure for the linked list
typedef struct Node {
    
    int data;
    struct Node* next;
} Node;

// Function prototype to insert a node at the end of the list
void insertAtEnd(Node** headRef, int data);
Node* createNode(int data);
void printList(Node* head);
void freeList(Node** headRef);

#endif /* HISTLIST_H */
