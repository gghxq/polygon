class Solution {
public:
    int uniquePaths(int m, int n) {
        // подсчет памяти:
        // - используем одномерный вектор dp размером n.
        // - память: O(n), так как храним только одну строку таблицы DP.

        // асимптотика:
        // - временная сложность: O(m * n), так как заполняем таблицу DP.
        // - пространственная сложность: O(n), так как используем одномерный массив.

        // инициализация вектора dp:
        // - dp[j] хранит количество путей до клетки (текущая строка, j).
        // - изначально все элементы равны 1, так как в первой строке только один путь (вправо).
        vector<int> dp(n, 1);

        // заполнение таблицы DP:
        // - для каждой строки (начиная со второй) обновляем значения dp[j].
        // - dp[j] = dp[j] (количество путей сверху) + dp[j - 1] (количество путей слева).
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[j] += dp[j - 1];
            }
        }

        // возвращаем количество путей до конечной клетки (m-1, n-1):
        // - dp[n - 1] содержит результат для последней клетки.
        return dp[n - 1];
    }
};
