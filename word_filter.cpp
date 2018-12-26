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

 @param string  a string which contains only 1 word.
 */
std::vector<std::string> word_filter::extract_substrings(std::string & string) {
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
 replace the word.

 @param replaced_word       a word needed to be replaced.
 @param substrings          all substrings of replaced word.
 @param filtered_expletives filtered expletives.
 */
void word_filter::replace_word(std::string & replaced_word,
                               std::vector<std::string> substrings,
                               std::vector<std::string> & filtered_expletives) {
    std::string::size_type key_index, index, size;

    std::sort(substrings.begin(), substrings.end(), [](std::string & string1, std::string & string2) {
        return string1.size() > string2.size();
    });

    for (auto & substring : substrings) {
        key_index = substring.size() % divisor;

        if (std::binary_search(expletives[key_index].begin(), expletives[key_index].end(), substring)) {
            if ((index = replaced_word.find(substring)) != std::string::npos) {
                size = substring.size();
                replaced_word.replace(index, size, std::string(size, '*'));
            }

            filtered_expletives.push_back(substring);
        }
    }
}

/**
 filter out expletives within sentence.

 @param     original_sentence   a random sentence which contains 100 words.
 @return    message             a message which contains original sentence, filtered sentence, and filtered expletives.

 time complexity is O(mn).
 first of all, the time complexity of the loop is O(m) because sentence contains m words. secondly, because we need to examine all substrings
 (let's assume n substrings) in a word, the time complexity of the replace_word member function is O(n). for example, abcd is a word contained
 within the sentence, so all substrings are ab, bc, cd, abc, bcd, abcd. The reason why I don't write a, b, c and d is that a character shouldn't
 be recognized as an expltives.

 sentence
    word1
        substring1, substring2, substring3...
    word2
        substring1, substring2, substring3...
    word3
        substring1, substring2, substring3...
 */
message word_filter::filter_expletives(std::string original_sentence) {
    std::regex word_regex;
    std::string filtered_sentence, word;
    std::sregex_iterator begin, end;
    std::vector<std::string> filtered_expletives;

    word_regex = std::regex("[^\\s]+");
    begin = std::sregex_iterator(original_sentence.begin(), original_sentence.end(), word_regex);
    end = std::sregex_iterator();

    for (std::sregex_iterator iterator = begin; iterator != end; iterator++) {
        word = (*iterator).str();
        replace_word(word, extract_substrings(word), filtered_expletives);
        filtered_sentence += word + ' ';
    }
    filtered_sentence.pop_back();

    return message {original_sentence, filtered_sentence, filtered_expletives};
}
