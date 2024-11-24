import random

# Parámetros del algoritmo genético
POPULATION_SIZE = 4 # mu
GENOME_LENGTH = 4
MUTATION_RATE = 0.01 # probabilidad de mutación
CROSSOVER_RATE = 0.9 # probabilidad de cruza
GENERATIONS = 1000
K_TOURNAMENT = 2

# Función de aptitud: conteo del número de ceros en el cromosoma
def fitness(genome):
    array = [(1, 1), (4, 3), (5, 4), (7, 5)]

    value = 0
    weight = 0

    # calcular
    for i, item in enumerate(genome):
        value = value + (item * array[i][0])
        weight = weight + (item * array[i][1])
    
    if (weight > 7):
        return 0
    else:
        return value

# Crear la población inicial de forma aleatoria
def create_population(size, length):
    return [[random.randint(0, 1) for _ in range(length)] for _ in range(size)]

# Selección de padres: selección de torneo k-ario
def tournament_selection(population, k=3):
    selected = random.sample(population, k)
    return max(selected, key=fitness)

# Cruza genética: cruza de un punto
def crossover(parent1, parent2, crossover_rate):
    if random.random() <= crossover_rate:
        if len(parent1) != len(parent2):
            raise ValueError("Genomes must be of the same length")
        point = random.randint(1, len(parent1) - 1)
        child1 = parent1[:point] + parent2[point:]
        child2 = parent2[:point] + parent1[point:]
        return child1, child2
    return parent1, parent2

# Mutación: mutación por bit-flip
def mutate(genome, mutation_rate):
    return [bit if random.random() > mutation_rate else 1 - bit for bit in genome]

# Algoritmo genético
def genetic_algorithm():
    population = create_population(POPULATION_SIZE, GENOME_LENGTH)

    for generation in range(GENERATIONS):
        new_population = []

        while len(new_population) < POPULATION_SIZE:
            # Aplicar la selección de padres
            parent1 = tournament_selection(population, k=K_TOURNAMENT)
            parent2 = tournament_selection(population, k=K_TOURNAMENT)

            # Aplicar la cruza y mutación genética
            child1, child2 = crossover(parent1, parent2, CROSSOVER_RATE)
            child1 = mutate(child1, MUTATION_RATE)
            child2 = mutate(child2, MUTATION_RATE)

            new_population.extend([child1, child2])

        # Trunca la población de hijos
        new_population = new_population[:POPULATION_SIZE]

        # Unir la población principal con la población de hijos
        population = population + new_population

        # Aplicar selección extintiva (mu + lambda)
        population = sorted(population, key=fitness, reverse=True)[:POPULATION_SIZE]

        # Desplegar el mejor cromosoma de la generación actual
        best_genome = population[0]
        print(f"Generation {generation + 1}: Best fitness = {fitness(best_genome)}, Genome = {best_genome}")

# Ejecutar el algoritmo genético
genetic_algorithm()
