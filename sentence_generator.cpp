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

 @param file_path a string descripting where your file location is.
 @param words     a vector holding words.
 */
void sentence_generator::read_words(std::string && file_path, std::vector<std::string> & words) {
    std::fstream fstream(file_path);
    if (fstream.is_open()) {
        for (std::string word; std::getline(fstream, word, ',');) {
            words.push_back(word);
        }
    }
    std::sort(words.begin(), words.end());
}

/**
 assign values to the message.

 @param message a message which contains expletive count, selected expletives, and a randomly generated sentence.
 @param mt19937 a mt19937.
 @param words   a vector used for holding words.
 */
void sentence_generator::randomly_select_word(message & message, std::mt19937 & mt19937, std::vector<std::string> & words) {
    std::size_t index;

    uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, (int)words.size() - 1));
    index = uniform_int_distribution(mt19937);
    message.sentence += words[index] + ' ';

    if (std::binary_search(expletives.begin(), expletives.end(), words[index])) {
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
    std::mt19937 mt19937(random_device());

    for (std::size_t i = 0; i < 100; i++) {
        uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, 6));
        switch (uniform_int_distribution(mt19937)) {
            case 0:
                randomly_select_word(message, mt19937, adjectives);
                break;
            case 1:
                randomly_select_word(message, mt19937, adverbs);
                break;
            case 2:
                randomly_select_word(message, mt19937, expletives);
                break;
            case 3:
                randomly_select_word(message, mt19937, nouns);
                break;
            case 4:
                randomly_select_word(message, mt19937, prepositions);
                break;
            case 5:
                randomly_select_word(message, mt19937, pronouns);
                break;
            default:
                randomly_select_word(message, mt19937, verbs);
                break;
        }
    }

    message.sentence.erase(message.sentence.size() - 1);
    return message;
}
