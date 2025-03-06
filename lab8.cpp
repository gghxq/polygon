#include <iostream>
#include <vector>

using namespace std;

vector<int> findIsolatedNodes(const vector<vector<int>>& adjacencyMatrix) {
    int n = adjacencyMatrix.size();
    vector<int> isolatedNodes; // dектор для хранения номеров изолированных элементов

    for (int i = 0; i < n; ++i) {
        bool isIsolated = true; // индикатор для проверки изолированности элемента

        // строка i
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                isIsolated = false; // если есть связь, значит элемент не изолирован
                break;
            }
        }

        // если строка i содержит только нули, проверяем столбец j
        if (isIsolated) {
            for (int j = 0; j < n; ++j) {
                if (adjacencyMatrix[j][i] == 1) {
                    isIsolated = false; // если есть связь в столбце, то элемент не изолирован
                    break;
                }
            }
        }

        // если элемент изолирован, добавляем его номер в результат
        if (isIsolated) {
            isolatedNodes.push_back(i);
        }
    }

    return isolatedNodes;
}
