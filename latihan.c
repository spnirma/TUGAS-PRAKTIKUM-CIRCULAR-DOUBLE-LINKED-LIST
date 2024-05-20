#include <stdio.h>
#include <stdlib.h>

struct alamat {
    int data;
    struct alamat *prev;
    struct alamat *next;
};

struct alamat* createNode(int data) {
    struct alamat *newNode = (struct alamat*)malloc(sizeof(struct alamat));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertNode(struct alamat **head, int data) {
    struct alamat *newNode = createNode(data);
    if (!*head) {
        newNode->next = newNode;
        newNode->prev = newNode;
        *head = newNode;
    } else {
        struct alamat *tail = (*head)->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

void displayList(struct alamat *head) {
    if (!head) return;
    struct alamat *temp = head;
    do {
        printf("Address: %p, Data: %d\n", (void*)temp, temp->data);
        temp = temp->next;
    } while (temp != head);
}

void swapNodes(struct alamat **head, struct alamat *node1, struct alamat *node2) {
    if (node1 == node2) return;

    struct alamat *prev1 = node1->prev;
    struct alamat *next1 = node1->next;
    struct alamat *prev2 = node2->prev;
    struct alamat *next2 = node2->next;

    if (node1->next == node2) {
        node1->next = next2;
        node1->prev = node2;
        node2->next = node1;
        node2->prev = prev1;
        if (next2) next2->prev = node1;
        if (prev1) prev1->next = node2;

    } else if (node2->next == node1) {
        node2->next = next1;
        node2->prev = node1;
        node1->next = node2;
        node1->prev = prev2;
        if (next1) next1->prev = node2;
        if (prev2) prev2->next = node1;

    } else {
        if (prev1) prev1->next = node2;
        if (next1) next1->prev = node2;
        if (prev2) prev2->next = node1;
        if (next2) next2->prev = node1;

        node1->next = next2;
        node1->prev = prev2;
        node2->next = next1;
        node2->prev = prev1;
    }

    if (*head == node1) *head = node2;
    else if (*head == node2) *head = node1;
}

void sortList(struct alamat **head) {
    if (!*head || (*head)->next == *head) return;

    struct alamat *i = *head;
    struct alamat *j = NULL;
    int swapped;

    do {
        swapped = 0;
        j = i->next;
        while (j != *head) {
            if (i->data > j->data) {
                swapNodes(head, i, j);
                swapped = 1;
            }
            j = j->next;
        }
        i = i->next;
    } while (swapped);
}

int main() {
    int N, data;
    struct alamat *head = NULL;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &data);
        insertNode(&head, data);
    }

    displayList(head);

    printf("\n");
    
    sortList(&head);

    displayList(head);

    struct alamat *current = head;
    struct alamat *nextNode;

    do {
        nextNode = current->next;
        free(current);
        current = nextNode;
    } while (current != head);

    return 0;
}
