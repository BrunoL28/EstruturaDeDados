import time
import random
import numpy as np
import matplotlib.pyplot as plt
import os

type_t = int

def swap(array, i, j):
    array[i], array[j] = array[j], array[i]

def partition(array, low, high):
    comparisons = 0
    swaps = 0
    pivot = array[low + (high - low) // 2]
    swap(array, low, low + (high - low) // 2)
    swaps += 1
    i = low + 1
    j = high
    
    while True:
        while i <= j and array[i] <= pivot:
            comparisons += 1
            i += 1
        while i <= j and array[j] > pivot:
            comparisons += 1
            j -= 1
        if i >= j:
            break
        swap(array, i, j)
        swaps += 1
    
    swap(array, low, j)
    swaps += 1
    return j, comparisons, swaps

def _quick_sort(array, low, high):
    total_comparisons = 0
    total_swaps = 0
    if low < high:
        p, comparisons, swaps = partition(array, low, high)
        total_comparisons += comparisons
        total_swaps += swaps
        comparisons_left, swaps_left = _quick_sort(array, low, p - 1)
        comparisons_right, swaps_right = _quick_sort(array, p + 1, high)
        total_comparisons += comparisons_left + comparisons_right
        total_swaps += swaps_left + swaps_right
    return total_comparisons, total_swaps

def quick_sort(array):
    return _quick_sort(array, 0, len(array) - 1)

def print_array(array):
    print("[", " ".join(map(str, array)), "]")

def initialize_array(size, sorting_type, data_type):
    array = [0] * size
    if data_type == int:
        if sorting_type == 'ordenado':
            for i in range(size):
                array[i] = i
        elif sorting_type == 'desordenado':
            for i in range(size):
                array[i] = random.randint(0, size)
        elif sorting_type == 'inversamente_ordenado':
            for i in range(size):
                array[i] = size - i - 1
    elif data_type == float:
        if sorting_type == 'ordenado':
            for i in range(size):
                array[i] = float(i)
        elif sorting_type == 'desordenado':
            for i in range(size):
                array[i] = random.uniform(0, size)
        elif sorting_type == 'inversamente_ordenado':
            for i in range(size):
                array[i] = float(size - i - 1)
    elif data_type == str:
        alphabet = 'abcdefghijklmnopqrstuvwxyz'
        if sorting_type == 'ordenado':
            array = [''.join(random.sample(alphabet, 5)) for _ in range(size)]
            array.sort()
        elif sorting_type == 'desordenado':
            array = [''.join(random.sample(alphabet, 5)) for _ in range(size)]
        elif sorting_type == 'inversamente_ordenado':
            array = [''.join(random.sample(alphabet, 5)) for _ in range(size)]
            array.sort(reverse=True)
    return array

def is_sorted(array):
    for i in range(1, len(array)):
        if array[i] < array[i - 1]:
            return False
    return True

def test(size, sorting_type, data_type, print_array):
    array = initialize_array(size, sorting_type, data_type)
    
    if print_array:
        print("Array inicial:")
        print_array(array)
    
    start_time = time.time()
    comparisons, swaps = quick_sort(array)
    end_time = time.time()
    
    print(f"Quick Sort ({data_type.__name__}): {(end_time - start_time) * 1e6:.2f} us")
    
    if print_array:
        print("Array final:")
        print_array(array)
        
    assert is_sorted(array)
    
    return (end_time - start_time) * 1e6, comparisons, swaps

def run_tests():
    sizes = [10, 100, 500, 1000, 5000, 10000, 20000, 50000]
    types = ['ordenado', 'desordenado', 'inversamente_ordenado']
    data_types = [int]
    
    results = {}
    
    for data_type in data_types:
        results[str(data_type)] = {}
        for sorting_type in types:
            results[str(data_type)][sorting_type] = {'tempos': [], 'comparacoes': [], 'trocas': []}
            for size in sizes:
                time_spent, comparisons, swaps = test(size, sorting_type, data_type, False)
                results[str(data_type)][sorting_type]['tempos'].append(time_spent)
                results[str(data_type)][sorting_type]['comparacoes'].append(comparisons)
                results[str(data_type)][sorting_type]['trocas'].append(swaps)

    # Criar a pasta para armazenar os gráficos
    output_dir = "graficos"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for data_type in data_types:
        for metric in ['tempos', 'comparacoes', 'trocas']:
            plt.figure(figsize=(10, 6))
            for sorting_type in types:
                plt.plot(sizes, results[str(data_type)][sorting_type][metric], label=sorting_type)
            plt.xlabel('Tamanho do Vetor')
            plt.ylabel(metric.capitalize())
            plt.title(f'Quick Sort => {metric.capitalize()} por Entrada ({data_type.__name__})')
            plt.legend()
            plt.grid(True)

            # Salvar o gráfico na pasta
            plt.savefig(os.path.join(output_dir, f'quick_sort_{metric}_{data_type.__name__}.png'))
            plt.close()

if __name__ == "__main__":
    run_tests()
