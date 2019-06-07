//
//  Chromosome.cpp
//  Genetic Algorithm
//
//  Created by Bharddwaj Vemulapalli on 6/6/19.
//  Copyright © 2019 Bharddwaj Vemulapalli. All rights reserved.
//

#include "Chromosome.hpp"

    


Chromosome::Chromosome (std::string sentence,int charlength){
        //constructor that initializes the chromosome with random genes of charlength
        //also gives the instance variable ans the value of the answer the algorithm is attempting to guess
        ans = sentence;
        
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, characters.size() - 1); //29 is inclusive
        int rand_num = distribution(generator);
        
        //std::srand(std::time(0)); //uses current time as a seed
        
        
        //const int min = 0;
        //const int max = 29;
        //int rand_num = std::rand() % min + max;
        
        for (int i = 0; i < charlength; i++) {
            genes.push_back(characters[rand_num]);
            rand_num = distribution(generator);
        }
    }
    int Chromosome::getChromosomeLength(void){
        // this->genes.size()
        return genes.size();
    }
    std::string Chromosome::getGenes(void){
        //basically the toString method of Chromosome
        std::basic_string<char> full_genes = "";
        for (int i = 0; i < genes.size(); i++) {
            full_genes += genes[i];
        }
        return full_genes;
    }
    void Chromosome::calcFitness(void){
        int score = 0;
        for (int i = 0; i < genes.size(); i++) {
            if (genes[i] == ans[i]) {
                score++;
            }
        }
        fitness = score;
    }
int Chromosome::getFitness(void){
        //score is based on the number of the same characters in the answer vs the genes
        //also sets the fitness instance variable
        
        return fitness;
    }
Chromosome Chromosome::copy(void){
        //creates a copy of the current Chromosome
        Chromosome deep_copy(ans,genes.size());
        for (int i = 0; i < genes.size(); i++) {
            deep_copy.genes[i] = genes[i];
        }
        return deep_copy;
    }

