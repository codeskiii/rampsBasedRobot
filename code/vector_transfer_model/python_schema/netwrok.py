from random import *
import random
import math
import json

NETWORK_START_ARCHITECTURE: list[int] = [3, 48, 96, 128, 256, 128, 96, 6]
RANDOM_WEIGHT_MAX_MIN: float = 1.2

def relu(x: float) -> float:
    return max(0, x)

class NeuralNetwork:
    def __init__(self, parents: list = None) -> None:
        self.network: list[list[float]] = []
        if parents is None:
            for i in range(1, len(NETWORK_START_ARCHITECTURE)):
                layer = [
                    [uniform(-RANDOM_WEIGHT_MAX_MIN, RANDOM_WEIGHT_MAX_MIN) for _ in range(NETWORK_START_ARCHITECTURE[i-1])]
                    for _ in range(NETWORK_START_ARCHITECTURE[i])
                ]
                self.network.append(layer)
        else:
            self.crosover(parents)

    def crosover(self, parents) -> None:
        network = []
        for i in range(len(self.network)):
            child_layer = []
            for j in range(len(self.network[i])):
                parent_1_weights = parents[0].network[i][j]
                if random.uniform(0, 1) > 0.4:
                    parent_2_weights = parents[1].network[i][j]
                else:
                    parent_2_weights = parent_1_weights

                child_weight = (parent_1_weights + parent_2_weights) / 2
                child_layer.append(child_weight)
            network.append(child_layer)
        self.network = network

    def _group_preds(self, c: list[float]) -> list[list[float]]:
        grouped = [c[i:i+2] for i in range(0, len(c), 2)]
        return grouped

    def predict(self, inputs: list[float]) -> list[float]:
        current_input = inputs
        for layer in self.network:
            next_input = []
            for neuron_weights in layer:
                weighted_sum = sum(w * i for w, i in zip(neuron_weights, current_input))
                neuron_output = relu(weighted_sum)
                next_input.append(neuron_output)
            current_input = next_input
        return self._group_preds(current_input)
    
    def mutate(self,mutation_rate: float, 
                    mutation_strength: float,
                    neuron_existance_mutation_rate: float,
                    layer_existance_mutation_rate: float,
                    add_neuron_rate: float,
                    add_layer_rate: float) -> None:

            # Usuwanie lub mutowanie istniejących neuronów i warstw
            for i in range(len(self.network)):
                if random.random() < layer_existance_mutation_rate:
                    self.network[i] = []
                else:
                    for j in range(len(self.network[i])):
                        if random.random() < neuron_existance_mutation_rate:
                            self.network[i][j] = []
                        else:
                            for k in range(len(self.network[i][j])):
                                if random.random() < mutation_rate:
                                    mutation = random.uniform(-mutation_strength, mutation_strength)
                                    self.network[i][j][k] += mutation

            # Druga runda mutacji dla wzmocnienia efektu
            for i in range(len(self.network)):
                for j in range(len(self.network[i])):
                    for k in range(len(self.network[i][j])):
                        if random.random() < mutation_rate:
                            mutation = random.uniform(-mutation_strength, mutation_strength)
                            self.network[i][j][k] += mutation

            # Dodawanie nowych neuronów
            for i in range(len(self.network)):
                if random.random() < add_neuron_rate:  # Sprawdź, czy dodajemy neuron do warstwy
                    if len(self.network[i]) > 0:
                        new_neuron = [random.uniform(-1, 1) for _ in range(len(self.network[i][0]))]
                    else:
                        # Zakładamy pewną liczbę wag, jeśli warstwa nie ma neuronów
                        new_neuron = [random.uniform(-1, 1) for _ in range(10)]
                    self.network[i].append(new_neuron)

            # Dodawanie nowych warstw
            if random.random() < add_layer_rate:
                if len(self.network) > 0 and len(self.network[0]) > 0:
                    num_weights = len(self.network[0][0])  # Liczba wag na neuron oparta na pierwszej warstwie
                else:
                    num_weights = 10  # Domyślna liczba wag, jeśli sieć jest pusta lub niekompletna

                new_layer_size = random.randint(1, 10)  # Losowa liczba neuronów w nowej warstwie
                new_layer = [[random.uniform(-1, 1) for _ in range(num_weights)] for _ in range(new_layer_size)]
                self.network.insert(random.randint(0, len(self.network)), new_layer)  # Wstawiamy nową warstwę w losowym miejscu
                
    def save_this_shit(self, filename) -> None:
        structure = [len(row) for row in self.network]
        
        to_save = {
            'structure': structure,
            'weights': self.network
            }
        