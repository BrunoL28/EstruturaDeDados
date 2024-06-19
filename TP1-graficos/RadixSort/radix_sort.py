import time
import random
import numpy as np
import matplotlib.pyplot as plt
import os

type_t = int

def get_max(array):
    max_val = array[0]
    for num in array:
        if num > max_val:
            max_val = num
    return max_val

def count_sort(array, exp):
    n = len(array)
    output = [0] * n
    count = [0] * 10
    swaps = 0
    comparisons = 0

    for i in range(n):
        index = array[i] // exp
        count[index % 10] += 1

    for i in range(1, 10):
        count[i] += count[i - 1]

    i = n - 1
    while i >= 0:
        index = array[i] // exp
        output[count[index % 10] - 1] = array[i]
        count[index % 10] -= 1
        swaps += 1
        i -= 1

    for i in range(n):
        array[i] = output[i]
        comparisons += 1

    return comparisons, swaps

def radix_sort(array):
    max_val = get_max(array)
    total_comparisons = 0
    total_swaps = 0
    exp = 1

    while max_val // exp > 0:
        comparisons, swaps = count_sort(array, exp)
        total_comparisons += comparisons
        total_swaps += swaps
        exp *= 10

    return total_comparisons, total_swaps

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
    comparisons, swaps = radix_sort(array)
    end_time = time.time()
    
    print(f"Radix Sort ({data_type.__name__}): {(end_time - start_time) * 1e6:.2f} us")
    
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
            plt.title(f'Radix Sort => {metric.capitalize()} por Entrada ({data_type.__name__})')
            plt.legend()
            plt.grid(True)

            plt.savefig(os.path.join(output_dir, f'radix_sort_{metric}_{data_type.__name__}.png'))
            plt.close()

if __name__ == "__main__":
    run_tests()
