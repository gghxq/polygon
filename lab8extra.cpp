#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 1. Полный перебор (рекурсия)
int knapsackRecursive(const vector<int>& weights, const vector<int>& values, int capacity, int n) {
    // если нет предметов или рюкзак заполнен
    if (n == 0 || capacity == 0) {
        return 0;
    }

    // если вес текущего предмета больше вместимости рюкзака, то скип
    if (weights[n - 1] > capacity) {
        return knapsackRecursive(weights, values, capacity, n - 1);
    }

    // Возвращаем максимум из двух случаев:
    // 1. текущий предмет включен в рюкзак
    // 2. текущий предмет не включен в рюкзак
    return max(
        values[n - 1] + knapsackRecursive(weights, values, capacity - weights[n - 1], n - 1),
        knapsackRecursive(weights, values, capacity, n - 1)
    );
}

// 2. жадный
int knapsackGreedy(vector<int>& weights, vector<int>& values, int capacity) {
    int n = weights.size();
    vector<pair<double, int>> ratio; // "плотность ценности"

    // заполнение вектора соотношений
    for (int i = 0; i < n; ++i) {
        ratio.push_back({(double)values[i] / weights[i], i});
    }

    // сортировка от более ценного к менее
    sort(ratio.rbegin(), ratio.rend());

    int totalValue = 0;
    int remainingCapacity = capacity;

    // добавление предмеитов
    for (const auto& r : ratio) {
        int idx = r.second;
        if (weights[idx] <= remainingCapacity) {
            totalValue += values[idx];
            remainingCapacity -= weights[idx];
        }
    }

    return totalValue;
}

// 3. динамическое программирование
int knapsackDP(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0)); // таблица

    // заполнение таблицы
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {

    vector<int> weights = {10, 20, 30};
    vector<int> values = {60, 100, 120};
    int capacity = 50;
    int n = weights.size();

    // 1. Полный перебор
    int resultRecursive = knapsackRecursive(weights, values, capacity, n);
    cout << "максимальная стоимость (полный перебор): " << resultRecursive << endl;

    // 2. Жадный алгоритм
    int resultGreedy = knapsackGreedy(weights, values, capacity);
    cout << "максимальная стоимость (жадник): " << resultGreedy << endl;

    // 3. Динамическое программирование
    int resultDP = knapsackDP(weights, values, capacity);
    cout << "максимальная стоимость (ДП): " << resultDP << endl;

    return 0;
}
