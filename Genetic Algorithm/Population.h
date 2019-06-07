//
//  Population.h
//  Genetic Algorithm
//
//  Created by Bharddwaj Vemulapalli on 6/6/19.
//  Copyright © 2019 Bharddwaj Vemulapalli. All rights reserved.
//

#ifndef Population_h
#define Population_h
#include <random>
#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <map>
#include "Chromosome.hpp"
class Population{
    
public:
    //characters you can use in your phrase
    std::array<char, 29> characters = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x',
        'y','z',' ', '?', '.'};
    std::vector<Chromosome> members;
    long long sumOfAllFitness; //help with normalizing fitness and selecting which chromosomes reproduce more
    Population(std::string sent,int popsize);
    
    int getNumPopulation(void);
    void calcAllFitness(void);
    bool allChromosomeLengths(void);
    int getMaxFitness(void);
    std::string getMostFitMember(void);
    void getAllGenes(void);
    Chromosome crossOver2(Chromosome parentOne,Chromosome parentTwo,int numChanges);
    Chromosome crossOver3(Chromosome parentOne,Chromosome parentTwo);
    void mutation(int mutationPercent,Chromosome &child,int numChanges);
    void deletion(int threshold);
    int minFitness(void);
    std::array<int, 2> max_min_fitness(void);
    
    
    void generateChildren3(int numChildren,int mutationPercent, int numMutationChanges,int numCrossoverChanges);
    
    
    
};

#endif /* Population_h */
