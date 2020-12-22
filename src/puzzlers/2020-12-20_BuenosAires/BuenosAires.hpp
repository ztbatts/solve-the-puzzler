//
// Created by zach on 12/20/20.
//

#pragma once

#include <vector>
#include <string>
#include <iostream>


namespace buenos_aires {

    std::vector <std::string> createDict(const std::string &pathToDict, const int minWordSize);

    class Dictionary {
        const std::vector <std::string> dict;

    public:
        const int minWordSize_;
        Dictionary(const std::string &pathToDict, const int minWordSize);

        bool isAWord(const std::string &s) const;
    };

    std::vector <std::string> findCandidateSolutions(const Dictionary &dict, const std::string &city);

}


