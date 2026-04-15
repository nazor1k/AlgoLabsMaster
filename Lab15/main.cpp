// Lab15/main.cpp
// Лабораторна робота №15. Хешування. Хеш-таблиця з методом ланцюжків.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <windows.h>

using namespace std;

#define TABLE_SIZE 101

struct HNode {
    int key;
    HNode* next;
};

struct HashTable {
    HNode* buckets[TABLE_SIZE];
    int size;
    int collisions;

    HashTable() : size(0), collisions(0) {
        for (int i = 0; i < TABLE_SIZE; i++)
            buckets[i] = nullptr;
    }

    int hash(int key) {
        return ((key % TABLE_SIZE) + TABLE_SIZE) % TABLE_SIZE;
    }

    void insert(int key) {
        int idx = hash(key);
        // Перевіряємо чи вже є
        for (HNode* cur = buckets[idx]; cur; cur = cur->next)
            if (cur->key == key) return;
        if (buckets[idx]) collisions++;
        HNode* node = new HNode{ key, buckets[idx] };
        buckets[idx] = node;
        size++;
    }

    bool search(int key) {
        int idx = hash(key);
        for (HNode* cur = buckets[idx]; cur; cur = cur->next)
            if (cur->key == key) return true;
        return false;
    }

    bool remove(int key) {
        int idx = hash(key);
        HNode** cur = &buckets[idx];
        while (*cur) {
            if ((*cur)->key == key) {
                HNode* tmp = *cur;
                *cur = (*cur)->next;
                delete tmp;
                size--;
                return true;
            }
            cur = &(*cur)->next;
        }
        return false;
    }

    void print() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!buckets[i]) continue;
            cout << "[" << i << "]: ";
            for (HNode* cur = buckets[i]; cur; cur = cur->next) {
                cout << cur->key;
                if (cur->next) cout << " -> ";
            }
            cout << "\n";
        }
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HNode* cur = buckets[i];
            while (cur) {
                HNode* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand((unsigned)time(0));

    cout << "=== Хеш-таблиця (розмір=" << TABLE_SIZE << ", метод ланцюжків) ===\n\n";

    // Демонстрація
    HashTable ht;
    int demoKeys[] = { 10, 20, 15, 7, 111, 212, 303 };
    for (int k : demoKeys) ht.insert(k);

    cout << "Вставлено: 10 20 15 7 111 212 303\n";
    cout << "Таблиця (непорожні кошики):\n";
    ht.print();

    cout << "\nПошук 15: " << (ht.search(15) ? "знайдено" : "не знайдено") << "\n";
    cout << "Пошук 99: " << (ht.search(99) ? "знайдено" : "не знайдено") << "\n";

    ht.remove(15);
    cout << "Після видалення 15, пошук 15: " << (ht.search(15) ? "знайдено" : "не знайдено") << "\n";
    cout << "Елементів у таблиці: " << ht.size << "\n";
    cout << "Колізій: " << ht.collisions << "\n";

    // Тест продуктивності
    cout << "\n=== Продуктивність на великих даних ===\n";
    int sizes[] = { 1000, 10000, 100000 };
    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        HashTable t;

        auto t1 = chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++) t.insert(rand());
        auto t2 = chrono::high_resolution_clock::now();
        double msIns = chrono::duration<double, milli>(t2 - t1).count();

        auto t3 = chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++) t.search(rand());
        auto t4 = chrono::high_resolution_clock::now();
        double msSrch = chrono::duration<double, milli>(t4 - t3).count();

        cout << "N=" << n << "\tВставка: " << msIns << " мс\tПошук: " << msSrch << " мс\t"
             << "Колізій: " << t.collisions << "\n";
    }

    return 0;
}
