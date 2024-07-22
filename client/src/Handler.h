#pragma once

#include <string>

#define MAX_STR_LEN 64
#define PATTERN "0|2|4|6|8"
#define REPLACE "KB"

class Handler {
public:
    Handler();
    bool check(const std::string& data);
    void process(std::string& data);
    int getSum(const std::string& data);
};
