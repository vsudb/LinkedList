#include <iostream>

// Выравнивание нужно потому, что процессор работает с памятью 
// не как с абстрактной последовательностью отдельных байтов, 
// а обычно читает данные блоками фиксированного размера : 
// например, по 4, 8, 16 байт и так далее.

// Допустим, указатель занимает 8 байт.
// Процессору удобнее и быстрее читать такой указатель, 
// если он лежит по адресу, кратному 8 :

// Cама структура имеет максимальное выравнивание 8 байт, 
// потому что внутри есть указатель.
// Значит, размер всей структуры тоже должен быть кратен 8. 
// Размер 8 + 4 = 12, а 12 не кратно 8, поэтому компилятор добавляет 4 байта в конец :

// Кратко: выравнивание нужно, чтобы процессор мог быстрее и корректнее читать данные из памяти. 
// Padding — это цена в несколько лишних байтов за более эффективный доступ к данным.

//Узел
struct Node {
	int value;  // 4
	Node* next; // 8
};

struct Node2 {
	Node2* next; // 8
	int value;   // 4
};

struct Node3 {
	int count;   // 4
	Node3* next; // 8
	int value;   // 4
};

struct Node4 {
	Node4* next;  // 8
	int value;	  // 4
	int count;	  // 4
};


struct Node5 {
	Node5* next;  // 8
	int value;	  // 4
	int count;	  // 4
	int four;	  // 4
};



// Обычная структура
struct Standard {
	char a;     // 1 байт + 3 байта отступа
	int b;      // 4 байта
};

// Упакованная структура
#pragma pack(push, 1) // Сохраняем текущие настройки и ставим упаковку в 1 байт
struct Packed {
	char a;     // 1 байт
	int b;      // 4 байта (идет сразу за char)
};

#pragma pack(pop)    // Возвращаем настройки выравнивания в исходное состояние


int main()
{

	printf("Size of Standard: %zu\n", sizeof(Standard));   // Выведет 8
	printf("Size of Packed: %zu\n"  , sizeof(Packed));     // Выведет 5

	Node  node = { 5, nullptr };
	Node2 node2 = { nullptr, 7 };
	Node3 node3 = { 3, nullptr, 7 };
	Node4 node4 = { nullptr, 7, 3 };
	Node5 node5 = { nullptr, 7, 3, 2 };

	node.value = 10;
	//node.next =;

	printf("size Node %zd\n" , sizeof(node));
	printf("size Node2 %zd\n", sizeof(node2));
	printf("size Node3 %zd\n", sizeof(node3));
	printf("size Node4 %zd\n", sizeof(node4));
	printf("size Node5 %zd\n", sizeof(node5));
}

