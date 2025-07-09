#pragma once

#include <string>
#include <vector>

inline std::vector<bool> getPrefixMatchMaskFromTypedEnd(const std::string& word, const std::string& typed) {
    std::vector<bool> matched(word.size(), false);

    size_t maxMatchLen = std::min(word.size(), typed.size());
    std::string typedSuffix = typed.substr(typed.size() - maxMatchLen, maxMatchLen);

    for (size_t i = 0; i < maxMatchLen; ++i) {
        if (word[i] == typedSuffix[i]) {
            matched[i] = true;
        } else {
            break;
        }
    }

    return matched;
}