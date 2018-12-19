//
//  main.cpp
//  WordFilter
//
//  Created by Alvin Pon on 12/17/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#include <iostream>
#include <string>

#include "word_filter.hpp"

int main(int argc, const char * argv[]) {
    unsigned int option;
    std::string string;
    word_filter word_filter;

    do {
        std::cout << "Selet what you want to do." << std::endl
                  << "0. Exit"                    << std::endl
                  << "1. Add expletive"           << std::endl
                  << "2. Remove expletive"        << std::endl
                  << "3. Filter expletive"        << std::endl;
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (0 < option && option < 4) {
            std::cout << "Enter a string: ";
            std::getline(std::cin, string);

            if (option == 1) {
                std::cout << (word_filter.add_expletive(string) ? "added successfully" : "added unsuccessfully") << std::endl;
            } else if (option == 2) {
                std::cout << (word_filter.remove_expletive(string) ? "removed successfully" : "removed unsuccessfully") << std::endl;
            } else {
                std::cout << word_filter.filter_expletive(string) << std::endl;
            }
        }
    } while(option not_eq 0);
    
    return 0;
}
