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

 @param string      a string which contains only 1 word.
 @param substrings  a vector which will hold all substrings.
 */
void word_filter::extract_substrings(const std::string & string, std::vector<std::string> & substrings) {
    std::string::size_type size;

    substrings.clear();
    size = string.size();

    for (auto start = 0; start < size; start++) {
        for (auto end = 2; end <= size - start; end++) {
            substrings.push_back(string.substr(start, end));
        }
    }
}

/**
 filter out all expletives within an array.

 time complexity is O(mn).
 first of all, the time complexity of the first loop is O(m) because sentence contains m words.
 secondly, because we need to examine all substrings (let's assume n substrings) in a word, the
 time complexity of the second loop is O(n). for example, abcd is a word contained within the
 sentence, so all substrings are ab, bc, cd, abc, bcd, abcd. the reason why I don't write a, b, c,
 and d is that a character shouldn't be recognized as an expltives.

 sentence
    word1
        substring1, substring2, substring3...
    word2
        substring1, substring2, substring3...
    word3
        substring1, substring2, substring3...
 */
void word_filter::filter_expletives(message & message) {
    std::vector<std::string> substrings;
    std::string::size_type key_index, replaced_index, size;

    message.filtered_words = message.original_words;

    for (std::array<std::string, 100>::size_type index = 0; index < 100; index++) {
        extract_substrings(message.original_words[index], substrings);

        std::sort(substrings.begin(), substrings.end(), [](std::string & string1, std::string & string2) {
            return string1.size() > string2.size();
        });

        for (auto & substring : substrings) {
            key_index = substring.size() % divisor;
            if (std::binary_search(expletives[key_index].begin(), expletives[key_index].end(), substring)) {
                if ((replaced_index = message.filtered_words[index].find(substring)) != std::string::npos) {
                    size = substring.size();
                    message.filtered_words[index].replace(replaced_index, size, std::string(size, '*'));
                }

                message.filtered_expletives.insert(substring);
            }
        }
    }
}
