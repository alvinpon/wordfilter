//
//  message.hpp
//  WordFilter
//
//  Created by Alvin Pon on 12/26/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#ifndef message_hpp
#define message_hpp

#include <array>
#include <queue>
#include <set>
#include <string>

#include "substring.hpp"

struct message {
    std::array<std::string, 100> original_words, filtered_words;
    std::queue<substring> substrings;
    std::set<std::string> filtered_expletives;
};

#endif /* message_hpp */
