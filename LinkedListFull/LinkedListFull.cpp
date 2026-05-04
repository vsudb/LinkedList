#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ================= NODE =================

typedef struct Node {
    int value;
    struct Node* next;
} Node;

// ================= LIST =================

typedef struct LinkedList {
    int size;
    Node* head;
    Node* tail;
} LinkedList;

// ================= PROTOTYPES =================

bool isEmpty(LinkedList* list);

LinkedList* createList(int arr[], int size);

void add(LinkedList* list, int value);
void addFront(LinkedList* list, int value);

int get(LinkedList* list, int index);
bool set(LinkedList* list, int index, int value);

bool insertAt(LinkedList* list, int index, int value);

bool removeAt(LinkedList* list, int index);
bool removeValue(LinkedList* list, int value);

int find(LinkedList* list, int value);

void printList(LinkedList* list);
void clear(LinkedList* list);
void freeList(LinkedList* list);

// ================= IMPLEMENTATION =================

bool isEmpty(LinkedList* list) {
    return (list == NULL || list->size == 0);
}

// -------- add to end --------
void add(LinkedList* list, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    if (isEmpty(list)) {
        list->head = node;
        list->tail = node;
    }
    else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}

// -------- add to front --------
void addFront(LinkedList* list, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = list->head;

    if (isEmpty(list)) {
        list->tail = node;
    }

    list->head = node;
    list->size++;
}

// -------- create list --------
LinkedList* createList(int arr[], int size) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    for (int i = 0; i < size; i++) {
        add(list, arr[i]);
    }

    return list;
}

// -------- get --------
int get(LinkedList* list, int index) {
    if (list == NULL || index < 0 || index >= list->size)
        return -1;

    Node* cur = list->head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }

    return cur->value;
}

// -------- set --------
bool set(LinkedList* list, int index, int value) {
    if (list == NULL || index < 0 || index >= list->size)
        return false;

    Node* cur = list->head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }

    cur->value = value;
    return true;
}

// -------- insert at --------
bool insertAt(LinkedList* list, int index, int value) {
    if (list == NULL || index < 0 || index > list->size)
        return false;

    if (index == 0) {
        addFront(list, value);
        return true;
    }

    if (index == list->size) {
        add(list, value);
        return true;
    }

    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;

    Node* cur = list->head;
    for (int i = 0; i < index - 1; i++) {
        cur = cur->next;
    }

    node->next = cur->next;
    cur->next = node;

    list->size++;
    return true;
}

// -------- remove at --------
bool removeAt(LinkedList* list, int index) {
    if (list == NULL || isEmpty(list) || index < 0 || index >= list->size)
        return false;

    Node* toDelete;

    if (index == 0) {
        toDelete = list->head;
        list->head = list->head->next;

        if (list->size == 1)
            list->tail = NULL;
    }
    else {
        Node* cur = list->head;

        for (int i = 0; i < index - 1; i++) {
            cur = cur->next;
        }

        toDelete = cur->next;
        cur->next = toDelete->next;

        if (toDelete == list->tail)
            list->tail = cur;
    }

    free(toDelete);
    list->size--;
    return true;
}

// -------- remove by value --------
bool removeValue(LinkedList* list, int value) {
    if (list == NULL || isEmpty(list))
        return false;

    Node* cur = list->head;
    Node* prev = NULL;

    while (cur != NULL) {
        if (cur->value == value) {

            if (prev == NULL) {
                list->head = cur->next;
            }
            else {
                prev->next = cur->next;
            }

            if (cur == list->tail)
                list->tail = prev;

            free(cur);
            list->size--;
            return true;
        }

        prev = cur;
        cur = cur->next;
    }

    return false;
}

// -------- find --------
int find(LinkedList* list, int value) {
    if (list == NULL)
        return -1;

    Node* cur = list->head;
    int index = 0;

    while (cur != NULL) {
        if (cur->value == value)
            return index;

        cur = cur->next;
        index++;
    }

    return -1;
}

// -------- print --------
void printList(LinkedList* list) {
    if (isEmpty(list)) {
        printf("List is empty\n");
        return;
    }

    Node* cur = list->head;

    while (cur != NULL) {
        printf("%d ", cur->value);
        cur = cur->next;
    }

    printf("\n");
}

// -------- clear --------
void clear(LinkedList* list) {
    if (list == NULL) return;

    Node* cur = list->head;

    while (cur != NULL) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// -------- free list --------
void freeList(LinkedList* list) {
    if (list != NULL) {
        clear(list);
        free(list);
    }
}

// ================= MAIN =================

int main() {

    int arr[] = { 1,2,3,4,5,6,7,8,9 };

    LinkedList* list = createList(arr, 9);

    printList(list);

    printf("get(5) = %d\n", get(list, 5));

    addFront(list, 100);
    insertAt(list, 3, 999);

    printList(list);

    removeAt(list, 2);
    removeValue(list, 5);

    printList(list);

    printf("find 999 = %d\n", find(list, 999));

    set(list, 0, 777);

    printList(list);

    freeList(list);

    return 0;
}