//
//  word_filter.cpp
//  WordFilter
//
//  Created by Alvin Pon on 12/18/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#include "word_filter.hpp"

/**
 * [initialize the expletives]
 */
word_filter::word_filter() {
    divisor = 50;

    std::fstream fstream("./profanity.txt", fstream.in);
    if (fstream.is_open()) {
        for (std::string expletive; std::getline(fstream, expletive, ',');) {
            expletives[expletive.size() % divisor].insert(expletive);
        }
    }
}

/**
 * [initialize the expletives]
 * @param std::string file_path [to assign the location where your text file is]
 */
word_filter::word_filter(std::string file_path) {
    divisor = 50;

    std::fstream fstream(file_path, fstream.in);
    if (fstream.is_open()) {
        for (std::string expletive; std::getline(fstream, expletive, ',');) {
            expletives[expletive.size() % divisor].insert(expletive);
        }
    }
}

/**
 * [add an expletive into the expletives if not existing]
 * @param  std::string expletive [an expletive]
 * @return bool                  [true if an expletive is added into the expletives]
 */
bool word_filter::add_expletive(std::string & expletive) {
    bool added = false;
    std::string::size_type index = expletive.size() % divisor;

    if (expletive.empty() == false && expletives[index].count(expletive) == 0) {
        expletives[index].insert(expletive);
        added = true;
    }

    return added;
}

/**
 * [remove an expletive from the expletives if existing]
 * @param  std::string expletive [an expletive]
 * @return bool                  [true if an expletive is removed from the expletives]
 */
bool word_filter::remove_expletive(std::string & expletive) {
    bool removed = false;
    std::string::size_type index = expletive.size() % divisor;

    if (expletive.empty() == false) {
        auto it = expletives[index].find(expletive);
        if (it != expletives[index].end()) {
            expletives[index].erase(it);
            removed = true;
        }
    }

    return removed;
}

/**
 * [filter swear_words existing within message]
 * @param  std::string message [a message that contain or doesn't contain swear words]
 * @return std::string         [a filtered message]
 */
std::string word_filter::filter_expletive(std::string message) {
    std::regex word_regex("[^\\s]+");
    std::set<std::string> swear_words;
    auto begin = std::sregex_iterator(message.begin(), message.end(), word_regex), end = std::sregex_iterator();

    /**
     * [using regular expression to find out every word in the message]
     * @param std::sregex_iterator it [an iterator to iterate words inside the message]
     */
    for (std::sregex_iterator it = begin; it != end; it++) {
        std::string word = (*it).str();
        std::string::size_type index = word.size() % divisor;

        /**
         * [if this word is a swear word that can be found in expletives, this word will be added into swear_words]
         */
        if (expletives[index].find(word) != expletives[index].end()) {
            swear_words.insert(word);
        }
    }

    /**
     * [replace the swear word with asterisk by using another regular expression]
     */
    for (auto & swear_word : swear_words) {
        std::regex swear_word_regex(swear_word);
        message = std::regex_replace(message, swear_word_regex, "*");
    }

    return message;
}
