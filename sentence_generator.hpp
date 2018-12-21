//
//  sentence_generator.hpp
//  WordFilter
//
//  Created by Alvin Pon on 12/20/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#ifndef sentence_generator_hpp
#define sentence_generator_hpp

#include <algorithm>
#include <fstream>
#include <random>
#include <string>
#include <vector>

#include "message.hpp"

class sentence_generator {
private:
    std::random_device random_device;
    std::uniform_int_distribution<> uniform_int_distribution;
    std::vector<std::string> adjectives, adverbs, expletives, nouns, prepositions, pronouns, verbs;

    void read_words(std::string && file_path, std::vector<std::string> & words);
    void randomly_select_word(message & message, std::mt19937 & mt19937, std::vector<std::string> & words);
    
public:
    sentence_generator();

    message generate_sentence();
};

#endif /* sentence_generator_hpp */
