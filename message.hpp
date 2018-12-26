//
//  message.hpp
//  WordFilter
//
//  Created by Alvin Pon on 12/26/18.
//  Copyright © 2018 Alvin Pon. All rights reserved.
//

#ifndef message_hpp
#define message_hpp

#include <string>
#include <vector>

struct message {
    std::string original_sentence, filtered_sentence;
    std::vector<std::string> filtered_expletives;
};

#endif /* message_hpp */
