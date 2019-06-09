//
//  Population.cpp
//  Genetic Algorithm
//
//  Created by Bharddwaj Vemulapalli on 6/6/19.
//  Copyright © 2019 Bharddwaj Vemulapalli. All rights reserved.
//

#include <stdio.h>
#include "Population.h"


    



Population::Population(std::string sent,int popsize){
        for (int i = 0; i < popsize; i ++ ) {
            members.push_back( Chromosome(sent,sent.size()) );
            members[i].calcFitness(); //calculating fitness for each chromosome
            sumOfAllFitness += members[i].fitness;
        }
    }
    
    int Population::getNumPopulation(void){
        return members.size();
    }
    void Population::calcAllFitness(void){
        for (int i = 0; i < members.size(); i ++ ) {
            
            members[i].calcFitness(); //calculating fitness for each chromosome
            
        }
    }
    bool Population::allChromosomeLengths(void){
        //checks to see that the size of every member is the same
        
        int length = members[0].genes.size();
        for (int i = 1; i < members.size(); i++) {
            if (members[i].genes.size()!= length){
                return false;
            }
        }
        return true;
    }
    int Population::getMaxFitness(void){
        //returns the max fitness number out of all the members in the population
        int fitness = 0;
        int score;
        for (int i = 0; i < members.size(); i++) {
            score = members[i].getFitness();
            if (score > fitness) {
                fitness = score;
            }
        }
        return fitness;
    }
    std::string Population::getMostFitMember(void){
        //returns essentially the 'toString' of the member of the population with the highest fitness
        int fitness = 0;
        int score;
        std::string sentence = "sm";
        for (int i = 0; i < members.size(); i++) {
            score = members[i].getFitness();
            if (score > fitness) {
                sentence =members[i].getGenes();
                fitness = score;
            }
        }
        return sentence;
    }
    void Population::getAllGenes(void){
        for (int i = 0; i < members.size(); i++) {
            std::cout << members[i].getGenes() << '\n';
        }
    }
    /*
     std::vector<Chromosome> mostFitMembers(){
     //returns vector of the members in ascending order based on fitness I believe
     std::map<int, Chromosome*> pop; //IMPORTANT can't store objects themselves in map but I can store pointers
     std::vector<Chromosome> ranking;
     int fitness = 0;
     int score;
     for (int i = 0; i < members.size(); i++) {
     score = members[i].getFitness();
     if (score > fitness) {
     fitness = score;
     }
     pop[score] = &members[i]; //due to possibility of multiple same scores those members are overwritten
     
     }
     
     std::map<int, Chromosome*>::iterator it;
     for (it = pop.begin(); it != pop.end(); it++) {
     int key = it -> first; // first accesses the key while second accesses the value
     //https://stackoverflow.com/questions/26281979/c-loop-through-map
     ranking.push_back(*pop[key]); //dereferencing pointer to get the actual object
     }
     return ranking;
     }
     
     Chromosome crossOver(int numChanges){
     //generates child by switching n random elements between the two randomly selected parents resulting in two children
     //then the function random returns one of the children
     std::random_device rd;
     std::mt19937 generator(rd());
     std::uniform_int_distribution<int> distribution(0, members.size() - 1); //second num is inclusive
     int rand_num = distribution(generator);
     int rand_num_2 = distribution(generator);
     std::uniform_int_distribution<int> distribution2(0, members[0].getChromosomeLength()); // inclusive
     int rand_num_3 = distribution2(generator);
     Chromosome parentOne = members[rand_num].copy();
     Chromosome parentTwo= members[rand_num_2].copy();
     
     std::unordered_map<int, char> genesHolder;
     for (int i = 0; i < numChanges; i++) {
     std::random_device rd;
     std::mt19937 generator(rd());
     std::uniform_int_distribution<int> distribution2(0, members[0].getChromosomeLength() - 1); // inclusive
     int rand_num_3 = distribution2(generator);
     genesHolder[rand_num_3] = parentOne.genes[rand_num_3];
     parentOne.genes[rand_num_3] = parentTwo.genes[rand_num_3];
     }
     std::unordered_map<int, char>::iterator it;
     for (auto it: genesHolder) {
     int key = it.first; // first accesses the key while second accesses the value
     char value = it.second;
     parentTwo.genes[key] = value;
     }
     std::uniform_int_distribution<int> distribution3(0, 1);
     
     int rand_num_4 = distribution3(generator);
     if (rand_num_4 == 0){
     return parentOne;
     }
     return parentTwo;
     
     } */
    Chromosome Population::crossOver2(Chromosome parentOne,Chromosome parentTwo,int numChanges){
        //generates child by switching n random elements between the two SELECTED parents resulting in two children
        //then the function random returns one of the children
        //IMPORTANT NOTE: I am not using pass by reference so the parameters are merely copies
        std::unordered_map<int, char> genesHolder;
        for (int i = 0; i < numChanges; i++) {
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<int> distribution2(0, members[0].getChromosomeLength() - 1); // inclusive
            int rand_num_3 = distribution2(generator);
            char gene = parentOne.genes[rand_num_3];
            genesHolder[rand_num_3] = gene;
            parentOne.genes[rand_num_3] = parentTwo.genes[rand_num_3];
        }
        std::unordered_map<int, char>::iterator it;
        for (auto it: genesHolder) {
            int key = it.first; // first accesses the key while second accesses the value
            char value = it.second;
            parentTwo.genes[key] = value;
        }
        std::uniform_int_distribution<int> distribution3(0, 1);
        std::random_device rd;
        std::mt19937 generator(rd());
        int rand_num_4 = distribution3(generator);
        if (rand_num_4 == 0){
            parentOne.calcFitness();
            return parentOne;
        }
        
        return parentTwo;
        
    }
    Chromosome Population::crossOver3(Chromosome parentOne,Chromosome parentTwo){
        //generates child by switching FIRST n random elements between the two SELECTED parents resulting in two children
        //then the function random returns one of the children
        //IMPORTANT NOTE: I am not using pass by reference so the parameters are merely copies
        
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution2(1, members[0].getChromosomeLength()); // inclusive
        int rand_num_3 = distribution2(generator); //selecting midpoint
        for (int i = 0; i < rand_num_3; i++) {
            
            
            parentOne.genes[i] = parentTwo.genes[i];
        }
        
        return parentOne;
        
    }
Chromosome Population::crossOver4(Chromosome parentOne,Chromosome parentTwo){
    //k-point crossover
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution2(1, members[0].getChromosomeLength()); // inclusive
    int rand_num = distribution2(generator); //selecting point1
    int rand_num_2 = distribution2(generator);//selecting point2
    if (rand_num < rand_num_2) {
        for (int i = rand_num; i < rand_num_2; i++) {
            parentOne.genes[i] = parentTwo.genes[i];
        }
        return parentOne;
    }
    else if (rand_num > rand_num_2){
        for (int i = rand_num_2; i < rand_num; i++) {
            parentOne.genes[i] = parentTwo.genes[i];
        }
        return parentOne;
    }
    else{
        //can't have rand_num == rand_num_2 or else there won't be any genes to switch
        return crossOver4(parentOne, parentTwo);
    }
    
    
    return parentOne;
}
    void Population::mutation(int mutationPercent,Chromosome &child,int numChanges){
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(1, 100);
        int rand_var = distribution(generator);
        if (rand_var <= mutationPercent) {
            
            for (int i = 0; i < numChanges ; i++) {
                std::random_device rd;
                std::mt19937 generator(rd());
                std::uniform_int_distribution<int> distribution2(0, child.getChromosomeLength() - 1);
                int rand_var_2 = distribution2(generator);
                std::uniform_int_distribution<int> distribution3(0, characters.size() - 1);
                int rand_var_3 = distribution3(generator);
                child.genes[rand_var_2] = characters[rand_var_3];
            }
            
        }
    }
    void Population::deletion(int threshold){
        //delete all elements below a certain threshold fitness
        for (auto it = members.begin(); it != members.end();){
            if (it->fitness <= threshold) {
                members.erase(it);
            }
            else{
                ++it;
            }
        }
    }
    int Population::minFitness(void){
        int minfitness = members[0].fitness;
        for (int i = 1; i < members.size(); i++) {
            if (members[i].fitness < minfitness){
                minfitness = members[i].fitness ;
            }
        }
        return minfitness;
    }
    std::array<int, 2> Population::max_min_fitness(void){
        int minfitness = members[0].fitness;
        int maxfitness = members[0].fitness;
        for (int i = 1; i < members.size(); i++) {
            if (members[i].fitness < minfitness){
                minfitness = members[i].fitness ;
            }
            else if(members[i].fitness > maxfitness){
                maxfitness = members[i].fitness ;
            }
        }
        return {maxfitness,minfitness};
    }
    /*
     void generateChildren(int numChildren,int mutationPercent, int numMutationChanges,int numCrossoverChanges){
     //repeatedly calls crossover and adds the children to the population
     for (int i = 0; i < numChildren; i++) {
     Chromosome child = crossOver(numCrossoverChanges);
     mutation(mutationPercent, child, numMutationChanges);
     members.push_back(child);
     
     }
     }
     
     void generateChildren2(std::vector<Chromosome> fitMembers,int mutationPercent, int numMutationChanges,int numCrossoverChanges){
     //generates multiple children by using mostFitMembers as parents
     int j = 1;
     for (int i = 0; i < fitMembers.size(); i++) {
     Chromosome child = crossOver2(fitMembers[i],fitMembers[j],numCrossoverChanges);
     mutation(mutationPercent, child, numMutationChanges);
     members.push_back(child);
     
     }
     } */
    
    void Population::generateChildren3(int numChildren,int mutationPercent, int numMutationChanges,int numCrossoverChanges){
        //inefficient wheel of fortune method
        //using weighted probabilities based on fitness to 'spin the wheel' for who reproduces
        //going to use normalization method sooner or later
        std::vector<int> wheel;
        int fitness;
        int maxFitness = getMaxFitness();
        for (int i = 0; i < members.size(); i++) {
            fitness = members[i].fitness;
            int limit = (((float)(fitness))/((float)(members[i].getChromosomeLength())))*10; //multiply by 100 if not using fitness squared
            //doing this because square fitness is what i am using
            for (int j = 0; j < limit; j++) {
                wheel.push_back(i);
            }
            
            
        }
        
        for (int children = 0; children < numChildren; children++) {
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<int> distribution(0, wheel.size() - 1);
            int rand_var = distribution(generator);
            int rand_var2 = distribution(generator);
            Chromosome parentOne = members[wheel[rand_var]];
            Chromosome parentTwo =  members[wheel[rand_var2]];
            //Chromosome child = crossOver2(parentOne,parentTwo, numCrossoverChanges);
            //Chromosome child = crossOver3(parentOne,parentTwo);
            Chromosome child = crossOver3(parentOne,parentTwo);
            mutation(mutationPercent, child, numMutationChanges);
            
            members.push_back(child);
            
        }
        calcAllFitness();
        wheel.clear();
    }
    
    
    

