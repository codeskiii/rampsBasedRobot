from pop import *

if __name__ == "__main__":
    best_robot = genetic_algorithm(pop_size=2_000, generations=100_000_000, mutation_rate=0.4)
    best_robot.predict()
    best_robot.translate_predictions()
    best_robot.calculate_fitness()