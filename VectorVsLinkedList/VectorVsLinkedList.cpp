// VectorVsLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int main() {
    const int N = 10'000'000; // размер контейнеров
    const int target = N - 1; // элемент для поиска (в конце)

    vector<int> vec;
    list<int> lst;

    cout << "Filling Vector and LinkedList" << endl;
    // Заполнение
    for (int i = 0; i < N; ++i) {
        vec.push_back(i);
        lst.push_back(i);
    }
    cout << "End of filling" << endl;

    // =========================
    // 🔍 Поиск в vector
    // =========================
    auto start_vec_search = high_resolution_clock::now();

    auto it_vec = find(vec.begin(), vec.end(), target);

    auto end_vec_search = high_resolution_clock::now();
    auto vec_search_time = duration_cast<milliseconds>(end_vec_search - start_vec_search);

    cout << "Vector search time: " << vec_search_time.count() << " ms" << endl;

    // =========================
    // 🔍 Поиск в list
    // =========================
    auto start_list_search = high_resolution_clock::now();

    auto it_lst = find(lst.begin(), lst.end(), target);

    auto end_list_search = high_resolution_clock::now();
    auto list_search_time = duration_cast<milliseconds>(end_list_search - start_list_search);

    cout << "List search time: " << list_search_time.count() << " ms" << endl;

    // =========================
    // 🔁 Обход vector
    // =========================
    long long sum_vec = 0;
    auto start_vec_iter = high_resolution_clock::now();

    for (int x : vec) {
        sum_vec += x;
    }

    auto end_vec_iter = high_resolution_clock::now();
    auto vec_iter_time = duration_cast<milliseconds>(end_vec_iter - start_vec_iter);

    cout << "Vector iteration time: " << vec_iter_time.count() << " ms" << endl;

    // =========================
    // 🔁 Обход list
    // =========================
    long long sum_lst = 0;
    auto start_list_iter = high_resolution_clock::now();

    for (int x : lst) {
        sum_lst += x;
    }

    auto end_list_iter = high_resolution_clock::now();
    auto list_iter_time = duration_cast<milliseconds>(end_list_iter - start_list_iter);

    cout << "List iteration time: " << list_iter_time.count() << " ms" << endl;

    return 0;
}