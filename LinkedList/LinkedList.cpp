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



Node* createNode(int value);

LinkedList* createList();

LinkedList* createList(int arr[], int size);

bool isEmpty(LinkedList* list);


void add(LinkedList* list, int value);

void addFront(LinkedList* list, int value);

void insertAt(LinkedList* list, int index, int value);



int get(LinkedList* list, int index);

void printList(LinkedList* list);

void freeList(LinkedList* list);




// ================== БАЗА ==================

bool isEmpty(LinkedList* list) {
	return (list == NULL || list->size == 0);
}

Node* createNode(int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->next = NULL;
	return node;
}

// ➕ В начало (O(1))
void addFront(LinkedList* list, int value) {
	Node* node = createNode(value);

	if (isEmpty(list)) {
		list->head = list->tail = node;
	}
	else {
		node->next = list->head;
		list->head = node;
	}
	list->size++;
}


// ➕ В конец (O(1))
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

// ➕ В середину (по индексу)
void insertAt(LinkedList* list, int index, int value) {
	if (index < 0 || index > list->size) return;

	if (index == 0) {
		addFront(list, value);
		return;
	}

	if (index == list->size) {
		add(list, value);
		return;
	}

	Node* node = createNode(value);
	Node* cur = list->head;

	for (int i = 0; i < index - 1; i++) {
		cur = cur->next;
	}

	node->next = cur->next;
	cur->next = node;

	list->size++;
}



// ================== УДАЛЕНИЕ ==================

void removeAt(LinkedList* list, int index) {
	if (isEmpty(list) || index < 0 || index >= list->size) return;

	Node* toDelete;

	// удаление головы
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
}


// ================== ДОСТУП ==================

int get(LinkedList* list, int index) {
	if (isEmpty(list) || index < 0 || index >= list->size) {
		printf("Index out of bounds\n");
		return -1;
	}

	Node* cur = list->head;

	for (int i = 0; i < index; i++) {
		cur = cur->next;
	}

	return cur->value;
}

// ================== СЛУЖЕБНЫЕ ==================

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

LinkedList* createList() {
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
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

