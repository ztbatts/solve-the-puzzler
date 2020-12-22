//
// Created by zach on 12/20/20.
//

#include "BuenosAires.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

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

bool buenos_aires::Dictionary::isAWord(const std::string &s) const {
    return std::binary_search(dict.begin(), dict.end(), s);
}

buenos_aires::Dictionary::Dictionary(const std::string &pathToDict, const int minWordSize) :
        dict{createDict(pathToDict, minWordSize)}, minWordSize_{minWordSize} {}

std::vector <std::string> buenos_aires::createDict(const std::string &pathToDict, const int minWordSize) {
    std::ifstream reader{pathToDict};
    std::istream_iterator <std::string> iter{reader}, eof;
    std::vector <std::string> dict{iter, eof};
    return dict | views::remove_if([minWordSize](const std::string &s) { return s.size() < minWordSize; });;
}

std::vector <std::string> buenos_aires::findCandidateSolutions(const Dictionary &dict, const std::string &city) {

    const int N = city.size();
    // city = ABCD
    const auto cityRepeated = city | views::cycle; // infinitely repeated ... ABCDABCDABCDABCD...
    const auto partialCities = cityRepeated | views::chunk(N - 1) | views::take(N); // ABC | DAB | CDA | BCD

    auto getAllPermutations = [](const std::string &str) {
        std::vector <std::string> permutations{str};
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
        for (auto iter = str.begin() + dict.minWordSize_; iter < str.end() - dict.minWordSize_ + 1; ++iter) {
            const std::string first = {str.begin(), iter};
            const std::string second = {iter, str.end()};
            if (dict.isAWord(first) && dict.isAWord(second)) {
                return false;
            }

        }
        return true;
    };

    const auto permutedPartialCities = // vector of ranges : {ABC, ACB, BAC, BCA, CAB, CBA} | {...} | {...} | {...}
            partialCities | views::transform(getAllPermutations) | ranges::to<std::vector>;
    const auto vec = permutedPartialCities | views::join | ranges::to<std::vector>; // flattened to a single vector

    const auto searchSize = vec.size() * (N - 2);
    std::cout << "There are " << searchSize << "combinations to look thru...\n";
    std::vector <std::string> candidates;

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
    buenos_aires::Dictionary dict{"/home/zach/solve-the-puzzler/datasets/wordlist.10000.txt", 2};

    /// test dictionary
    std::cout << "Is apple a word? A: " << std::boolalpha << dict.isAWord("apple") << std::endl;
    std::cout << "Is a a word? A: " << std::boolalpha << dict.isAWord("a") << std::endl; // not if minWordSize > 1
    std::cout << "Is asdfgh a word? A: " << std::boolalpha << dict.isAWord("asdfgh") << std::endl;


    std::cout << "BuenosAires Puzzle candidates: \n";

    //    const auto possibleAnswers = buenos_aires::createOrderings(dict, "asactr"); // test
    const auto possibleAnswers = buenos_aires::findCandidateSolutions(dict, "buenosaires");

    for (const auto &s : possibleAnswers) {
        std::cout << s << std::endl;
    }
}

