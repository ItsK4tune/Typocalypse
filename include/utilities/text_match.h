#pragma once

#include <string>
#include <vector>

inline std::vector<bool> getPrefixMatchMaskFromTypedEnd(const std::string& word, const std::string& typed) {
    std::vector<bool> matched(word.size(), false);

    size_t maxLen = std::min(word.size(), typed.size());

    for (size_t len = maxLen; len > 0; --len) {
        std::string typedSuffix = typed.substr(typed.size() - len, len);
        std::string wordPrefix = word.substr(0, len);

        if (typedSuffix == wordPrefix) {
            for (size_t i = 0; i < len; ++i)
                matched[i] = true;
            break;
        }
    }

    return matched;
}