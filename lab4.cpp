#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

// функция для подсчета суммы отклонений в кластере
double calculateClusterCost(const vector<int>& arr, int start, int end) {
    double mean = 0;
    for (int i = start; i <= end; ++i) {
        mean += arr[i];
    }
    mean /= (end - start + 1); // среднее значение кластера

    double cost = 0;
    for (int i = start; i <= end; ++i) {
        cost += abs(arr[i] - mean); // сумма модулей отклонений
    }
    return cost;
}

// рекурсивная функция для поиска оптимального разбиения
void findOptimalClustering(const vector<int>& arr, int k, int start, vector<int>& currentCluster, vector<vector<int>>& bestClusters, double& minCost) {
    if (k == 1) {
        // базовый случай: один кластер от start до конца массива
        double cost = calculateClusterCost(arr, start, arr.size() - 1);
        if (cost < minCost) {
            minCost = cost;
            bestClusters.clear();
            bestClusters.push_back(vector<int>(arr.begin() + start, arr.end()));
        }
        return;
    }

    // перебираем все возможные позиции разделения кластера
    for (int i = start; i < arr.size() - (k - 1); ++i) {
        // добавляем текущий кластер
        for (int j = start; j <= i; ++j) {
            currentCluster.push_back(arr[j]);
        }

        // рекурсивно ищем разбиение для оставшихся кластеров
        vector<int> nextCluster;
        findOptimalClustering(arr, k - 1, i + 1, nextCluster, bestClusters, minCost);

        // удаляем текущий кластер
        currentCluster.clear();
    }
}

// основная функция кластеризации
vector<vector<int>> clusterArray(const vector<int>& arr, int k) {
    vector<vector<int>> bestClusters;
    double minCost = numeric_limits<double>::max();
    vector<int> currentCluster;

    findOptimalClustering(arr, k, 0, currentCluster, bestClusters, minCost);

    return bestClusters;
}

int main() {
    vector<int> arr = {1, -2, 3, 4, -5, 6};
    int k = 3;

    vector<vector<int>> clusters = clusterArray(arr, k);

    cout << "Кластеры:" << endl;
    for (size_t i = 0; i < clusters.size(); ++i) {
        cout << "Кластер " << i + 1 << ": ";
        for (int num : clusters[i]) {
            cout << num << " ";
        }
        cout << endl;
    }

    /*
    Время:
    calculateClusterCost: O(n) для вычисления среднего и суммы отклонений.
    findOptimalClustering: O(n * k) из-за перебора всех возможных разбиений.
    Итого: O(n^2 * k) в худшем случае из-за рекурсивного перебора.

    Память:
    Используется O(n) для хранения текущего кластера и O(n) для хранения лучших кластеров.
    Итого: O(n).

    Итоговая асимптотика:
    - calculateClusterCost: O(n) на каждое вычисление
    - заполнение dp: O(k * n^2), так как перебираем все разбиения
    - восстановление разбиения: O(k), так как идем по split
    Итого: O(k * n^2), что гораздо быстрее рекурсивного O(n^k)
    */

    return 0;
}
