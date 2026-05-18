#include <iostream>

//Узел
typedef struct Node {
    int value;  // 4
    Node* next; // 8
} Node;

//  typedef позволяет в Си компиляторах
//  использовать просто псевдоним Node вместо struct Node для улучшения читаемости и чистоты кода; 

typedef struct LinkedList {
    int size;   // 4
    Node* head; // 8
    Node* tail; // 8
} LinkedList;

//==============Prototypes===============

bool isEmpty(LinkedList* list);

//инициализация Node
Node* createNode(int val);

//инициализация пустого LinkedList
LinkedList* createList();

//создвние списка заполненного данными из массива
LinkedList* createList(int arr[], int size);

//============== 3 function = 25 points ===============


void add(LinkedList* list, int value); //append push_back вставка элемента в конец списка 

void printList(LinkedList* list);

void freeList(LinkedList* list);

//===================================================

//================ 2 function = 15 points ============


LinkedList* insertAt(LinkedList* list, int index, int value);

LinkedList* removeAt(LinkedList* list, int index);

//===================================================


int get(LinkedList* list, int index);

void addFront(LinkedList* list, int value);

void removeFront(LinkedList* list);

void removeBack(LinkedList* list);

//===================================================
// На 45  баллов вам достанется одна из 3 задач
//===================================================

// 🔁 1. Разворот списка
void reverse(LinkedList* list);

// 🐢 2. Поиск цикла(Floyd)
bool hasCycle(LinkedList* list);

//🧹 3. Удаление дубликатов  (НЕ отсортированный — O(n²))
void removeDuplicatesUnsorted(LinkedList* list);

//===================================================
// На 50  баллов           продвинутый уровень Floyd 
//===================================================
//

//🧠 Задача : Найти начало цикла в связном списке
//             Дан односвязный список.
//             Некоторые узлы могут образовывать цикл — то есть последний элемент списка может указывать на один из предыдущих.
//   Ваша задача :
//              🔍 Определить, есть ли цикл в списке, и если есть — вернуть узел, с которого начинается цикл.
//                 Если цикла нет — вернуть NULL.

Node* detectCycleStart(LinkedList* list);

//===================================================

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


LinkedList* insertAt(LinkedList* list, int index, int value) {

    printList(list);
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

    printList(list);

    return list;
}

LinkedList* removeAt(LinkedList* list, int index) {


    printList(list);
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


int main()
{
    int arr[] = { 0,1,2,3,4,5,6,7,8,9 };

    LinkedList* list = createList(arr, sizeof(arr) / sizeof(int));
    printList(list);

    //insertAt(list, 4, 444);
    //insertAt(list, 0, 111);
    //insertAt(list, 9, 999);
    //insertAt(list, 10, 1010);
    //insertAt(list, 11, 1111);

    //removeAt(list, 4);
    //removeAt(list, 0);
    //removeAt(list, list->size);
    //removeAt(list, list->size - 1);


    freeList(list);

}
