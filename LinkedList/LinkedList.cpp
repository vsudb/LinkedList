#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Определение узла
//typedef struct Node {
//    int value;
//    struct Node* next;
//} Node;
//
//// Определение самого списка
//typedef struct LinkedList {
//    int size;
//    Node* head;
//    Node* tail;
//} LinkedList;
//
//// Функция создания пустого списка
//LinkedList* createList() {
//    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
//    list->head = NULL;
//    list->tail = NULL;
//    list->size = 0;
//    return list;
//}
//
//// Добавление в конец
//void add(LinkedList* list, int value) {
//    Node* newNode = (Node*)malloc(sizeof(Node));
//    newNode->value = value;
//    newNode->next = NULL;
//
//    if (list->head == NULL) {
//        list->head = newNode;
//        list->tail = newNode;
//    }
//    else {
//        list->tail->next = newNode;
//        list->tail = newNode;
//    }
//    list->size++;
//}
//
//// Функция создания пустого списка
//LinkedList* createList(int arr[], int size) {
//    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
//    list->head = NULL;
//    list->tail = NULL;
//    list->size = 0;
//    
//    for (int i = 0; i < size; i++) {
//      		add(list, arr[i]);
//    }
//
//    return list;
//}
//
//// Вывод списка
//void printList(LinkedList* list) {
//    Node* cur = list->head;
//    while (cur != NULL) {
//        printf("%d -> ", cur->value);
//        cur = cur->next;
//    }
//    printf("NULL\n");
//}
//
//// Очистка памяти (в Си это обязательно делать вручную)
//void freeList(LinkedList* list) {
//    Node* cur = list->head;
//    while (cur != NULL) {
//        Node* temp = cur;
//        cur = cur->next;
//        free(temp); // Освобождаем каждый узел
//    }
//    free(list); // Освобождаем саму структуру списка
//}
//
//int main() {
//    //LinkedList* myList = createList();
//
//    //add(myList, 10);
//    //add(myList, 20);
//    //add(myList, 30);
//
//    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//
//    LinkedList* myList  = createList(arr, sizeof(arr) / sizeof(int));
//
//    printf("Size of list: %d\n", myList->size);
//    printList(myList);
//
//    freeList(myList); // Удаляем список перед выходом
//    return 0;
//}
//Узел
 struct Node {
	int value;  // 4
	struct Node* next; // 8
};
 struct LinkedList {
	int size;
	Node* head;
	Node* tail;
};

void add(LinkedList* list, int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->next = NULL;
	//list->size++;
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	}
	else {
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}

LinkedList* createList(int arr[], int size) {
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	for (int i = 0; i < size; i++) {
		add(list, arr[i]);
	}
	return list;
}

void printList(LinkedList* list) {
	Node* cur = list->head;

	for (int i = 0; i < list->size; i++) {
		printf("%d ", cur->value );
		cur = cur->next;
	}
	printf("\n ");
}

//void printList(LinkedList* list) {
//    Node* cur = list->head;
//    while (cur != NULL) {
//        printf("%d -> ", cur->value);
//        cur = cur->next;
//    }
//    printf("NULL\n");
//}

void freeList(LinkedList* list) {
    Node* cur = list->head;
    while (cur != NULL) {
        Node* temp = cur;
        cur = cur->next;
        free(temp); // Освобождаем каждый узел
    }
    free(list); // Освобождаем саму структуру списка
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	LinkedList* list  = createList(arr, sizeof(arr) / sizeof(int));
	printList(list);
	freeList(list);

}

