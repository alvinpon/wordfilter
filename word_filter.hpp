//
//  word_filter.hpp
//  WordFilter
//
//  Created by Alvin Pon on 12/18/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#ifndef word_filter_hpp
#define word_filter_hpp

#include <array>
#include <fstream>
#include <set>
#include <string>

#include "message.hpp"
#include "substring.hpp"

class word_filter {
private:
    std::set<std::string> expletives;

public:
    word_filter();

    bool add_expletive(const std::string & expletive);
    bool remove_expletive(const std::string & expletive);
    void filter_expletives(message & message);
    void extract_substrings(message & message);
};

#endif /* word_filter_hpp */
