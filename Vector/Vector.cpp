#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ================= VECTOR ДИНАМИЧЕСКИЙ МАССИВ=================

typedef struct Vector {
    int* data;
    int size;     // Фактическое количество элементов в массиве
    int capacity; // Вместимость массива - количество элементов в массиве, 
                  // в массиве могут быть не задействованные ячейки для ускорения процедуры вставки в массив
} Vector;

// ================= PROTOTYPES =================

Vector* createVector(int capacity);
void freeVector(Vector* v);

void pushBack(Vector* v, int value);
void popBack(Vector* v);

int get(Vector* v, int index);
bool set(Vector* v, int index, int value);

void insert(Vector* v, int index, int value);
void erase(Vector* v, int index);

void resize(Vector* v, int newCapacity);
void printVector(Vector* v);

// ================= IMPLEMENTATION =================

// -------- create --------
Vector* createVector(int capacity) {
    Vector* v = (Vector*)malloc(sizeof(Vector));
    if (!v) return NULL;

    v->data = (int*)malloc(sizeof(int) * capacity);
    v->size = 0;
    v->capacity = capacity;

    return v;
}

// -------- free --------
void freeVector(Vector* v) {
    if (v) {
        free(v->data);
        free(v);
    }
}

// -------- resize internal --------
void resize(Vector* v, int newCapacity) {
    int* newData = (int*)realloc(v->data, sizeof(int) * newCapacity);

    if (!newData) return;

    v->data = newData;
    v->capacity = newCapacity;
}

// -------- push back --------
void pushBack(Vector* v, int value) {
    if (v->size >= v->capacity) {
        resize(v, v->capacity * 2);
    }

    v->data[v->size++] = value;
}

// -------- pop back --------
void popBack(Vector* v) {
    if (v->size > 0) {
        v->size--;
    }
}

// -------- get --------
int get(Vector* v, int index) {
    if (!v || index < 0 || index >= v->size)
        return -1;

    return v->data[index];
}

// -------- set --------
bool set(Vector* v, int index, int value) {
    if (!v || index < 0 || index >= v->size)
        return false;

    v->data[index] = value;
    return true;
}

// -------- insert --------
void insert(Vector* v, int index, int value) {
    if (!v || index < 0 || index > v->size)
        return;

    if (v->size >= v->capacity) {
        resize(v, v->capacity * 2);
    }

    for (int i = v->size; i > index; i--) {
        v->data[i] = v->data[i - 1];
    }

    v->data[index] = value;
    v->size++;
}

// -------- erase --------
void erase(Vector* v, int index) {
    if (!v || index < 0 || index >= v->size)
        return;

    for (int i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }

    v->size--;
}

// -------- print --------
void printVector(Vector* v) {
    if (!v) return;

    for (int i = 0; i < v->size; i++) {
        printf("%d ", v->data[i]);
    }
    printf("\n");
}

// ================= MAIN =================

int main() {

    Vector* v = createVector(4);

    pushBack(v, 1);
    pushBack(v, 2);
    pushBack(v, 3);
    pushBack(v, 4);
    pushBack(v, 5); // triggers resize

    printVector(v);

    insert(v, 2, 99);
    printVector(v);

    erase(v, 1);
    printVector(v);

    printf("get(2) = %d\n", get(v, 2));

    set(v, 0, 777);
    printVector(v);

    popBack(v);
    printVector(v);

    freeVector(v);

    return 0;
}