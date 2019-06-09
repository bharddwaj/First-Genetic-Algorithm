//
//  Chromosome.hpp
//  Genetic Algorithm
//
//  Created by Bharddwaj Vemulapalli on 6/6/19.
//  Copyright © 2019 Bharddwaj Vemulapalli. All rights reserved.
//

#ifndef Chromosome_hpp
#define Chromosome_hpp

#include <stdio.h>
#include <random>
#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <map>
class Chromosome {
    
public:
    //characters you can use in your phrase
    std::array<char, 31> characters = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x',
        'y','z',' ', '?', '.', ',', '!'};
    int fitness;
    std::vector<char> genes;
    std::basic_string<char> ans;
    Chromosome (std::string sentence,int charlength);
    int getChromosomeLength(void);
    std::string getGenes(void);
    void calcFitness(void);
    int getFitness(void);
    Chromosome copy(void);
};
#endif /* Chromosome_hpp */
