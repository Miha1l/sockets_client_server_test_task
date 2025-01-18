#pragma once

#include <string>

#define MAX_STR_LEN 64

class Handler {
public:
    Handler();
    
    bool check(const std::string& data) const;
    std::string process(const std::string& data) const;
};
