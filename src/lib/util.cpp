#include <util.hpp>

#include <algorithm>
#include <fstream>
#include <iterator>
#include <type_traits>

#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/algorithm/equal.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/range/conversion.hpp>


namespace util {

bool Dictionary::isAWord(const std::string &s) const {
    return std::binary_search(words.begin(), words.end(), s);
}

Dictionary::Dictionary(const std::string &pathToDict, const int minWordSize) :
        words{createMinWordSizeDict(pathToDict, minWordSize)} {}

Dictionary::Dictionary(std::vector<std::string> wordlist) : words{std::move(wordlist) | ranges::actions::sort} {}

Dictionary::Dictionary(const std::string &pathToDict) : Dictionary(createDict(pathToDict)) {}

std::vector<std::string> createMinWordSizeDict(const std::string &pathToDict, const int minWordSize) {
    auto dict = createDict(pathToDict);
    return dict | ranges::views::remove_if([minWordSize](const std::string &s) { return s.size() < minWordSize; }) |
           ranges::to<std::vector>();
}

std::vector<std::string> createSpecificWordSizeDict(const std::string &pathToDict, const int wordSize) {
    auto dict = createDict(pathToDict);
    return dict | ranges::views::remove_if([wordSize](const std::string &s) { return s.size() != wordSize; }) |
           ranges::to<std::vector>();
}

bool isPalindromeString(const std::string &word) {
    if (word.empty()) {
        return false;
    }
    const bool isPalindrome = ranges::equal(word | ranges::views::all, word | ranges::views::reverse);
    return isPalindrome;
}

Dictionary createPalindromeDict(const std::string &pathToDict, size_t wordsize) {
    auto dict = createDict(pathToDict);
    return dict |
           ranges::views::remove_if([wordsize](const std::string &s) { return s.size() != wordsize; }) |
           ranges::views::remove_if([](const auto &s) { return !util::isPalindromeString(s); }) |
           ranges::to_vector;
}

std::vector<Dictionary> createAscendingWordSizeDictionaries(const std::string &pathToDict, const size_t wordsize) {
    std::vector<Dictionary> dicts;
    for (size_t i = 0; i <= wordsize; ++i) {
        dicts.emplace_back(createSpecificWordSizeDict(pathToDict, i));
    }
    return dicts;
}

std::vector<std::string> createDict(const std::string &pathToDict) {
    std::ifstream reader{pathToDict};
    std::istream_iterator<std::string> iter{reader}, eof;
    return std::vector<std::string>{iter, eof} | ranges::actions::sort;
}


} // namespace util