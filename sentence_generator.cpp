//
//  sentence_generator.cpp
//  WordFilter
//
//  Created by Alvin Pon on 12/20/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#include "sentence_generator.hpp"

sentence_generator::sentence_generator() {
    read_words("./dictionary/adjectives.txt", adjectives);
    read_words("./dictionary/adverbs.txt", adverbs);
    read_words("./dictionary/expletives.txt", expletives);
    read_words("./dictionary/nouns.txt", nouns);
    read_words("./dictionary/prepositions.txt", prepositions);
    read_words("./dictionary/pronouns.txt", pronouns);
    read_words("./dictionary/verbs.txt", verbs);
}

/**
 load words.

 @param file_path   a string describing where your file is.
 @param words       a vector used for containing a lot of words.
 */
void sentence_generator::read_words(std::string && file_path, std::vector<std::string> & words) {
    std::fstream fstream(file_path);
    if (fstream.is_open()) {
        for (std::string word; std::getline(fstream, word, ',');) {
            words.push_back(word);
        }
    }
}

/**
 generate a struct message whose expletive count and selected expletives will be recorded, and sentence are created by uniform distribution.

 @param result                      a variable used for checking whether it's adding an expletive or not.
 @param mt19937                     a mt19937.
 @param uniform_int_distribution    a uniform_int_distribution used for creating an index created by uniform distribution.
 @param words                       a vector used for holding words.
 @param message                     a message which contains expletive count, selected expletives, and a randomly generated sentence.
 */
void sentence_generator::randomly_select_word(message & message,
                                              std::uniform_int_distribution<>::result_type & result,
                                              std::mt19937 mt19937,
                                              std::uniform_int_distribution<> & uniform_int_distribution,
                                              std::vector<std::string> & words) {
    std::size_t index;

    uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, (int)words.size() - 1));
    index = uniform_int_distribution(mt19937);
    message.sentence += words[index] + ' ';

    if (result == 2) {
        message.expletive_count++;
        message.selected_expletives.push_back(words[index]);
    }
}

/**
 generate a message.

 @return the message.
 */
message sentence_generator::generate_sentence() {
    message message {};
    std::random_device random_device;
    std::mt19937 mt19937(random_device());
    std::uniform_int_distribution<> uniform_int_distribution;
    std::uniform_int_distribution<>::result_type result;

    for (std::size_t i = 0; i < 100; i++) {
        uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, 6));
        switch ((result = uniform_int_distribution(mt19937))) {
            case 0:
                randomly_select_word(message, result, mt19937, uniform_int_distribution, adjectives);
                break;
            case 1:
                randomly_select_word(message, result, mt19937, uniform_int_distribution, adverbs);
                break;
            case 2:
                randomly_select_word(message, result, mt19937, uniform_int_distribution, expletives);
                break;
            case 3:
                randomly_select_word(message, result, mt19937, uniform_int_distribution, nouns);
                break;
            case 4:
                randomly_select_word(message, result, mt19937, uniform_int_distribution, prepositions);
                break;
            case 5:
                randomly_select_word(message, result, mt19937, uniform_int_distribution, pronouns);
                break;
            default:
                randomly_select_word(message, result, mt19937, uniform_int_distribution, verbs);
                break;
        }
    }

    return message;
}
