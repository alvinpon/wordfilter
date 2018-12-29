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
bool word_filter::add_expletive(const std::string & expletive) {
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
bool word_filter::remove_expletive(const std::string & expletive) {
    bool removed = false;
    auto iterator = expletives.find(expletive);

    if (expletive.empty() == false && iterator != expletives.end()) {
        expletives.erase(iterator);
        removed = true;
    }

    return removed;
}

/**
 extract all substrings

 @param message a message which contains original sentence, filtered sentence, substrings, and filtered expletives.
 */
void word_filter::extract_substrings(message & message) {
    std::string::size_type size;

    for (std::array<std::string, 100>::size_type i = 0; i < 100; i++) {
        size = message.original_words[i].size();

        for (std::string::size_type start = 0; start < size; start++) {
            for (std::string::difference_type end = size; end - start >= 2; end--) {
                message.substrings.push(substring{i, message.original_words[i].substr(start, end)});
            }
        }
    }
}

/**
 filter out all expletives within an array.
 time complexity is O(n) because this function only goes through all substrings once.

 @param message a message which contains original sentence, filtered sentence, substrings, and filtered expletives.
 */
void word_filter::filter_expletives(message & message) {
    substring substring;
    std::string::size_type replaced_index, size;

    message.filtered_words = message.original_words;

    while (message.substrings.empty() == false) {
        substring = message.substrings.front();
        message.substrings.pop();

        if (expletives.count(substring.word) == 1) {
            if ((replaced_index = message.filtered_words[substring.index].find(substring.word)) != std::string::npos) {
                size = substring.word.size();
                message.filtered_words[substring.index].replace(replaced_index, size, std::string(size, '*'));
            }

            message.filtered_expletives.insert(substring.word);
        }
    }
}
