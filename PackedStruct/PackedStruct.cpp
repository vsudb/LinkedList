#include <cstdio>
#include <ctime>
#include <vector>

using namespace std;

#pragma pack(push, 1)
struct Packed {
    char a;
    int b; // Адрес этого int всегда будет (не кратным 4)
};
#pragma pack(pop)

struct Aligned {
    char a;
    // Здесь компилятор добавит 3 байта Padding
    int b; // Адрес этого int всегда выровнен по 4 байтам
};

const int SIZE = 1'000;
const int ITERATIONS = 100'000'000; // 100 миллионов операций

int main() {
    vector<Packed> packed_arr(SIZE);
    vector<Aligned> aligned_arr(SIZE);


    // Заполняем векторы данными
    for (int i = 0; i < SIZE; ++i) {
        packed_arr[i].a = 'p';
        packed_arr[i].b = i;      // Записываем число i

        aligned_arr[i].a = 'a';
        aligned_arr[i].b = i;     // Записываем то же число i
    }



    // Тест для выровненной структуры
    clock_t start_aligned = clock();
    long long sum_a = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        sum_a += aligned_arr[i % SIZE].b;
    }
    clock_t end_aligned = clock();

    // Тест для невыровненной (упакованной) структуры
    clock_t start_packed = clock();
    long long sum_p = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        sum_p += packed_arr[i % SIZE].b;
    }
    clock_t end_packed = clock();

    printf("Aligned time: %.3f sec\n", (double)(end_aligned - start_aligned) / CLOCKS_PER_SEC);
    printf("Packed time:  %.3f sec\n", (double)(end_packed - start_packed) / CLOCKS_PER_SEC);

    return 0;
}


/*
* Что здесь происходит:
    Промах мимо кэш-линий: 
        Процессор читает память блоками по 64 байта (кэш-линии). 
        В упакованном случае int может «разрезаться» — часть числа окажется в конце одной кэш-линии, а часть в начале другой.
        Процессору придется загружать две линии вместо одной.
    Лишние такты: 
        Даже если данные в одной кэш-линии, 
        контроллеру памяти требуется выполнить дополнительные сдвиги 
        и логические операции (AND/OR), чтобы «выкусить» невыровненное число 
        из общего потока байтов.

    Компилируйте без оптимизаций (например, просто g++ main.cpp), 
    иначе компилятор может понять, что данные в массиве нулевые, и просто выкинет цикл.
*/