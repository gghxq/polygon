#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

// Функция для подсчета суммы отклонений в кластере
double calculateClusterCost(const vector<int>& arr, int start, int end) {
    double mean = 0;
    for (int i = start; i <= end; ++i) {
        mean += arr[i];
    }
    mean /= (end - start + 1); // Среднее значение кластера

    double cost = 0;
    for (int i = start; i <= end; ++i) {
        cost += abs(arr[i] - mean); // Сумма модулей отклонений
    }
    return cost;
}

// Рекурсивная функция для полного перебора кластеров
double findOptimalClustering(const vector<int>& arr, int k, int start, vector<vector<double>>& memo) {
    if (k == 1) {
        // Базовый случай: один кластер от start до конца массива
        return calculateClusterCost(arr, start, arr.size() - 1);
    }
    if (memo[start][k] != -1) {
        // Используем мемоизацию для предотвращения повторных вычислений
        return memo[start][k];
    }

    double minCost = numeric_limits<double>::max(); // Инициализируем минимальную стоимость большим значением

    // Перебираем все возможные позиции разделения кластера
    for (int i = start; i < arr.size() - (k - 1); ++i) {
        double currentCost = calculateClusterCost(arr, start, i) +
                             findOptimalClustering(arr, k - 1, i + 1, memo);
        minCost = min(minCost, currentCost);
    }

    return memo[start][k] = minCost; // Сохраняем результат в таблицу мемоизации
}

// Основная функция кластеризации
// Параметры:
// arr - массив чисел, k - количество кластеров
// Возвращает минимальную сумму отклонений

double clusterArray(const vector<int>& arr, int k) {
    int n = arr.size();

    // Таблица мемоизации размером O(N * K)
    vector<vector<double>> memo(n, vector<double>(k + 1, -1)); 

    return findOptimalClustering(arr, k, 0, memo);
}

int main() {
    // Пример ввода
    vector<int> arr = {1, -2, 3, 4, -5, 6}; // Массив чисел
    int k = 3; // Количество кластеров

    // Вызов алгоритма кластеризации
    double result = clusterArray(arr, k);

    // Вывод результата
    cout << "Минимальная сумма отклонений: " << result << endl;

    return 0;
}

/*
Память:
1. memo (N * (K + 1)): каждый double занимает 8 байт. Пример: N = 6, K = 3 -> 6 * 4 * 8 = 192 байта.
2. Локальные переменные (на вызов): 36 байт (4 double и int).

В сумме:
- memo: 192 байта.
- Переменные: 36 байт.
Итого: ~228 байт.

Время:
1. Перебор всех разбиений O(2^N).
2. Мемоизация ускоряет, но не убирает O(2^N).

Ограничения:
1. Максимум 25 элементов в массиве.
2. K намного меньше N.
*/
