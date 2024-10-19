from random import *
import random
from math import sin, cos, radians
from netwrok import *

# Constants
#POLYNOMIAL_LENGTH: int = 12
RANDOM_WAGE_MAX_MIN: float = 1.2
DIMENSIONS: int = 3
JOINTS_NUM: int = 3
CORDINATES_PER_JOINT: int = 2

L1: float = 7.0
L2: float = 5.0

class ChildRobot:
    def __init__(self,
                  #wages: list[list[float]] = None,
                  parents: list = None) -> None:
        self.goal: list[float] = [random.uniform(-10, 10) for _ in range(DIMENSIONS)]
        
        #if wages:
        #    self.wages: list[list[float]] = wages
        #else:
        #    self.wages: list[list[float]] = [[random.uniform(-1.2, 1.2).real for _ in range(POLYNOMIAL_LENGTH)] for _ in range(6)]
        if parents:
            self.network: NeuralNetwork = NeuralNetwork(parents=parents) 
        else:
            self.network: NeuralNetwork = NeuralNetwork()

        self.predictions: list[list[float]] = []
        self.translated_predictions: list[float] = []
        self.fitness: float = 0.0

    #def predict_polynomial(self) -> None:
    #    self.predictions.clear()
    #    for j in range(JOINTS_NUM):
    #        _joint = []
    #        for _ in range(CORDINATES_PER_JOINT):
    #            current_theta: float = 0.0
    #            for d in range(DIMENSIONS):
    #                current_theta += sum([self.goal[d] ** w for w in self.wages[j]])
    #            _joint.append(current_theta.real)
    #        self.predictions.append(_joint)

    def predict_network(self) -> None:
        self.predictions = self.network.predict(inputs=self.goal)

    def mutate(self,
                mutation_rate,
                mutation_strength,
                neuron_existance_mutation_rate,
                layer_existance_mutation_rate,
                add_neuron_rate,
                add_layer_rate) -> None:
        
        #for i in range(len(self.wages)):
        #    if random.random() < mutation_rate:
        #        for j in range(len(self.wages[i])):
        #            mutation = random.uniform(-0.1, 0.1)
        #            self.wages[i][j] = (self.wages[i][j] + mutation).real
        self.network.mutate(mutation_rate,
                            mutation_strength,
                            neuron_existance_mutation_rate,
                            layer_existance_mutation_rate,
                            add_neuron_rate,
                            add_layer_rate)

    def calculate_fitness(self) -> None:
        if not self.translated_predictions:
            return
        
        x, y, z = self.translated_predictions[-1]  # Get the last prediction
        distance = ((self.goal[0] - x) ** 2 + (self.goal[1] - y) ** 2 + (self.goal[2] - z) ** 2) ** 0.5
        self.fitness = 1 / (1 + distance)  # Higher fitness for closer distances

    def translate_predictions(self) -> None:
        self.translated_predictions.clear()  # Clear previous translations
        for pred_array in self.predictions:
            if len(pred_array) < 2:  # Ensure we have enough angles
                continue
            
            theta_1 = (pred_array[0])  # Convert to radians
            theta_2 = (pred_array[1])  # Convert to radians
            
            # Calculate coordinates
            y = sin(theta_2) * L1  # Length along y direction based on theta_2
            z = sin(theta_1) * L2  # Length along z direction based on theta_1
            x = cos(theta_1) * (L1**2 - y**2)**0.5  # Length along x direction, derived from the geometry

            # Append the computed Cartesian coordinates
            self.translated_predictions.append([x, y, z])