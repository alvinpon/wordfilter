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

    std::fstream fstream("./dictionary/expletives.txt", fstream.in);
    if (fstream.is_open()) {
        for (std::string expletive; std::getline(fstream, expletive, ',');) {
            // O(log N)
            expletives[expletive.size() % divisor].insert(expletive);
        }
    }
}

/**
 add an expletive into the expletives if the expletive doesn't exist.

 @param     expletive   an expletive.
 @return                true if an expletive is added into the expletives.
 */
bool word_filter::add_expletive(std::string & expletive) {
    bool added = false;
    std::string::size_type index = expletive.size() % divisor;

    if (expletive.empty() == false && expletives[index].count(expletive) == 0) {
        // O(log N)
        expletives[index].insert(expletive);
        added = true;
    }

    return added;
}

/**
 remove an expletive from the expletives if the expletive exists.

 @param     expletive   an expletive.
 @return                true if an expletive is removed from the expletives.
 */
bool word_filter::remove_expletive(std::string & expletive) {
    bool removed = false;
    std::string::size_type index = expletive.size() % divisor;

    if (expletive.empty() == false) {
        // O(log N)
        auto it = expletives[index].find(expletive);
        if (it != expletives[index].end()) {
            // O(log N)
            expletives[index].erase(it);
            removed = true;
        }
    }

    return removed;
}

/**
 filter out expletives within original_message, and return a filtered message.

 @param     original_message    an original message which contains an original expletive count, selected expletives, and sentence.
 @return    filtered_message    a filtered message which contains a filtered expletive count, selected expletives, and sentence.
 */
message word_filter::filter_expletive(message original_message) {
    message filtered_message {0, original_message.sentence};
    std::regex word_regex("[^\\s]+");
    std::sregex_iterator begin = std::sregex_iterator(filtered_message.sentence.begin(), filtered_message.sentence.end(), word_regex), end = std::sregex_iterator();

    // O(N)
    for (std::sregex_iterator iterator = begin; iterator != end; iterator++) {
        std::string word = (*iterator).str();
        std::string::size_type index = word.size() % divisor;

        // O(log N)
        if (std::binary_search(expletives[index].begin(), expletives[index].end(), word)) {
            filtered_message.selected_expletives.push_back(word);
        }
    }

    filtered_message.expletive_count = filtered_message.selected_expletives.size();
    for (auto & selected_expletive : filtered_message.selected_expletives) {
        std::regex expletive_regex(selected_expletive);
        filtered_message.sentence = std::regex_replace(filtered_message.sentence, expletive_regex, std::string(selected_expletive.size(), '*'));
    }

    return filtered_message;
}

/**
 detect unfiltered expletives.

 @param     original_expletives     an original expletives.
 @param     filtered expletives     an filtered expletives.
 @param     unfiltered_expletives   an unfiltered expletives.
 */
void word_filter::detect_unfiltered_expletives(std::vector<std::string> & original_expletives,
                                               std::vector<std::string> & filtered_expletives,
                                               std::vector<std::string> & unfiltered_expletives) {
    std::vector<std::string>::size_type size = filtered_expletives.size();

    unfiltered_expletives = original_expletives;

    // O(MN)
    for (auto s = 0; unfiltered_expletives.empty() == false && s < size; s++) {
        auto iterator = std::find(unfiltered_expletives.begin(), unfiltered_expletives.end(), filtered_expletives[s]);

        if (iterator != unfiltered_expletives.end()) {
            unfiltered_expletives.erase(iterator);
        }
    }
}
