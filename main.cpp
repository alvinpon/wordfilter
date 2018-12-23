//
//  main.cpp
//  WordFilter
//
//  Created by Alvin Pon on 12/17/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

#include "message.hpp"
#include "sentence_generator.hpp"
#include "word_filter.hpp"

void write_analysis(std::size_t & total_expletives, std::size_t & total_filtered_expletives) {
    std::ofstream analysis("./analysis.txt");

    analysis << "There are "
             << total_expletives << " expletives that need to be filtered and "
             << total_filtered_expletives << " expletives that are filtered out.\nAccuracy is "
             << (float)total_filtered_expletives / total_expletives;
}

void write_result(std::ofstream & result, message & message1, message & message2, std::vector<std::string> & unfiltered_expletives) {
    std::vector<std::string>::size_type size = unfiltered_expletives.size();

    result << "original message contains " << message1.expletive_count << " expletives\n" << message1.sentence << "\n\n"
           << "filtered message contains " << message2.expletive_count << " expletives\n" << message2.sentence << "\n\n";

    result << "There are " << size << " expletives not filtered: ";
    for (auto & unfiltered_expletive : unfiltered_expletives) {
        result << unfiltered_expletive << ", ";
    }
    result << '\n' << "Accuracy: " << float(message1.expletive_count - size) / message1.expletive_count << "\n\n";
}

void calculate_time(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end) {
    std::time_t start_time, end_time;
    std::chrono::duration<double> elapsed_seconds;

    start_time = std::chrono::system_clock::to_time_t(start);
    end_time = std::chrono::system_clock::to_time_t(end);
    elapsed_seconds = end - start;

    std::cout << std::ctime(&start_time)
              << std::ctime(&end_time)
              << "elapsed time: "  << elapsed_seconds.count() << "s" << std::endl;
}

void filter(std::size_t & total_expletives, std::size_t & total_filtered_expletives) {
    std::ofstream result("./result.txt");
    std::vector<std::string> unfiltered_expletives;
    message message1, message2;
    sentence_generator sentence_generator;
    word_filter word_filter;

    for (std::size_t i = 1; i <= 200000; i++) {
        message1 = sentence_generator.generate_sentence();
        message2 = word_filter.filter_expletive(message1);

        word_filter.detect_unfiltered_expletives(message1.selected_expletives, message2.selected_expletives, unfiltered_expletives);

        total_expletives += message1.expletive_count;
        total_filtered_expletives += message1.expletive_count - unfiltered_expletives.size();

        write_result(result, message1, message2, unfiltered_expletives);
    }
}

int main(int argc, const char * argv[]) {
    std::size_t total_expletives = 0, total_filtered_expletives = 0;

    auto start = std::chrono::system_clock::now();
    std::cout << "expletives are being filtered." << std::endl;
    filter(total_expletives, total_filtered_expletives);
    std::cout << "expletives have been filtered." << std::endl;
    auto end = std::chrono::system_clock::now();

    calculate_time(start, end);
    write_analysis(total_expletives, total_filtered_expletives);
    return 0;
}
