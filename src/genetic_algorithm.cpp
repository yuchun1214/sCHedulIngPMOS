#include "include/genetic_algorithm.h"

genetic_algorithm_t::genetic_algorithm_t(int gene_size,
                                         int population_size,
                                         double initial_selection_rate,
                                         double mutation_rate,
                                         double crossover_rate)
{
    _population_size = population_size;
    _gene_size = gene_size;
    _initial_selection_rate = initial_selection_rate;
    _mutation_rate = mutation_rate;
    _crossover_rate = crossover_rate;
}

void genetic_algorithm_t::initializePopulation()
{
    for (int i = 0; i < _population_size; i++) {
        chromosome_t *chromosome = new chromosome_t(_gene_size);
        _populations.push_back(chromosome);
    }
}

void genetic_algorithm_t::geneticAlgorithm(int iterations)
{
    initializePopulation();
    for (int i = 0; i < iterations; i++) {
    }
}