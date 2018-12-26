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
 @return    added       true if an expletive is added into the expletives.
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
 @return    removed     true if an expletive is removed from the expletives.
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
 extract all substrings whose length is equal to or greater than 2.

 @param string    a string which contains only 1 word.
 */
std::vector<std::string> word_filter::extract_substrings(std::string string) {
    std::string::size_type size;
    std::vector<std::string> substrings;

    size = string.size();
    for (auto start = 0; start < size; start++) {
        for (auto end = 2; end <= size - start; end++) {
            substrings.push_back(string.substr(start, end));
        }
    }

    return substrings;
}

/**
 filter out expletives within sentence.

 @param sentence    a random sentence which contains 100 words.
 */
std::vector<std::string> word_filter::filter_expletives(std::string sentence) {
    std::string string;
    std::string::size_type index;
    std::regex word_regex("[^\\s]+");
    std::vector<std::string> filtered_expletives, substrings;
    std::sregex_iterator begin = std::sregex_iterator(sentence.begin(), sentence.end(), word_regex), end = std::sregex_iterator();

    /**
     time complexity is O(mn).
     first of all, if sentence contains m words, the time complexity of first loop is O(m).
     secondly, because we need to examine all substrings (let's assume n substrings) in a word, the time complexity of second loop is O(n).
     for example, ABCD is a word contained within the sentence. The all substrings are AB, BC, CD, ABC, BCD, ABCD.
     Architecture:
     sentence
        word1
            substring1, substring2, substring3...
        word2
            substring1, substring2, substring3...
        word3
            substring1, substring2, substring3...
          .
          .
          .
     */
    for (std::sregex_iterator iterator = begin; iterator != end; iterator++) {
        substrings = extract_substrings((*iterator).str());

        for (auto & substring : substrings) {
            index = substring.size() % divisor;

            // time complexity of binary search is O(logn).
            if (std::binary_search(expletives[index].begin(), expletives[index].end(), substring)) {
                // space complexity is O(mn).
                filtered_expletives.push_back(substring);
            }
        }
    }

    return filtered_expletives;
}
