import time
import random
import numpy as np
import matplotlib.pyplot as plt
import os

type_t = int

def counting_sort(array):
    max_val = max(array)
    size = len(array)
    count = [0] * (max_val + 1)
    output = [0] * size
    comparisons = 0

    # Store the count of each element
    for i in range(size):
        count[array[i]] += 1
        comparisons += 1  # Comparison when counting elements

    # Store the cumulative count
    for i in range(1, len(count)):
        count[i] += count[i - 1]
        comparisons += 1  # Comparison when building cumulative count

    # Place the elements in sorted order
    for i in range(size - 1, -1, -1):
        output[count[array[i]] - 1] = array[i]
        count[array[i]] -= 1

    # Copy the sorted elements back to the original array
    for i in range(size):
        array[i] = output[i]

    return comparisons, 0  # Counting sort doesn't use swaps

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
    comparisons, swaps = counting_sort(array)
    end_time = time.time()
    
    print(f"Counting Sort: {(end_time - start_time) * 1e6:.2f} us")
    
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
            plt.title(f'Counting Sort => {metric.capitalize()} por Entrada ({data_type.__name__})')
            plt.legend()
            plt.grid(True)

            # Salvar o gráfico na pasta
            plt.savefig(os.path.join(output_dir, f'counting_sort_{metric}_{data_type.__name__}.png'))
            plt.close()

if __name__ == "__main__":
    run_tests()
