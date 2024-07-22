#include <regex>
#include <algorithm>
#include "Handler.h"

Handler::Handler() {

}

bool Handler::check(const std::string& data) {
    if (data.length() > MAX_STR_LEN || data.empty()) {
        return false;
    }

    for (const auto& sym: data) {
        if (!std::isdigit(sym)) {
            return false;
        }
    }

    return true;
}

void Handler::process(std::string& data) {
    std::sort(data.begin(), data.end(), [](const auto& a, const auto& b) {
        return a > b;
    });

    data = std::regex_replace(data, std::regex(PATTERN), REPLACE);
}

int Handler::getSum(const std::string& data) {
    auto sum = 0;
    for (const auto& sym: data) {
        if (!std::isdigit(sym)) {
            continue;
        }
        sum += sym - '0';
    }
    return sum;
}
