//
//  word_filter.cpp
//  WordFilter
//
//  Created by Alvin Pon on 12/18/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#include "word_filter.hpp"

word_filter::word_filter() {
    divisor = 50;

    std::fstream fstream("./profanity.txt", fstream.in);
    if (fstream.is_open()) {
        for (std::string expletive; std::getline(fstream, expletive, ',');) {
            expletives[expletive.size() % divisor].push_back(expletive);
        }
    }

    for (auto it = expletives.begin(); it != expletives.end(); it++) {
        std::sort((*it).second.begin(), (*it).second.end());
    }
}

word_filter::word_filter(std::string file_path) {
    divisor = 50;

    std::fstream fstream(file_path, fstream.in);
    if (fstream.is_open()) {
        for (std::string expletive; std::getline(fstream, expletive, ',');) {
            std::cout << expletive << std::endl;
            expletives[expletive.size() % divisor].push_back(expletive);
        }
    }

    for (auto it = expletives.begin(); it != expletives.end(); it++) {
        std::sort((*it).second.begin(), (*it).second.end());
    }
}

bool word_filter::add_expletive(std::string & expletive) {
    bool added = false;
    std::string::size_type index = expletive.size() % divisor;

    if (expletive.empty() == false && std::find(expletives[index].begin(), expletives[index].end(), expletive) == expletives[index].end()) {
        expletives[index].insert(std::upper_bound(expletives[index].begin(), expletives[index].end(), expletive), expletive);
        added = true;
    }

    return added;
}

bool word_filter::remove_expletive(std::string & expletive) {
    bool removed = false;
    std::string::size_type index = expletive.size() % divisor;

    if (expletive.empty() == false) {
        auto it = std::find(expletives[index].begin(), expletives[index].end(), expletive);
        if (it != expletives[index].end()) {
            expletives[index].erase(it);
            removed = true;
        }
    }

    return removed;
}

void word_filter::filter_expletive(std::string & message) {
    std::regex word_regex("[^\\s]+");
    std::set<std::string> swear_words;
    auto begin = std::sregex_iterator(message.begin(), message.end(), word_regex), end = std::sregex_iterator();

    for (std::sregex_iterator it = begin; it != end; it++) {
        std::string word = (*it).str();
        std::string::size_type index = word.size() % divisor;

        if (std::find(expletives[index].begin(), expletives[index].end(), word) != expletives[index].end()) {
            swear_words.insert(word);
        }
    }

    for (auto & swear_word : swear_words) {
        std::regex swear_word_regex(swear_word);
        message = std::regex_replace(message, swear_word_regex, "*");
    }
}
