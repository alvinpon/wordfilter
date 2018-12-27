//
//  sentence_generator.cpp
//  WordFilter
//
//  Created by Alvin Pon on 12/20/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#include "sentence_generator.hpp"

sentence_generator::sentence_generator() {
    load_words("./dictionary/adjectives.txt", adjectives);
    load_words("./dictionary/adverbs.txt", adverbs);
    load_words("./dictionary/expletives.txt", expletives);
    load_words("./dictionary/nouns.txt", nouns);
    load_words("./dictionary/prepositions.txt", prepositions);
    load_words("./dictionary/pronouns.txt", pronouns);
    load_words("./dictionary/verbs.txt", verbs);
}

/**
 load all words from dictionary folder into different vectors.

 @param file_path   a string descripting where your file is.
 @param words       a vector hoding different words.
 */
void sentence_generator::load_words(std::string && file_path, std::vector<std::string> & words) {
    std::fstream fstream(file_path);
    if (fstream.is_open()) {
        for (std::string word; std::getline(fstream, word, ',');) {
            words.push_back(word);
        }
    }
}

/**
 generate a sentence which will contain a plethora of words randomly selected by uniform distribution.
 */
void sentence_generator::generate_sentence(message & message) {
    std::mt19937 mt19937;
    std::random_device random_device;
    std::uniform_int_distribution<> uniform_int_distribution;

    mt19937 = std::mt19937(random_device());

    for (std::size_t i = 0; i < 100; i++) {
        uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, 6));
        switch (uniform_int_distribution(mt19937)) {
            case 0:
                uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, (int)adjectives.size() - 1));
                message.original_words[i] = adjectives[uniform_int_distribution(mt19937)];
                break;
            case 1:
                uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, (int)adverbs.size() - 1));
                message.original_words[i] = adverbs[uniform_int_distribution(mt19937)];
                break;
            case 2:
                uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, (int)expletives.size() - 1));
                message.original_words[i] = expletives[uniform_int_distribution(mt19937)];
                break;
            case 3:
                uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, (int)nouns.size() - 1));
                message.original_words[i] = nouns[uniform_int_distribution(mt19937)];
                break;
            case 4:
                uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, (int)prepositions.size() - 1));
                message.original_words[i] = prepositions[uniform_int_distribution(mt19937)];
                break;
            case 5:
                uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, (int)pronouns.size() - 1));
                message.original_words[i] = pronouns[uniform_int_distribution(mt19937)];
                break;
            default:
                uniform_int_distribution.param(std::uniform_int_distribution<>::param_type(0, (int)verbs.size() - 1));
                message.original_words[i] = verbs[uniform_int_distribution(mt19937)];
                break;
        }

        auto size = message.original_words[i].size();
        for (auto start = 0; start < size; start++) {
            for (auto end = 2; end <= size - start; end++) {
                message.substrings.push_back(substring{i, message.original_words[i].substr(start, end)});
            }
        }
    }

    message.filtered_words = message.original_words;
    std::sort(message.substrings.begin(), message.substrings.end(), [](substring & string1, substring & string2) {
        return string1.word.size() > string2.word.size();
    });
}
