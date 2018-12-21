//
//  main.cpp
//  WordFilter
//
//  Created by Alvin Pon on 12/17/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#include <iostream>

#include "message.hpp"
#include "sentence_generator.hpp"
#include "word_filter.hpp"

int main(int argc, const char * argv[]) {
    sentence_generator sentence_generator;
    word_filter word_filter;

    for (std::size_t i = 0; i < 200; i++) {
        message message1, message2;

        message1 = sentence_generator.generate_sentence();
        message2 = word_filter.filter_expletive(message1);

        std::cout << message1.expletive_count << " expletives\n" << message1.sentence << '\n' << std::endl;
        std::cout << message2.expletive_count << " expletives\n" << message2.sentence << '\n' << std::endl;
    }

    return 0;
}
