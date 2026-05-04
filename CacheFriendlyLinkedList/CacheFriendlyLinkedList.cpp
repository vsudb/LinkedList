#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000000

// =====================
// 📦 Узел (индекс вместо указателя)
// =====================
typedef struct {
    int data;
    int next; // индекс
} Node;

// =====================
// 🧠 Пул памяти
// =====================
Node pool[MAX_NODES];
int free_index = 0;

// =====================
// 🏗️ Создание узла
// =====================
int create_node(int value) {
    if (free_index >= MAX_NODES) {
        printf("Out of memory\n");
        exit(1);
    }

    pool[free_index].data = value;
    pool[free_index].next = -1;
    return free_index++;
}

// =====================
// 📋 Список
// =====================
typedef struct {
    int head;
} List;

void init_list(List* list) {
    list->head = -1;
}

// =====================
// ➕ Добавление
// =====================
void push_front(List* list, int value) {
    int node = create_node(value);
    pool[node].next = list->head;
    list->head = node;
}

void push_back(List* list, int value) {
    int node = create_node(value);

    if (list->head == -1) {
        list->head = node;
        return;
    }

    int cur = list->head;
    while (pool[cur].next != -1)
        cur = pool[cur].next;

    pool[cur].next = node;
}

// =====================
// 🔁 Обход
// =====================
void print_list(List* list) {
    int cur = list->head;
    while (cur != -1) {
        printf("%d -> ", pool[cur].data);
        cur = pool[cur].next;
    }
    printf("NULL\n");
}

// =====================
// 🔍 Поиск
// =====================
int find(List* list, int value) {
    int cur = list->head;

    while (cur != -1) {
        if (pool[cur].data == value)
            return cur;
        cur = pool[cur].next;
    }

    return -1;
}

// =====================
// ❌ Удаление
// =====================
void pop_front(List* list) {
    if (list->head == -1) return;

    list->head = pool[list->head].next;
}

void delete_value(List* list, int value) {
    while (list->head != -1 && pool[list->head].data == value) {
        list->head = pool[list->head].next;
    }

    int cur = list->head;

    while (cur != -1 && pool[cur].next != -1) {
        if (pool[pool[cur].next].data == value) {
            pool[cur].next = pool[pool[cur].next].next;
        }
        else {
            cur = pool[cur].next;
        }
    }
}

// =====================
// 🔄 Разворот
// =====================
void reverse(List* list) {
    int prev = -1;
    int cur = list->head;

    while (cur != -1) {
        int next = pool[cur].next;
        pool[cur].next = prev;
        prev = cur;
        cur = next;
    }

    list->head = prev;
}

// =====================
// 🔢 Размер
// =====================
int size(List* list) {
    int count = 0;
    int cur = list->head;

    while (cur != -1) {
        count++;
        cur = pool[cur].next;
    }

    return count;
}

// =====================
// 🧪 Демонстрация
// =====================
int main() {
    List list;
    init_list(&list);

    push_back(&list, 1);
    push_back(&list, 2);
    push_back(&list, 3);
    push_front(&list, 0);

    print_list(&list);

    printf("Size: %d\n", size(&list));

    reverse(&list);
    print_list(&list);

    delete_value(&list, 2);
    print_list(&list);

    return 0;
}