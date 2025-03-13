import numpy as np


def has_duplicates(arr):
    # Используем numpy.unique для поиска уникальных элементов
    unique_elements = np.unique(arr)
    return len(unique_elements) != len(arr)


testArray = np.array([1, 2, 3, 4, 5, 2])  # Массив с дубликатом (число 2)
print(has_duplicates(testArray))  # Вывод: True

testArray = np.array([1, 2, 3, 4, 5])  # Массив без дубликатов
print(has_duplicates(testArray))  # Вывод: False
