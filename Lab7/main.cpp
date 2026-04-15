// Lab7/main.cpp
// Лабораторна робота №7. Сортування підрахунком та блокове сортування.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <windows.h>

using namespace std;

// Сортування підрахунком (тільки для невід'ємних чисел до maxVal)
void countingSort(int arr[], int n, int maxVal) {
    int* count = new int[maxVal + 1]();
    for (int i = 0; i < n; i++)
        count[arr[i]]++;
    int idx = 0;
    for (int v = 0; v <= maxVal; v++)
        while (count[v]-- > 0)
            arr[idx++] = v;
    delete[] count;
}

// Сортування вставкою для кошика (допоміжна)
void insertionSortRange(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Блокове сортування
void bucketSort(int arr[], int n, int maxVal, int bucketCount) {
    // Визначаємо межі кошиків
    int bucketSize = maxVal / bucketCount + 1;
    // Масиви для підрахунку та індексів
    int* bucketStart = new int[bucketCount]();
    int* bucketLen = new int[bucketCount]();

    for (int i = 0; i < n; i++) {
        int b = arr[i] / bucketSize;
        if (b >= bucketCount) b = bucketCount - 1;
        bucketLen[b]++;
    }

    bucketStart[0] = 0;
    for (int i = 1; i < bucketCount; i++)
        bucketStart[i] = bucketStart[i - 1] + bucketLen[i - 1];

    // Розкладаємо по кошиках
    int* temp = new int[n];
    int* pos = new int[bucketCount]();
    for (int i = 0; i < n; i++) {
        int b = arr[i] / bucketSize;
        if (b >= bucketCount) b = bucketCount - 1;
        temp[bucketStart[b] + pos[b]] = arr[i];
        pos[b]++;
    }

    // Сортуємо кожен кошик
    for (int b = 0; b < bucketCount; b++) {
        if (bucketLen[b] > 1)
            insertionSortRange(temp, bucketStart[b], bucketStart[b] + bucketLen[b] - 1);
    }

    for (int i = 0; i < n; i++)
        arr[i] = temp[i];

    delete[] bucketStart;
    delete[] bucketLen;
    delete[] temp;
    delete[] pos;
}

void fillRandom(int arr[], int n, int maxVal) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (maxVal + 1);
}

void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand((unsigned)time(0));

    int sizes[] = { 100, 1000, 10000 };
    int MAX_VAL = 9999;
    int BUCKETS = 10;

    cout << "Лабораторна №7. Сортування підрахунком vs Блокове сортування\n";
    cout << "===========================================\n";
    cout << "Розмір\tАлгоритм\t\tЧас(мс)\n";
    cout << "-------------------------------------------\n";

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        int* original = new int[n];
        int* arr = new int[n];
        fillRandom(original, n, MAX_VAL);

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
        bucketSort(arr, n, MAX_VAL, BUCKETS);
        auto t4 = chrono::high_resolution_clock::now();
        double ms2 = chrono::duration<double, milli>(t4 - t3).count();
        cout << "\tБлокове\t\t\t" << ms2 << "\n";

        cout << "-------------------------------------------\n";

        delete[] original;
        delete[] arr;
    }

    return 0;
}
