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

#include "sentence_generator.hpp"
#include "word_filter.hpp"

/**
 write how many expletives are filtered out into the result.txt.

 @param result              an output file stream.
 @param filtered_expletives a vector which contains all expletives filtered out.
 */
void write_result(std::ofstream & result, std::vector<std::string> filtered_expletives) {
    result << "There are " << filtered_expletives.size() << " expletives filtered out.\n";
    for (auto filtered_expletive : filtered_expletives) {
        result << filtered_expletive << ' ';
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
 filter out all expltives within a sentence which contains at least 100 words generated randomly by uniform distribution.
 */
void filter() {
    std::string sentence;
    std::ofstream result("./result.txt");
    word_filter word_filter;
    sentence_generator sentence_generator;

    /**
     time complexity is O(n) because it only goes through once.
     */
    for (std::size_t i = 1; i <= 200000; i++) {
        write_result(result, word_filter.filter_expletives(sentence_generator.generate_sentence()));
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
