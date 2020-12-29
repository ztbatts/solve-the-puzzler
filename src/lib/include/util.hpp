#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <range/v3/view/join.hpp>
#include <range/v3/view/all.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/take_last.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/common.hpp>
#include <range/v3/action/transform.hpp>
#include <range/v3/range/conversion.hpp>

namespace util {

struct Dictionary {
    const std::vector<std::string> words; /// Assumes input text file is ordered

    Dictionary(const std::string &pathToDict, int minWordSize);

    Dictionary(const std::string &pathToDict);

    Dictionary(std::vector<std::string> wordlist);

    bool isAWord(const std::string &s) const;
};

std::vector<std::string> createDict(const std::string &pathToDict);

std::vector<std::string> createSpecialDict(const std::string &pathToDict);

std::vector<std::string> createMinWordSizeDict(const std::string &pathToDict, int minWordSize);

std::vector<std::string> createSpecificWordSizeDict(const std::string &pathToDict, int wordSize);

Dictionary createPalindromeDict(const std::string &pathToDict, size_t wordsize);

std::vector<Dictionary> createAscendingWordSizeDictionaries(const std::string &pathToDict, size_t wordsize);

bool isPalindromeString(const std::string &word);

template<typename Container,
        typename = typename std::enable_if<std::is_same<
                std::decay_t<typename Container::value_type>, std::string>::value>::type>
bool isPalindromePhrase(const Container &phrase) {
    auto phraseConcat = phrase | ranges::views::transform([](const auto &elem) {
        return elem | ranges::views::all;
    }) | ranges::views::join | ranges::to<std::string>();
    return isPalindromeString(phraseConcat);
}

} // namespace util