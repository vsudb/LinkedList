//https://pythontutor.com/visualize.html#mode=display
//Визуализация работы LinkedList в Stack и Heap
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct Node {
    int value;         // 4
    struct Node* next; // 8
} Node;

typedef struct LinkedList {
    int size;   // 4
    Node* head; // 8
    Node* tail; // 8
} LinkedList;

//==============Prototypes===============

bool isEmpty(LinkedList* list);

Node* createNode(int val);

LinkedList* initList();

LinkedList* createList(int arr[], int size);

void add(LinkedList* list, int value); //append push_back вставка элемента в конец списка 

void freeList(LinkedList* list);

LinkedList* insertAt(LinkedList* list, int index, int value);


void addFront(LinkedList* list, int value);


bool isEmpty(LinkedList* list) {
    return list == NULL || list->size == 0;
}

Node* createNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->next = NULL; //*(node).next;
    node->value = val;

    return node;
}

LinkedList* initList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

LinkedList* createList(int arr[], int size) {
    LinkedList* list = initList();

    for (int i = 0; i < size; i++) {
        add(list, arr[i]);
    }
    return list;
}


void add(LinkedList* list, int value) { //push_back
    Node* node = createNode(value);

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


void freeList(LinkedList* list) {
    Node* cur = list->head;

    while (cur != NULL) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }

    free(list);
}


void addFront(LinkedList* list, int value) {
    Node* node = createNode(value);

    node->next = list->head;
    list->head = node;
    list->size++;
}

LinkedList* insertAt(LinkedList* list, int index, int value) {

    printf("insertAt index = [%d] \n", index);

    if (isEmpty(list) || index < 0 || index > list->size) {
        printf("Index = [%d] Out Of Bound Exception\n", index);
        return list;
    }

    if (index == 0) {
        addFront(list, value);
    }
    else if (index == list->size) {
        add(list, value);
    }
    else {
        Node* node = createNode(value);
        Node* cur = list->head;

        for (int i = 0; i < index - 1; i++) {
            cur = cur->next;
        }

        node->next = cur->next;
        cur->next = node;

        list->size++;
    }
    return list;
}

int main()
{
    int arr[] = { 0,1,2,3,4,5,6,7,8,9 };

    LinkedList* list = createList(arr, sizeof(arr) / sizeof(int));

    insertAt(list, 4, 444);

    freeList(list);

}