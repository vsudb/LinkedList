#include <iostream>
#include <stdio.h>
#include <stdlib.h>


//Узел

typedef struct Node {   //  typedef позволяет в Си компиляторах 
						//  использовать просто псевдоним Node вместо struct Node для улучшения читаемости и чистоты кода; 
	int value;  // 4
	struct Node* next; // 8
} Node;

typedef struct LinkedList {
	int size;
	Node* head;
	Node* tail;
} LinkedList;


void add(LinkedList* list, int value);

bool isEmpty(LinkedList* list);

LinkedList* createList(int arr[], int size);

int get(LinkedList* list, int i);

void printList(LinkedList* list);

void freeList(LinkedList* list);




bool isEmpty(LinkedList* list) {
	if (list == NULL || list->size == 0)
		return true;
	else
		return false;
}

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

LinkedList* createList(int arr[], int size) {
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
	if (list == NULL) {
		return NULL;
	}

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	for (int i = 0; i < size; i++) {
		add(list, arr[i]);
	}
	return list;
}

int get(LinkedList* list, int index) {
	if (list == NULL) {
		return NULL;
	}

	Node* cur = list->head;
	for (int i = 0; i < index; i++) {
		cur = cur->next;
	}

	return cur->value;
}

void printList(LinkedList* list) {
	
	if (isEmpty(list)) {
		printf("List is empty\n");
		return;
	}

	Node* cur = list->head;
	for (int i = 0; i < list->size; i++) {
		printf("%d ", cur->value);
		cur = cur->next;
	}

	printf("\n");
}

void freeList(LinkedList* list) {
	if (list != NULL) {

		Node* cur = list->head;

		while (cur != NULL) {
			Node* next = cur->next;
			free(cur);
			cur = next;
		}
		free(list);
	}
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	LinkedList* list  = createList(arr, sizeof(arr) / sizeof(int));
	printf("%d \n", get(list, 5));

	
	printList(list);
	freeList(list);

}

