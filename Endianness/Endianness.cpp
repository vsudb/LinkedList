#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <cstdint>

#pragma comment(lib, "Ws2_32.lib")

void print_bytes(const char* label, void* ptr, size_t size) {
    printf("%s: ", label);
    unsigned char* p = (unsigned char*)ptr;
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", p[i]);
    }
    printf("\n");
}

//Допустим, сервер отправляет пакет, в котором указан номер порта 80 (в 16 - ричной системе это 0x0050).
//1. Что происходит в сети(Big - Endian) :
//    Сетевая карта передает байты ровно в том порядке, в котором они идут в числе :
//Байт 1 : 0x00
//Байт 2 : 0x50
//2. Что происходит на компьютере студента(Little - Endian) :
//    Процессор Intel получает эти байты и кладет их в память.Когда программа пытается прочитать их как uint16_t, она интерпретирует их «навыворот» :
//Она думает, что первым пришел младший байт.
//В итоге для компьютера число выглядит как 0x5000.
//Результат : Вместо порта 80 программа увидит порт 20480. Соединение не установится.

void broken_port_2() {
    // Порт 80 (0x0050)
    uint16_t port = 80;

    // 1. Посмотрим, как он лежит в памяти (на Intel это будет 50 00)
    unsigned char* ptr = (unsigned char*)&port;
    printf("Raw bytes in memory (Little-Endian): %02x %02x\n", ptr[0], ptr[1]);

    // 2. Имитируем отправку в сеть (переводим в Big-Endian)
    uint16_t net_port = htons(port); // Host TO Network Short

    unsigned char* net_ptr = (unsigned char*)&net_port;
    printf("Raw bytes for Network (Big-Endian):    %02x %02x\n", net_ptr[0], net_ptr[1]);

    // 3. Если мы забудем конвертировать обратно при получении:
    printf("\nIf we forget to convert: we see port %d instead of 80\n", net_port);

}

void broken_port() {
    uint16_t host_port = 443; // 0x01BB
    uint16_t net_port = htons(host_port); // Host to Network Short

    printf("--- Port 443 Analysis ---\n");
    printf("Host Order (Little-Endian): 0x%04X\n", host_port);
    printf("Network Order (Big-Endian): 0x%04X\n", net_port);

    // Demonstration of the "Broken Port"
    if (net_port != host_port) {
        printf("\nWARNING: If you don't use htons(), the server sees port %u instead of %u\n",
            (uint16_t)net_port, host_port);
    }


}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Берем порт 80. В хексе это 0x0050
    unsigned short host_port = 80;

    // ПРЯМОЙ ПОРЯДОК (Host Order / Little-Endian на Intel)
    // В памяти байты перевернуты: младший идет первым
    printf("--- HOST ORDER (Little-Endian) ---\n");
    printf("Value: %d (0x%04X)\n", host_port, host_port);
    print_bytes("Bytes in memory", &host_port, sizeof(host_port));

    printf("\n");

    // ОБРАТНЫЙ ПОРЯДОК (Network Order / Big-Endian)
    // Используем htons для перевода в сетевой стандарт
    unsigned short net_port = htons(host_port);

    printf("--- NETWORK ORDER (Big-Endian) ---\n");
    printf("Value: %d (0x%04X)\n", net_port, net_port);
    print_bytes("Bytes in memory", &net_port, sizeof(net_port));

    WSACleanup();
    return 0;
}

//Пример для студентов : "Сломанный порт"
//Допустим, сервер отправляет пакет, в котором указан номер порта 80 (в 16 - ричной системе это 0x0050).
//1. Что происходит в сети(Big - Endian) :
//    Сетевая карта передает байты ровно в том порядке, в котором они идут в числе :
//Байт 1 : 0x00
//Байт 2 : 0x50
//2. Что происходит на компьютере студента(Little - Endian) :
//    Процессор Intel получает эти байты и кладет их в память.Когда программа пытается прочитать их как uint16_t, она интерпретирует их «навыворот» :
//Она думает, что первым пришел младший байт.
//В итоге для компьютера число выглядит как 0x5000.
//Результат : Вместо порта 80 программа увидит порт 20480. Соединение не установится.
