//
//  word_filter.cpp
//  WordFilter
//
//  Created by Alvin Pon on 12/18/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#include "word_filter.hpp"

word_filter::word_filter() {
    std::fstream fstream("./dictionary/expletives.txt", fstream.in);

    if (fstream.is_open()) {
        for (std::string expletive; std::getline(fstream, expletive, ',');) {
            expletives.insert(expletive);
        }
    }
}

/**
 add an expletive into the expletives if the expletive doesn't exist.

 @param     expletive   an expletive.
 @return    added       true if an expletive is added into the expletives.
 */
bool word_filter::add_expletive(std::string & expletive) {
    bool added = false;

    if (expletive.empty() == false && expletives.count(expletive) == 0) {
        expletives.insert(expletive);
        added = true;
    }

    return added;
}

/**
 remove an expletive from the expletives if the expletive exists.

 @param     expletive   an expletive.
 @return    removed     true if an expletive is removed from the expletives.
 */
bool word_filter::remove_expletive(std::string & expletive) {
    bool removed = false;
    std::set<std::string>::iterator iterator;

    if (expletive.empty() == false && (iterator = expletives.find(expletive)) != expletives.end()) {
        expletives.erase(iterator);
        removed = true;
    }

    return removed;
}

/**
 filter out all expletives within an array.

 time complexity is O(n) because this function only goes all substrings once.
 */
void word_filter::filter_expletives(message & message) {
    std::string::size_type replaced_index, size;

    for (substring & substring : message.substrings) {
        if (expletives.count(substring.word) == 1) {
            if ((replaced_index = message.filtered_words[substring.index].find(substring.word)) != std::string::npos) {
                size = substring.word.size();
                message.filtered_words[substring.index].replace(replaced_index, size, std::string(size, '*'));
            }

            message.filtered_expletives.insert(substring.word);
        }
    }
}
