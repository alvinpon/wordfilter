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
    std::string message, expletive;
    word_filter word_filter;
    
    do {
        std::cout << "Selet what you want to do." << std::endl
                  << "0. Exit"                    << std::endl
                  << "1. Add expletive"           << std::endl
                  << "2. Remove expletive"        << std::endl
                  << "3. Filter expletive"        << std::endl;
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (option == 1 or option == 2) {
            std::cout << "Enter a expletive: ";
            std::getline(std::cin, expletive);
            
            if (option == 1) {
                word_filter.add_expletive(expletive);
            } else {
                word_filter.remove_expletive(expletive);
            }
        } else if (option == 3) {
            std::cout << "Enter a message: ";
            std::getline(std::cin, message);
            
            word_filter.filter_expletive(message);
            
            std::cout << message << std::endl;
        }
    } while(option not_eq 0);
    
    return 0;
}

//    std::string message = "不管我前面寫什麼，把幹你娘給我替換掉。";
//    std::regex regex("幹你娘");
//    message = std::regex_replace(message, regex, "*");
//    std::cout << message << std::endl;
