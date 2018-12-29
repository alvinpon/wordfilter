//
//  main.cpp
//  WordFilter
//
//  Created by Alvin Pon on 12/17/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "message.hpp"
#include "sentence_generator.hpp"
#include "word_filter.hpp"

/**
 write a result about filtered message.

 @param result  an output file stream
 @param message a message which contains original sentence, filtered sentence, substrings, and filtered expletives.
 */
void write_result(std::ofstream & result, message & message) {
    for (const std::string & original_word : message.original_words) {
        result << original_word << ' ';
    }
    result << "\n\n";

    for (const std::string & filtered_word : message.filtered_words) {
        result << filtered_word << ' ';
    }
    result << "\n\n";

    result << message.filtered_expletives.size() << " expletives filtered out.\n";
    for (const std::string & filtered_expletive : message.filtered_expletives) {
        result << filtered_expletive << ", ";
    }
    result << "\n\n";
}

/**
 calculate time.

 @param start   a start time point
 @param end     an end time point
 */
void calculate_time(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end) {
    std::time_t start_time, end_time;
    std::chrono::duration<double> elapsed_seconds;

    start_time = std::chrono::system_clock::to_time_t(start);
    end_time = std::chrono::system_clock::to_time_t(end);
    elapsed_seconds = end - start;

    std::cout << std::ctime(&start_time) << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}

/**
 filter out all expltives within an array which contains at least 100 words generated randomly by uniform distribution.
 */
void filter() {
    std::ofstream result("./result.txt");
    message message;
    word_filter word_filter;
    sentence_generator sentence_generator;

    for (std::size_t i = 0; i < 200000; i++) {
        sentence_generator.generate_sentence(message);
        word_filter.extract_substrings(message);
        word_filter.filter_expletives(message);
        write_result(result, message);
        message = {};
    }
}

int main(int argc, const char * argv[]) {
    auto start = std::chrono::system_clock::now();
    std::cout << "expletives are being filtered." << std::endl;
    filter();
    std::cout << "expletives have been filtered." << std::endl;
    auto end = std::chrono::system_clock::now();

    calculate_time(start, end);
    return 0;
}
