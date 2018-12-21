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
        auto it = expletives[index].find(expletive);
        if (it != expletives[index].end()) {
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

    for (std::sregex_iterator iterator = begin; iterator != end; iterator++) {
        std::string word = (*iterator).str();
        std::string::size_type index = word.size() % divisor;

        if (std::binary_search(expletives[index].begin(), expletives[index].end(), word)) {
            filtered_message.selected_expletives.push_back(word);
        }
    }

    filtered_message.expletive_count = filtered_message.selected_expletives.size();
    for (auto & expletive : filtered_message.selected_expletives) {
        std::regex curse_regex(expletive);
        filtered_message.sentence = std::regex_replace(filtered_message.sentence, curse_regex, std::string(expletive.size(), '*'));
    }

    return filtered_message;
}
