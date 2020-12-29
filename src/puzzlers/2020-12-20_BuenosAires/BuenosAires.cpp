//
// Created by zach on 12/20/20.
//

#include "BuenosAires.hpp"

#include <iostream>
#include <algorithm>
#include <map>

#include <range/v3/view/cycle.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/common.hpp>
#include <range/v3/view/single.hpp>

using namespace ranges;

std::vector<std::string> buenos_aires::findCandidateSolutions(const util::Dictionary &dict, const std::string &city) {
    constexpr int minWordSize = 3;
    const int N = city.size();
    // city = ABCD
    const auto cityRepeated = city | views::cycle; // infinitely repeated ... ABCDABCDABCDABCD...
    const auto partialCities =                     // ABC | DAB | CDA | BCD
            cityRepeated | views::chunk(N - 1) | views::take(N) |
            views::transform(ranges::to<std::string>());

    auto getAllPermutations = [](const std::string &str) {
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

    auto hasNoPairsOfWords = [&dict = std::as_const(dict)](const std::string &str) {
        for (auto iter = str.begin() + minWordSize; iter < str.end() - minWordSize + 1; ++iter) {
            const std::string first = {str.begin(), iter};
            const std::string second = {iter, str.end()};
            if (dict.isAWord(first) && dict.isAWord(second)) {
                return false;
            }

        }
        return true;
    };

    const auto permutedPartialCities = // vector of ranges : {ABC, ACB, BAC, BCA, CAB, CBA} | {...} | {...} | {...}
            partialCities | views::transform(getAllPermutations) | ranges::to_vector;
    const auto vec = permutedPartialCities | views::join | ranges::to<std::vector>; // flattened to a single vector

    const auto searchSize = vec.size() * (N - 2);
    std::cout << "There are " << searchSize << "combinations to look thru...\n";
    std::vector<std::string> candidates;

    for (const auto &str : vec) {
        if (!hasNoPairsOfWords(str)) {
            candidates.push_back(str);
        }
    }
    // haven't gotten this one to work yet
    //    auto candidates = vec | views::remove_if(hasNoPairsOfWords) | ranges::to<std::vector>;
    return candidates;
}


int main() {
    util::Dictionary dict{"/home/zach/solve-the-puzzler/datasets/wordlist.10000.txt", 2};

    /// test dictionary
    std::cout << "Is apple a word? A: " << std::boolalpha << dict.isAWord("apple") << std::endl;
    std::cout << "Is a a word? A: " << std::boolalpha << dict.isAWord("a") << std::endl; // not if minWordSize > 1
    std::cout << "Is asdfgh a word? A: " << std::boolalpha << dict.isAWord("asdfgh") << std::endl;


    std::cout << "BuenosAires Puzzle candidates: \n";

    //    const auto possibleAnswers = buenos_aires::createOrderings(words, "asactr"); // test
    const auto possibleAnswers = buenos_aires::findCandidateSolutions(dict, "buenosaires");

    for (const auto &s : possibleAnswers) {
        std::cout << s << std::endl;
    }
}

