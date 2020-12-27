#pragma once

#include <vector>
#include <string>

namespace util {
    std::vector <std::string> createDict(const std::string &pathToDict, int minWordSize);

    class Dictionary {
        const std::vector <std::string> dict;

    public:
        const int minWordSize_;
        Dictionary(const std::string &pathToDict, int minWordSize);

        bool isAWord(const std::string &s) const;
    };
} // namespace util