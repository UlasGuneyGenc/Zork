#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Direction.h"

inline std::vector<std::string> GetVerbs(const std::string& input)
{
    std::vector<std::string> verbs;
    std::stringstream ss(input);
    std::string word;
    while (ss >> word) {
        verbs.push_back(word);
    }
    return verbs;
}

inline std::string toLowerCase(const std::string& str) {
    std::string temp(str);
    std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    return temp;
}