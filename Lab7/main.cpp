// Lab7/main.cpp
// Лабораторна робота №7. Сортування підрахунком та блокове сортування.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <windows.h>

using namespace std;

#define MAX_SIZE 10001
#define MAX_VAL  9999
#define KOSHY    10

// Сортування підрахунком (для невід'ємних чисел до maxVal)
void countingSort(int arr[], int n, int maxVal) {
    int* countArr = new int[maxVal + 1]();
    for (int i = 0; i < n; i++)
        countArr[arr[i]]++;
    int index = 0;
    for (int v = 0; v <= maxVal; v++) {
        while (countArr[v] > 0) {
            arr[index] = v;
            index++;
            countArr[v]--;
        }
    }
    delete[] countArr;
}

// Сортування вставкою для одного кошика (допоміжна)
void insertionSortRange(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int element = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > element) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = element;
    }
}

// Блокове сортування
void bucketSort(int arr[], int n, int maxVal, int bucketCount) {
    int bucketSize = maxVal / bucketCount + 1;

    int* bucketStart = new int[bucketCount]();
    int* bucketLen = new int[bucketCount]();
    int* temp     = new int[n];
    int* index = new int[bucketCount]();

    // Рахуємо кількість елементів у кожному кошику
    for (int i = 0; i < n; i++) {
        int k = arr[i] / bucketSize;
        if (k >= bucketCount) k = bucketCount - 1;
        bucketLen[k]++;
    }

    // Визначаємо початкові позиції кошиків
    bucketStart[0] = 0;
    for (int i = 1; i < bucketCount; i++)
        bucketStart[i] = bucketStart[i - 1] + bucketLen[i - 1];

    // Розкладаємо елементи по кошиках у temp
    for (int i = 0; i < n; i++) {
        int k = arr[i] / bucketSize;
        if (k >= bucketCount) k = bucketCount - 1;
        temp[bucketStart[k] + index[k]] = arr[i];
        index[k]++;
    }

    // Сортуємо кожен кошик вставкою
    for (int k = 0; k < bucketCount; k++) {
        if (bucketLen[k] > 1)
            insertionSortRange(temp, bucketStart[k], bucketStart[k] + bucketLen[k] - 1);
    }

    // Копіюємо назад
    for (int i = 0; i < n; i++)
        arr[i] = temp[i];

    delete[] bucketStart;
    delete[] bucketLen;
    delete[] temp;
    delete[] index;
}

void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (MAX_VAL + 1);
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

    cout << "Лабораторна №7. Сортування підрахунком vs Блокове сортування\n";
    cout << "===========================================\n";
    cout << "Розмір\tАлгоритм\t\tЧас(мс)\n";
    cout << "-------------------------------------------\n";

    for (int s = 0; s < 3; s++) {
        int n = rozmiry[s];
        generateArray(original, n);

        // Сортування підрахунком
        copyArray(original, arr, n);
        auto t1 = chrono::high_resolution_clock::now();
        countingSort(arr, n, MAX_VAL);
        auto t2 = chrono::high_resolution_clock::now();
        double ms1 = chrono::duration<double, milli>(t2 - t1).count();
        cout << n << "\tПідрахунком\t\t" << ms1 << "\n";

        // Блокове сортування
        copyArray(original, arr, n);
        auto t3 = chrono::high_resolution_clock::now();
        bucketSort(arr, n, MAX_VAL, KOSHY);
        auto t4 = chrono::high_resolution_clock::now();
        double ms2 = chrono::duration<double, milli>(t4 - t3).count();
        cout << "\tБлокове\t\t\t" << ms2 << "\n";

        cout << "-------------------------------------------\n";
    }

    return 0;
}
