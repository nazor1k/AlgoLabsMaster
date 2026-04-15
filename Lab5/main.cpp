// Lab5/main.cpp
// Лабораторна робота №5. Сортування бульбашкою та сортування вставкою.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <windows.h>

using namespace std;

#define MAX_SIZE 10001

void bubbleSort(int arr[], int n, long long& checks, long long& changes) {
    checks = 0;
    changes = 0;
    for (int i = 0; i < n - 1; i++) {
        bool isChanged = false;
        for (int j = 0; j < n - i - 1; j++) {
            checks++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                changes++;
                isChanged = true;
            }
        }
        if (!isChanged) break;
    }
}

void insertionSort(int arr[], int n, long long& checks, long long& moves) {
    checks = 0;
    moves = 0;
    for (int i = 1; i < n; i++) {
        int element = arr[i];
        int j = i - 1;
        while (j >= 0) {
            checks++;
            if (arr[j] > element) {
                arr[j + 1] = arr[j];
                moves++;
                j--;
            }
            else break;
        }
        arr[j + 1] = element;
    }
}

void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

int original[MAX_SIZE];
int arr[MAX_SIZE];

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand((unsigned)time(0));

    int rozmiry[] = { 100, 1000, 10000 };

    cout << "Лабораторна №5. Порівняння сортувань\n";
    cout << "===========================================\n";
    cout << "Розмір\tАлгоритм\tПорівн.\tОбміни\tЧас(мс)\n";
    cout << "-------------------------------------------\n";

    for (int s = 0; s < 3; s++) {
        int n = rozmiry[s];
        generateArray(original, n);

        long long checks, changes;

        // Бульбашка
        copyArray(original, arr, n);
        auto t1 = chrono::high_resolution_clock::now();
        bubbleSort(arr, n, checks, changes);
        auto t2 = chrono::high_resolution_clock::now();
        double ms1 = chrono::duration<double, milli>(t2 - t1).count();
        cout << n << "\tБульбашка\t" << checks << "\t" << changes << "\t" << ms1 << "\n";

        // Вставка
        copyArray(original, arr, n);
        auto t3 = chrono::high_resolution_clock::now();
        insertionSort(arr, n, checks, changes);
        auto t4 = chrono::high_resolution_clock::now();
        double ms2 = chrono::duration<double, milli>(t4 - t3).count();
        cout << "\tВставка\t\t" << checks << "\t" << changes << "\t" << ms2 << "\n";

        cout << "-------------------------------------------\n";
    }

    return 0;
}
