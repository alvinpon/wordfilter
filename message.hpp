//
//  message.hpp
//  WordFilter
//
//  Created by Alvin Pon on 12/21/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#ifndef message_hpp
#define message_hpp

#include <cstddef>
#include <string>
#include <vector>

struct message {
    std::size_t expletive_count;
    std::string sentence;
    std::vector<std::string> selected_expletives;
};

#endif /* message_hpp */
