//
//  main.cpp
//  Genetic Algorithm
//
//  Created by Bharddwaj Vemulapalli on 6/2/19.
//  Copyright © 2019 Bharddwaj Vemulapalli. All rights reserved.
//
#include <random>
#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <map>

std::array<char, 29> characters = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x',
    'y','z',' ', '?', '.'};

class Chromosome {
    
public:
    int fitness;
    std::vector<char> genes;
    std::basic_string<char> ans;
    Chromosome (std::string sentence,int charlength){
        //constructor that initializes the chromosome with random genes of charlength
        //also gives the instance variable ans the value of the answer the algorithm is attempting to guess
        ans = sentence;
        
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, characters.size()); //29 is inclusive
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
    int getChromosomeLength(){
        // this->genes.size()
        return genes.size();
    }
    std::string getGenes(){
        //basically the toString method of Chromosome
        std::basic_string<char> full_genes = "";
        for (int i = 0; i < genes.size(); i++) {
            full_genes += genes[i];
        }
        return full_genes;
    }
    void calcFitness(){
        int score = 0;
        for (int i = 0; i < genes.size(); i++) {
            if (genes[i] == ans[i]) {
                score++;
            }
        }
        fitness = score;
    }
    int getFitness(){
        //score is based on the number of the same characters in the answer vs the genes
        //also sets the fitness instance variable
        
        return fitness;
    }
    Chromosome copy(){
        //creates a copy of the current Chromosome
        Chromosome deep_copy(ans,genes.size());
        for (int i = 0; i < genes.size(); i++) {
            deep_copy.genes[i] = genes[i];
        }
        return deep_copy;
    }
};

class Population{
private:
    std::vector<Chromosome> members;
public:
    int sumOfAllFitness; //help with normalizing fitness and selecting which chromosomes reproduce more
    Population(std::string sent,int popsize){
        for (int i = 0; i < popsize; i ++ ) {
            members.push_back( Chromosome(sent,sent.size()) );
            members[i].calcFitness(); //calculating fitness for each chromosome
            sumOfAllFitness += members[i].getFitness();
        }
    }
    
    int getNumPopulation(){
        return members.size();
    }
    
    int getMaxFitness(){
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
    std::string getMostFitMember(){
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
        
    }
    Chromosome crossOver2(Chromosome parentOne,Chromosome parentTwo,int numChanges){
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
            return parentOne;
        }
        return parentTwo;
        
    }
    void mutation(int mutationPercent,Chromosome &child,int numChanges){
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, 100);
        int rand_var = distribution(generator);
        if (rand_var <= mutationPercent) {
            
            for (int i = 0; i < members[0].getChromosomeLength() ; i++) {
                std::random_device rd;
                std::mt19937 generator(rd());
                std::uniform_int_distribution<int> distribution2(0, members[0].getChromosomeLength() - 1);
                int rand_var_2 = distribution2(generator);
                std::uniform_int_distribution<int> distribution3(0, characters.size());
                int rand_var_3 = distribution3(generator);
                child.genes[distribution2(generator)] = characters[rand_var_3];
            }
            
        }
    }
    
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
    }
    
    void generateChildren3(int numChildren,int mutationPercent, int numMutationChanges,int numCrossoverChanges){
        //inefficient wheel of fortune method
        //using weighted probabilities based on fitness to 'spin the wheel' for who reproduces
        //going to use normalization method sooner or later
        std::vector<Chromosome> wheel;
        int fitness;
        int maxFitness = getMaxFitness();
        for (int i = 0; i < members.size(); i++) {
            fitness = members[i].getFitness();
            if (fitness != 0 && fitness >= maxFitness-2) {
                for (int j = 0; j < fitness; j++) {
                    wheel.push_back(members[i]);
                }
            }
            
        }
        
        for (int children = 0; children < numChildren; children++) {
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<int> distribution(0, 100);
            int rand_var = distribution(generator);
            int rand_var2 = distribution(generator);
            Chromosome parentOne = (wheel[rand_var]);
            Chromosome parentTwo =  (wheel[rand_var2]);
            Chromosome child = crossOver2(parentOne,parentTwo, numCrossoverChanges);
            mutation(mutationPercent, child, numMutationChanges);
            members.push_back(child);
        }
        wheel.clear();
    }
    
    
    
};

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
    std::string sentence = "hello my name is";
    int popsize = 2000;
    int mutationPercent = 5;
    int numMutationChanges = sentence.size()/6;
    int numCrossoverChanges = sentence.size()/2;
    int numChildren = 150; //used for generateChildren()
    int count = 0;
    int threshold = sentence.size();
    Population p(sentence,popsize);
    int maxFitness = p.getMaxFitness();
    while ( maxFitness < threshold) {
        //p.generateChildren(numChildren,mutationPercent,numMutationChanges,numCrossoverChanges);
        std::vector<Chromosome> mostFit = p.mostFitMembers();
        //p.generateChildren2(mostFit, mutationPercent, numMutationChanges,numCrossoverChanges);
        p.generateChildren3(numChildren, mutationPercent, numMutationChanges, numCrossoverChanges);
        maxFitness = p.getMaxFitness();
        std::cout <<maxFitness << ' ' << threshold << '\n';
        std::cout << "count " << count << '\n';
        std::cout << "Num Members " << p.getNumPopulation() << '\n';
        count++;
        if (count ==1500) {
            std::cout << p.getMostFitMember() << '\n';
            break;
        }
        
    }
    return 0;
}
