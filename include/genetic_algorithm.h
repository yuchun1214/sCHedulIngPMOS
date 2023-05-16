#ifndef __GA_H__
#define __GA_H__

#include <vector>

#include "forward_declaration.h"
#include "include/chromosome.h"
#include "include/job_base.h"

class genetic_algorithm_t
{
protected:
    /// @brief 
    int _population_size, _gene_size;
    double _initial_selection_rate, _mutation_rate, _crossover_rate;

    std::vector<chromosome_t *> _populations;

public:
    genetic_algorithm_t(
                        int gene_size,
                        int population_size,
                        double initial_selection_rate,
                        double mutation_rate,
                        double crossover_rate);
    void geneticAlgorithm(int iterations);
    void initializePopulation();
};

#endif