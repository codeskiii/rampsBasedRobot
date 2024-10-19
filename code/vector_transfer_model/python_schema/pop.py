from random import uniform
import random
from object import *

def genetic_algorithm(pop_size: int, generations: int, mutation_rate: float):
    mutation_rate: float = 0.01
    mutation_strength: float = 0.3
    neuron_existance_mutation_rate: float = 0.001
    layer_existance_mutation_rate: float = 0.0001
    add_neuron_rate: float = 0.001
    add_layer_rate: float = 0.0001

    # Initialize population
    population = [ChildRobot() for _ in range(pop_size)]
    
    for generation in range(generations):
        for robot in population:
            robot.predict_network()
            robot.translate_predictions()
            robot.calculate_fitness()
        
        # Sort population by fitness (best first)
        population.sort(key=lambda r: r.fitness, reverse=True)
        
        # Print best fitness in this generation
        print(f"Generation {generation + 1}: Best fitness = {population[0].fitness}")

        # Create new population
        new_population = population[:pop_size // 2]

        # Generate new offspring
        while len(new_population) < pop_size:
            parent_1 = population[random.randint(0, int(len(population) * 0.9))]
            parent_2 = population[random.randint(0, int(len(population) * 0.9))]
            child = ChildRobot(parents=[parent_1, parent_2])

            mutation_rate *= 1.0000001
            mutation_strength *= 1.0000001
            neuron_existance_mutation_rate *= 1.0000001
            layer_existance_mutation_rate *= 1.0000001
            add_neuron_rate *= 1.0000001
            add_layer_rate *= 1.0000001

            child.mutate(mutation_rate,
                        mutation_strength,
                        neuron_existance_mutation_rate,
                        layer_existance_mutation_rate,
                        add_neuron_rate,
                        add_layer_rate)
            
            new_population.append(child)

        population = new_population

    # Return the best solution found
    return population[0]