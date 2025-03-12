// бабл сорт, расческа и подсчет

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// пузырьковая сортировка
// O(N^2) в худшем и среднем случае, O(N) в лучшем случае (если массив уже отсортирован)
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false; 
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]); // Меняем их местами
                swapped = true;
            }
        }
        if (!swapped) break; // если обменов не было значит массив уже отсортирован
    }
}

// Сортировка расческой (comb sort)
// O(N^2) в худшем случае, O(N log N) в среднем случае
void combSort(vector<int>& arr) {
    int n = arr.size();
    int gap = n; // изначальный размер "расчески"
    bool swapped = true; // флаг для отслеживания обменов

    while (gap > 1 || swapped) {
        gap = max(1, (gap * 10) / 13); // уменьшаем интервал (оптимальный коэффициент — 1.3)
        swapped = false; // сброс флага

        for (int i = 0; i < n - gap; ++i) { // Проходим по массиву с текущим интервалом
            if (arr[i] > arr[i + gap]) { // если элементы не в порядке,
                swap(arr[i], arr[i + gap]); // то меняем их местами
                swapped = true;
            }
        }
    }
}

// Ссртировка подсчетом (Counting Sort)
// асимптотика: O(N + K) где K — диапазон значений (max - min + 1)
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0); // массив для подсчета частот

    // подсчет частоты каждого элемента
    for (int num : arr) {
        count[num - minVal]++; // увеличение счетчика
    }

    // Восстанавливаем отсортированный массив
    int index = 0;
    for (int i = 0; i < range; ++i) {
        while (count[i] > 0) { // пока есть элементы с текущим значением
            arr[index++] = i + minVal; // добавляем их в исходный массив
            count[i]--;
        }
    }
}

// Функция для вывода массива
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    cout << "Исходный массив: ";
    printArray(arr);

    vector<int> arr1 = arr;
    bubbleSort(arr1);
    cout << "после пузырьковой сортировки: ";
    printArray(arr1);

    vector<int> arr2 = arr;
    combSort(arr2);
    cout << "после расчески: ";
    printArray(arr2);

    vector<int> arr3 = arr;
    countingSort(arr3);
    cout << "после сортировки подсчетом: ";
    printArray(arr3);

    return 0;
}
