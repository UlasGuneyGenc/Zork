#pragma once
#include "Direction.h"
#include <string>
#include <vector>
#include <sstream>
#include <vector>
#include <algorithm>

inline std::vector<std::string> GetVerbs(std::string input)
{
    std::vector<std::string> verbs;
    std::stringstream ss(input);
    std::string word;
    while (ss >> word) {
        verbs.push_back(word);
    }
    return verbs;
}

inline std::string toLowerCase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}