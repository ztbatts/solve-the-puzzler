#include <util.hpp>

#include <algorithm>
#include <fstream>
#include <iterator>
#include <type_traits>

#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/algorithm/equal.hpp>


namespace util {

bool Dictionary::isAWord(const std::string &s) const {
    return std::binary_search(dict.begin(), dict.end(), s);
}

Dictionary::Dictionary(const std::string &pathToDict, const int minWordSize) :
        dict{createMinWordSizeDict(pathToDict, minWordSize)} {}

Dictionary::Dictionary(std::vector<std::string> wordlist) : dict{std::move(wordlist)} {}

Dictionary::Dictionary(const std::string &pathToDict) : Dictionary(createDict(pathToDict)) {}

std::vector<std::string> createMinWordSizeDict(const std::string &pathToDict, const int minWordSize) {
    auto dict = createDict(pathToDict);
    return dict | ranges::views::remove_if([minWordSize](const std::string &s) { return s.size() < minWordSize; }) |
           ranges::to_vector;
}

std::vector<std::string> createSpecificWordSizeDict(const std::string &pathToDict, const int wordSize) {
    auto dict = createDict(pathToDict);
    return dict | ranges::views::remove_if([wordSize](const std::string &s) { return s.size() != wordSize; }) |
           ranges::to_vector;
}

bool isPalindromeString(const std::string &word) {
    if (word.empty()) {
        return false;
    }
    return ranges::equal(word | ranges::views::all, word | ranges::views::reverse);
}

Dictionary createPalindromeDict(const std::string &pathToDict, size_t wordsize) {
    auto dict = createDict(pathToDict);
    return dict |
           ranges::views::remove_if([wordsize](const std::string &s) { return s.size() != wordsize; }) |
           ranges::views::remove_if(isPalindromeString) |
           ranges::to_vector;
}

std::vector<Dictionary> createAscendingWordSizeDictionaries(const std::string &pathToDict, const size_t wordsize) {
    std::vector<Dictionary> dicts;

    for (size_t i = 0; i < wordsize; ++i) {
        dicts.emplace_back(createSpecificWordSizeDict(pathToDict, i));
    }
    return dicts;
}

std::vector<std::string> createDict(const std::string &pathToDict) {
    std::ifstream reader{pathToDict};
    std::istream_iterator<std::string> iter{reader}, eof;
    return std::vector<std::string>{iter, eof};
}


} // namespace util