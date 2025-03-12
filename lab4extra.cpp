#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    vector<set<int>> sets = {{1, 2}, {2, 3}, {3, 4}}; // заданные множества
    set<int> universe = {1, 2, 3};                  // множество которое нужно покрыть

    int n = sets.size(); // количество подмножеств
    vector<int> best_cover; // оптимальное покрытие

    // перебираем все возможные комбинации подмножеств — их 2^n, сложность O(2^n)
    for (int mask = 0; mask < (1 << n); ++mask) {
        set<int> covered;       // множество покрытых элементов
        vector<int> selected;   // индексы выбранных подмножеств

        // проверяем, какие множества включены в текущую комбинацию — O(n)
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // Если i-е множество включено в комбинацию
                selected.push_back(i);
                covered.insert(sets[i].begin(), sets[i].end()); // добавляем элементы множества в покрытие — O(k), где k — размер множества
            }
        }

        // проверяем, покрыли ли мы все элементы universe — O(u), где u — размер universe
        if (includes(covered.begin(), covered.end(), universe.begin(), universe.end())) {
            // если покрытие полное и оно меньше текущего оптимального по размеру — обновляем
            if (best_cover.empty() || selected.size() < best_cover.size()) {
                best_cover = selected;
            }
        }
    }

    // выводим минимальное покрывающее подмножество
    cout << "[";
    for (int i = 0; i < best_cover.size(); ++i) {
        int idx = best_cover[i];
        cout << "{";
        for (auto it = sets[idx].begin(); it != sets[idx].end(); ++it) {
            if (it != sets[idx].begin()) cout << ", ";
            cout << *it;
        }
        cout << "}";
        if (i < best_cover.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
