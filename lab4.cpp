#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Функция для подсчёта суммы отклонений в кластере
vector<vector<double>> costMatrix;

void computeCostMatrix(const vector<int>& arr) {
    int n = arr.size();
    costMatrix.assign(n, vector<double>(n, 0));
    
    for (int i = 0; i < n; ++i) {
        double sum = 0, mean = 0;
        for (int j = i; j < n; ++j) {
            sum += arr[j];
            mean = sum / (j - i + 1);
            double cost = 0;
            for (int k = i; k <= j; ++k) {
                cost += abs(arr[k] - mean);
            }
            costMatrix[i][j] = cost;
        }
    }
}

// Функция для разбиения массива на k кластеров
vector<vector<int>> clusterArray(const vector<int>& arr, int k) {
    int n = arr.size();
    computeCostMatrix(arr);
    
    vector<vector<double>> dp(k, vector<double>(n, numeric_limits<double>::max()));
    vector<vector<int>> split(k, vector<int>(n, -1));
    
    for (int j = 0; j < n; ++j) {
        dp[0][j] = costMatrix[0][j];
    }
    
    for (int clusters = 1; clusters < k; ++clusters) {
        for (int j = clusters; j < n; ++j) {
            for (int i = clusters - 1; i < j; ++i) {
                double cost = dp[clusters - 1][i] + costMatrix[i + 1][j];
                if (cost < dp[clusters][j]) {
                    dp[clusters][j] = cost;
                    split[clusters][j] = i;
                }
            }
        }
    }
    
    vector<vector<int>> clusters(k);
    int end = n - 1;
    for (int i = k - 1; i >= 0; --i) {
        int start = (i > 0) ? split[i][end] + 1 : 0;
        clusters[i].assign(arr.begin() + start, arr.begin() + end + 1);
        end = start - 1;
    }
    
    return clusters;
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
