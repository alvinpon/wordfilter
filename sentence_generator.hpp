//
//  sentence_generator.hpp
//  WordFilter
//
//  Created by Alvin Pon on 12/20/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#ifndef sentence_generator_hpp
#define sentence_generator_hpp

#include <fstream>
#include <random>
#include <string>
#include <vector>

class sentence_generator {
private:
    std::vector<std::string> adjectives, adverbs, expletives, nouns, prepositions, pronouns, verbs;
    
    void load_words(std::string && file_path, std::vector<std::string> & words);
    
public:
    sentence_generator();
    
    std::string generate_sentence();
};

#endif /* sentence_generator_hpp */
