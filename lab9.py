import numpy as np

def find_longest_sequence(arr):
    if len(arr) == 0:
        return 0  # если массив пустой, то длина последовательности 0

    # преобразуем список в массив numpy
    arr = np.array(arr)

    # разница между соседними элементами
    diff = np.diff(arr)

    # индексы где элементы меняются
    change_indices = np.where(diff != 0)[0] + 1

    # начало и конец массива
    change_indices = np.concatenate(([0], change_indices, [len(arr)]))

    # находим длины последовательностей
    lengths = np.diff(change_indices)

    # ответ
    return np.max(lengths)
