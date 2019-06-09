//
//  main.cpp
//  Genetic Algorithm
//
//  Created by Bharddwaj Vemulapalli on 6/2/19.
//  Copyright © 2019 Bharddwaj. All rights reserved.
//
#include <random>
#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <map>
#include "Population.h"
//characters you can use in your phrase


//for some reason comma in the sentence does not work???

int main(int argc, const char * argv[]) {
    
    /*
     START
     Generate the initial population
     Compute fitness
     REPEAT
     Selection
     Crossover
     Mutation
     Compute fitness
     UNTIL population has converged
     STOP
     */
    
    
    
    std::string sentence = "to be or not to be, that is the real question? i wonder how good this algorithm really is though, lets test it out a bit.?!";
    
    //std::cout << "Enter sentence that you wish the algorithm to guess " << '\n';
    //std::getline(std::cin,sentence) ;
    
    int popsize = 500;
    int mutationPercent = 25;
    int numMutationChanges = 1;
    int numCrossoverChanges = sentence.size()/2;
    int numChildren = 100; //used for generateChildren()
    int count = 0;
    int threshold = sentence.size();
    Population p(sentence,popsize);
    int numPopulation = p.getNumPopulation();
    p.getAllGenes();
    int stagnationCounter = 0;
    std::array<int,2> max_min = p.max_min_fitness();
    
    int maxFitness = max_min[0];
    int minFitness = max_min[1];
    if (p.allChromosomeLengths()) {
        std::cout << "hello world" << '\n';
    }
    p.calcAllFitness();
    
    std::cout << "Max Fitness " <<maxFitness << '\n';
    std::cout << "Min Fitness " <<minFitness << '\n';
    //p.deletion(0);
    
    
   /*
     //this was me checking to see whether the mutation function was working
    std::string one = p.members[0].getGenes();
    std::string two = p.members[0].getGenes();
    int mutCount = 0;
    while (one == two) {
        std::cout << one << '\n';
        p.mutation(mutationPercent, p.members[0], numMutationChanges);
        two = p.members[0].getGenes();
        std::cout << two << '\n';
        mutCount++;
    }
    std::cout << mutCount << '\n'; */
    /*
     //this was me checking to see whether crossover3 works which it does
    Chromosome child = p.crossOver3(p.members[0], p.members[1]);
    std::cout <<p.members[0].getGenes() << '\n';
    std::cout <<p.members[1].getGenes() << '\n';
    std::cout <<child.getGenes() << '\n';
     */
    /*
     //checking to see if the stagnation worked and i fixed my mistake i think
    for (int i = 0; i < numPopulation; i++) {
        p.mutation(60, p.members[i], threshold - maxFitness); //doesn't rlly work at the moment
        
    }
    p.calcAllFitness();
    max_min = p.max_min_fitness();
    maxFitness = max_min[0];
    minFitness = max_min[1];
    std::cout << "Max Fitness " <<maxFitness << '\n';
    std::cout << "Min Fitness " <<minFitness << '\n';
    */
   /////////////////////////////////////////////////////
    
     //this is for CrossOver2
    int prevFitness = maxFitness;
    while(maxFitness != threshold*threshold ) {
        
         p.generateChildren3(numChildren, mutationPercent, numMutationChanges, numCrossoverChanges);
        
        max_min = p.max_min_fitness();
        maxFitness = max_min[0];
        minFitness = max_min[1];
        p.deletion(0);
        numPopulation = p.getNumPopulation();
        
        if (numPopulation > 9000) {
            p.deletion(maxFitness - 8);
        }
        if (numPopulation > 15000) {
            std::cout << "BEGIN PRINTING STUFF" << '\n';
            p.getAllGenes();
            break;
        }
        if (maxFitness == minFitness) {
            stagnationCounter++;
            std::cout << "Stagnation Counter " << stagnationCounter << '\n';
            if (stagnationCounter >= 20) {
                p.deletion(maxFitness - 1);
                std::cout << "Beginning Mass Mutation" << '\n';
                for (int i = 0; i < numPopulation; i++) {
                    p.mutation(100, p.members[i], threshold - maxFitness);
                    
                }
                p.calcAllFitness();
                stagnationCounter = 0;
            }
        }
        if (prevFitness == maxFitness) {
            stagnationCounter++;
            std::cout << "Stagnation Counter " << stagnationCounter << '\n';
            if (stagnationCounter >= 20) {
                p.deletion(maxFitness - 1);
                std::cout << "Beginning Mass Mutation" << '\n';
                for (int i = 0; i < numPopulation; i++) {
                    p.mutation(100, p.members[i], threshold - maxFitness);
                    
                }
                p.calcAllFitness();
                stagnationCounter = 0;
            }
        }
        
        prevFitness = maxFitness;
        std::cout <<  "Max Fitness "<< maxFitness << ' ' << threshold*threshold << '\n';
        std::cout << "Min Fitness " << minFitness << ' ' <<threshold*threshold << '\n';
        std::cout << "count " << count << '\n';
        count++;
        std::cout << "Num Members " << numPopulation << '\n';
    }
    std::cout << "----------------------------------------------" << '\n';
    std::cout << p.getMostFitMember() << '\n';
    
    
    return 0;
}
