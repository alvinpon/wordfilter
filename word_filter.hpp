//
//  word_filter.hpp
//  WordFilter
//
//  Created by Alvin Pon on 12/18/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#ifndef word_filter_hpp
#define word_filter_hpp

#include <fstream>
#include <map>
#include <regex>
#include <set>
#include <string>

#include "message.hpp"

class word_filter {
private:
    std::string::size_type divisor;
    // O(N)
    std::map<std::string::size_type, std::set<std::string>> expletives;

public:
    word_filter();

    bool add_expletive(std::string & expletive);
    bool remove_expletive(std::string & expletive);
    message filter_expletive(message original_message);
    void detect_unfiltered_expletives(std::vector<std::string> & original_expletives,
                                      std::vector<std::string> & filtered_expletives,
                                      std::vector<std::string> & unfiltered_expletives);
};

#endif /* word_filter_hpp */
