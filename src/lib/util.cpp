#include <util.hpp>

#include <algorithm>
#include <fstream>
#include <iterator>

#include <range/v3/view/remove_if.hpp>


bool util::Dictionary::isAWord(const std::string &s) const {
    return std::binary_search(dict.begin(), dict.end(), s);
}

util::Dictionary::Dictionary(const std::string &pathToDict, const int minWordSize) :
        dict{createDict(pathToDict, minWordSize)}, minWordSize_{minWordSize} {}

std::vector<std::string> util::createDict(const std::string &pathToDict, const int minWordSize) {
    std::ifstream reader{pathToDict};
    std::istream_iterator<std::string> iter{reader}, eof;
    std::vector<std::string> dict{iter, eof};
    return dict | ranges::views::remove_if([minWordSize](const std::string &s) { return s.size() < minWordSize; });;
}

