//
// Created by zach on 12/20/20.
//

#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <range/v3/view/filter.hpp>
#include <range/v3/action/transform.hpp>
#include <range/v3/action/unique.hpp>
#include <range/v3/action/push_back.hpp>
#include <range/v3/view/cycle.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/common.hpp>
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/single.hpp>


using namespace ranges;

namespace buenos_aires {

    std::vector<std::string> createDict(const std::string &pathToDict,const int minWordSize);

    class Dictionary {
        const std::vector<std::string> dict;

    public:
        Dictionary(const std::string &pathToDict, const int minWordSize);

        bool isAWord(const std::string &s) const;
    };


    std::vector<std::string> createOrderings(const Dictionary &dict, const std::string &city);


}


