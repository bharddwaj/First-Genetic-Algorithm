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
    
    int getFitness(){
        //score is based on the number of the same characters in the answer vs the genes
        int score = 0;
        for (int i = 0; i < genes.size(); i++) {
            if (genes[i] == ans[i]) {
                score++;
            }
        }
        return score;
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
    Population(std::string sent,int popsize){
        for (int i = 0; i < popsize; i ++ ) {
            members.push_back( Chromosome(sent,sent.size()) );
        }
    }
    
    int getMaxFitness(){
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
            ranking.push_back(*pop[key]); //dereferencing pointer to get the actual object
        }
        return ranking;
    }
   
    Chromosome crossOver(){
        //generates child by switching the first n random elements between the two randomly selected parents resulting in two children
        //then the function random returns one of the children
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, members.size() - 1); //second num is inclusive
        int rand_num = distribution(generator);
        int rand_num_2 = distribution(generator);
        std::uniform_int_distribution<int> distribution2(0, members[0].getChromosomeLength() - 1);
        int rand_num_3 = distribution2(generator);
        Chromosome parentOne = members[rand_num].copy();
        Chromosome parentTwo= members[rand_num_2].copy();
        std::vector<char> child;
        for (int i = 0; i < rand_num_3 + 1; i++) {
            child.push_back(parentOne.genes[i]);
            parentOne.genes[i] = parentTwo.genes[i];
        }
        for (int i = 0; members[0].getChromosomeLength(); i++) {
            parentTwo.genes[i] = child[i];
        }
        std::uniform_int_distribution<int> distribution3(0, 1);
        int rand_num_4 = distribution3(generator);
        if (rand_num_4 == 0){
            return parentOne;
        }
        return parentTwo;
        
    }
    void generateChildren(int numChildren){
        //repeatedly calls crossover and adds the children to the population
        for (int i = 0; i < numChildren; i++) {
            members.push_back(crossOver());
        }
    }
    
    void mutation(int mutationPercent,Chromosome child,int numChanges){
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
    
};

int main(int argc, const char * argv[]) {
    
    //Chromosome c("Hello my name is",23);
    
   // std::cout << c.getChromosomeLength() << std::endl;
   // std::cout << c.getGenes() << '\n';
    Population p("hello my name is",40);
    
    std::vector<Chromosome> wut = p.mostFitMembers();
    std::cout << p.mostFitMembers().size() << '\n';
    for (int i = 0; i < p.mostFitMembers().size(); i++) {
        std::cout << wut[i].getFitness() << '\n';
    }
    return 0;
}
