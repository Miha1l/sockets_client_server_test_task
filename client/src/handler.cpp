#include <cctype>
#include <unordered_map>

#include "handler.h"

Handler::Handler() {

}

bool Handler::check(const std::string& data) const {
    if (data.length() > MAX_STR_LEN || data.empty()) {
        return false;
    }

    for (const auto &sym: data) {
        if (!std::isalpha(sym)) {
            return false;
        }
    }

    return true;
}

std::string Handler::process(const std::string& data) const {
    std::unordered_map<char, int> symbols_count;
    for (const auto &sym: data) {
        symbols_count[sym]++;
    }

    std::string res;
    for (const auto &[key, val] : symbols_count) {
        res = res + key + ':' + std::to_string(val) + '\n';
    }

    return res;
}
