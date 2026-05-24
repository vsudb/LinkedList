#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


// ================= NODE УЗЕЛ =================
// Поле next должно быть указателем, так как структура 
// не может содержать саму себя целиком
// (её размер в таком случае был бы бесконечным, 
// и компилятор не будет знать, сколько памяти выделить).

typedef struct Node {
    int value;         // 4
    struct Node* next; // 8
} Node;

//  typedef позволяет в Си компиляторах
//  использовать просто псевдоним Node вместо struct Node для улучшения читаемости и чистоты кода; 

typedef struct LinkedList {
    int size;   // 4
    Node* head; // 8
    Node* tail; // 8
} LinkedList;

//============== PROTOTYPES (объявление заголовка функции) ===============

//===================================================
// = 25  баллов реализуете 3 метода
//===================================================
// void add(LinkedList* list, int value); 
// void printList(LinkedList* list);
// void freeList(LinkedList* list);

//===================================================
// += 15  баллов реализуете 2 метода
//===================================================
// LinkedList* insertAt(LinkedList* list, int index, int value);
// LinkedList* removeAt(LinkedList* list, int index);

//===================================================
// += 5 На 45  баллов вам достанется одна из 3 задач
//===================================================
void reverse(LinkedList* list);                      // 🔁 1. Разворот списка
bool hasCycle(LinkedList* list);                     // 🐢 2. Поиск цикла(Floyd)
void removeDuplicatesUnsorted(LinkedList* list);     // 🧹 3. Удаление дубликатов  (НЕ отсортированный — O(n²))

//===================================================
// += 5 На 50   баллов продвинутый уровень Floyd 
//===================================================
Node* detectCycleStart(LinkedList* list);            // 🔍 Найти начало цикла в связном списке. 
                                                     //    Если цикл есть — вернуть узел, с которого начинается цикл.
//===================================================

bool isEmpty(LinkedList* list);

Node*       createNode(int val);             // инициализация Node

LinkedList* createList();                    // инициализация пустого LinkedList
LinkedList* createList(int arr[], int size); // создвние списка заполненного данными из массива

int get(LinkedList* list, int index);
int set(LinkedList* list, int index, int value);

void add(LinkedList* list, int value);       //append push_back вставка элемента в конец списка 
void addFront(LinkedList* list, int value);

void removeFront(LinkedList* list);
void removeBack(LinkedList* list);

LinkedList* insertAt(LinkedList* list, int index, int value); 
LinkedList* removeAt(LinkedList* list, int index);

void printList(LinkedList* list);
void freeList(LinkedList* list);

void runTest();
void testInsertAt(int arr[], int size, int index, int value);
void testRemoveAt(int arr[], int size, int index);


int main()
{
    int arr[] = { 0,1,2,3,4,5,6,7,8,9 };

    LinkedList* list = createList(arr, sizeof(arr) / sizeof(int));
    printList(list);

    //insertAt(list, 4, 444);
    //insertAt(list, 0, 111);
    //insertAt(list, list->size-1, 999);
    //insertAt(list, list->size, 1010);
    //insertAt(list, list->size++, 1111);

    //removeAt(list, 4);
    //removeAt(list, 0);
    //removeAt(list, list->size);
    //removeAt(list, list->size - 1);
    
    //runTest();
    freeList(list);
}



//============== IMPLEMENTATION = РЕАЛИЗАЦИЯ МЕТОДОВ ===============

bool isEmpty(LinkedList* list) {
    return list == NULL || list->size == 0;
}

Node* createNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));

    if (!node) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    node->next = NULL; //*(node).next;
    node->value = val;

    return node;
}

LinkedList* createList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

    if (!list) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

LinkedList* createList(int arr[], int size) {
    LinkedList* list = createList();

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
        //list->head = list->tail = node;
    }
    else {
        list->tail->next = node;
        list->tail = node;
        //list->tail = list->tail->next = node;
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

LinkedList* insertAt(LinkedList* list, int index, int value) {

    printf("insertAt index = [%d] \n", index);

    if (list == NULL || index < 0 || index > list->size) {
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

    printList(list);

    return list;
}

LinkedList* removeAt(LinkedList* list, int index) {

    printf("removeAt index = [%d] \n", index);

    if (isEmpty(list) || index < 0 || index >= list->size) {
        printf("Index [%d] out of bounds\n", index);
        return list;
    }

    if (index == 0) {
        removeFront(list);
    }
    else if (index == list->size - 1) {
        removeBack(list);
    }
    else {

        Node* cur = list->head;
        for (int i = 0; i < index - 1; i++) {
            cur = cur->next;
        }

        Node* deleted = cur->next;
        cur->next = deleted->next;
        free(deleted);

        list->size--;
    }

    printList(list);


    return list;

}


void printList(LinkedList* list) {
    if (!isEmpty(list)) {
        Node* cur = list->head;
        printf("==============list==============\n");

        while (cur != NULL) {
            printf("%d ", cur->value);
            cur = cur->next;
        }
        printf("\n");

        printf("================================\n");
        printf("head->value = %d \n", list->head->value);
        printf("tail->value = %d \n", list->tail->value);
        printf("list->size  = %d \n", list->size);
        printf("================================\n");

    }
    else {
        printf("================================\n");
        printf("List is Empty \n");
        printf("================================\n");

    }
}

void addFront(LinkedList* list, int value) {
    Node* node = createNode(value);

    node->next = list->head;
    list->head = node;
    list->size++;
}

void removeFront(LinkedList* list) {

    if (isEmpty(list)) {
        return;
    }

    Node* deleted = list->head;
    list->head = list->head->next;
    free(deleted);
    list->size--;

    if (list->size == 0) {
        list->tail = NULL;
    }
}

void removeBack(LinkedList* list) {
    if (isEmpty(list)) {
        return;
    }

    if (list->size == 1) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return;
    }

    Node* cur = list->head;
    while (cur->next != list->tail) {
        cur = cur->next;
    }

    free(list->tail);
    list->tail = cur;
    list->tail->next = NULL;
    list->size--;
}

int get(LinkedList* list, int index) {

    if (index < 0 || index >= list->size) {
        printf("Index [%d] out of bounds\n", index);
        return -1;
    }

    Node* cur = list->head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }

    return cur->value;
}

int set(LinkedList* list, int index, int value) {

    if (index < 0 || index >= list->size) {
        printf("Index [%d] out of bounds\n", index);
        return -1;
    }

    Node* cur = list->head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }

    cur->value = value;

    return cur->value;
}
