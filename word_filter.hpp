//
//  word_filter.hpp
//  WordFilter
//
//  Created by Alvin Pon on 12/18/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#ifndef word_filter_hpp
#define word_filter_hpp

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

class word_filter {
private:
    std::string::size_type divisor;
    std::map<std::string::size_type, std::vector<std::string>> expletives;
    
public:
    word_filter();
    word_filter(std::string file_path);
    
    bool add_expletive(std::string & expletive);
    bool remove_expletive(std::string & expletive);
    void filter_expletive(std::string & message);
};

#endif /* word_filter_hpp */
