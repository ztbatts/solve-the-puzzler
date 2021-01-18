
#include "util.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/common.hpp>
#include <range/v3/range/conversion.hpp>


std::vector<std::pair<std::string, std::string>> findAllPalindromePhrases(const std::string &pathToDict) {
    auto fullDict = util::createDict(pathToDict);
    auto firstWords = fullDict |
                      ranges::views::remove_if([](const std::string &s) { return s.size() != 5; }) |
                      ranges::views::remove_if([](const auto &s) { return s.at(2) != s.at(4); });

    auto twoWordDict = fullDict |
                       ranges::views::remove_if([](const std::string &s) { return s.size() != 2; });

    std::vector<std::pair<std::string, std::string>> res;
    auto nextChar = [](const auto letter) {
        return letter == 'z' ? 'a' : letter + 1;
    };
    for (const auto &first : firstWords) {
        auto slimDict = twoWordDict |
                        ranges::views::remove_if([&first](const auto &s) { return s.at(0) != first.at(1); }) |
                        ranges::views::remove_if(
                                [first, &nextChar](const auto &s) {
                                    return nextChar(s.at(1)) != first.at(0);
                                });
        auto secondWords = slimDict |
                           ranges::views::remove_if([&first, &nextChar](auto s) {
                               s.at(1) = nextChar(s.at(1));
                               return !util::isPalindromePhrase(std::vector<std::string>{first, s});
                           }) | ranges::to_vector;
        for (const auto &second : secondWords) {
            res.emplace_back(first, second);
        }
    }

    return res;
};

int main() {
//    const std::string pathToDict = "/home/zach/solve-the-puzzler/datasets/words_alpha.txt";
    const std::string pathToDict = "/home/zach/solve-the-puzzler/datasets/wordlist.10000.txt";

    auto pairs = findAllPalindromePhrases(pathToDict);

    for (const auto &pair : pairs) {
        std::cout << pair.first << ", " << pair.second << std::endl;
    }
}
