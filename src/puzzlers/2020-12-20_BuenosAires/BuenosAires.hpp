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
#include <range/v3/action/push_back.hpp>
#include <range/v3/view/cycle.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/common.hpp>
#include <range/v3/view/single.hpp>

using namespace ranges;

namespace buenos_aires {


    void createOrderings() {

//    const std::string city = "BUENOSAIRES";
        const std::string city = "ABCD";
        const int N = city.size();

        auto cityRepeated = city | views::cycle; // inf cityRepeated ... ABCDABCDABCDABCD...
        auto partialCities = cityRepeated | views::chunk(N - 1) | views::take(N); // ABC | DAB | CDA | BCD

        auto getPermutations = [](const std::string &str) // s is a range
        {
            std::vector<std::string> permutations{str};
            auto s = str;
            while (std::prev_permutation(s.begin(), s.end())) {
                permutations.push_back(s);
            }
            s = str;
            while (std::next_permutation(s.begin(), s.end())) {
                permutations.push_back(s);
            }
            return permutations;
        };

        auto permutedPartialCities = partialCities | views::transform(getPermutations) | ranges::to<std::vector>;
//        auto permutedPartialCities = partialCities | views::transform(getPermutations);
        auto vec = permutedPartialCities | views::join | ranges::to<std::vector>;

        std::cout << "hey!\n";
    }


}


