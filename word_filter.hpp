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
#include <algorithm>
#include <fstream>
#include <map>
#include <regex>
#include <set>
#include <string>

#include "message.hpp"

class word_filter {
private:
    std::string::size_type divisor;
    std::map<std::string::size_type, std::set<std::string>> expletives;
    
    void extract_substrings(const std::string & string, std::vector<std::string> & substrings);
    
public:
    word_filter();
    
    bool add_expletive(std::string & expletive);
    bool remove_expletive(std::string & expletive);
    void filter_expletives(message & message);
};

#endif /* word_filter_hpp */
