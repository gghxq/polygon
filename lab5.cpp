#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <chrono>

using namespace std;

// Сортировка методом Bucket Sort
void bucketSort(vector<double>& arr) {
    int n = arr.size();
    vector<vector<double>> buckets(n);

    for (double num : arr) {
        int bucketIndex = static_cast<int>(num * n);
        buckets[bucketIndex].push_back(num);
    }

    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
    }

    int index = 0;
    for (const auto& bucket : buckets) {
        for (double num : bucket) {
            arr[index++] = num;
        }
    }
}

// Память и сложность Bucket Sort:
/*
Память:
1. Вектора для корзин: O(n).
2. Исходный массив: O(n).
Итого: O(n).

Время:
1. Распределение по корзинам: O(n).
2. Сортировка каждой корзины: O(n log(n/k)), где k - средний размер корзины.
Итого: O(n + n log(n/k)) ≈ O(n log n) в худшем случае.
*/

// Сортировка методом Heap Sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Память и сложность Heap Sort:
/*
Память:
1. Исходный массив: O(n).
2. Дополнительный стек для рекурсии в heapify: O(log n).
Итого: O(n).

Время:
1. Построение кучи: O(n).
2. Извлечение элементов: O(n log n).
Итого: O(n log n).
*/

// Сортировка методом Shaker Sort
void shakerSort(vector<int>& arr) {
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

// Память и сложность Shaker Sort:
/*
Память:
1. Исходный массив: O(n).
2. Дополнительные переменные: O(1).
Итого: O(n).

Время:
1. Худший случай: O(n^2) (если массив сильно неупорядочен).
2. Лучший случай: O(n) (если массив уже отсортирован).
*/

int main() {
    // Пример для Bucket Sort
    vector<double> bucketArr = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    auto startBucket = chrono::high_resolution_clock::now();
    bucketSort(bucketArr);
    auto endBucket = chrono::high_resolution_clock::now();
    for (double num : bucketArr) {
        cout << num << " ";
    }
    cout << "\nВремя выполнения Bucket Sort: " 
         << chrono::duration_cast<chrono::microseconds>(endBucket - startBucket).count() << " микросекунд\n";

    // Пример для Heap Sort
    vector<int> heapArr = {4, 10, 3, 5, 1};
    auto startHeap = chrono::high_resolution_clock::now();
    heapSort(heapArr);
    auto endHeap = chrono::high_resolution_clock::now();
    for (int num : heapArr) {
        cout << num << " ";
    }
    cout << "\nВремя выполнения Heap Sort: " 
         << chrono::duration_cast<chrono::microseconds>(endHeap - startHeap).count() << " микросекунд\n";

    // Пример для Shaker Sort
    vector<int> shakerArr = {5, 3, 8, 6, 2, 7, 4, 1};
    auto startShaker = chrono::high_resolution_clock::now();
    shakerSort(shakerArr);
    auto endShaker = chrono::high_resolution_clock::now();
    for (int num : shakerArr) {
        cout << num << " ";
    }
    cout << "\nВремя выполнения Shaker Sort: " 
         << chrono::duration_cast<chrono::microseconds>(endShaker - startShaker).count() << " микросекунд\n";

    return 0;
}
