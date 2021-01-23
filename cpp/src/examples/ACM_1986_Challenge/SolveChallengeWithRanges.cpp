#include "SolveChallengeWithRanges.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <cctype> // tolower, isalnum
#include <fstream>
#include <iterator>

#include <range/v3/action/sort.hpp>
#include <range/v3/view/istream.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/action/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/group_by.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/to_container.hpp>

using namespace ranges;

/// Read in path to text file
std::string readMainArgs(int argc, char *argv[]) {
    std::vector<std::string> all_args;
    if (argc > 1) {
        all_args.assign(argv + 1, argv + argc);
        return all_args.at(0);
    } else {
        throw std::runtime_error("Please provide path to text file as input.");
    }
}

/// Convert txt file to vector of strings
std::vector<std::string> createTxtStr(const std::string &pathToTxtFile) {
    std::ifstream reader{pathToTxtFile};
    std::istream_iterator<std::string> iter{reader}, eof;
    return {iter, eof};
}

/// wrapper for std::tolower, since it only works on chars
std::string string_to_lower(std::string c) {
    std::transform(c.begin(), c.end(), c.begin(),
                   [](char e) { return std::tolower(e); });
    return c;
}

/// wrapper for std::isalpha, since it only works on chars
std::string string_only_alnum(std::string s) {
    auto char_only_alum = [](auto c) {
        return !std::isalpha(static_cast<unsigned char>(c));
    };
    s.erase(std::remove_if(s.begin(), s.end(), char_only_alum), s.end());
    return s;
}

int main(int argc, char *argv[]) {
    const auto pathToTxtFile = readMainArgs(argc, argv);
    const auto rawStringVector = createTxtStr(pathToTxtFile);

    const auto words = rawStringVector | views::transform(string_to_lower)
                       | views::transform(string_only_alnum)
                       | views::remove_if(&std::string::empty)
                       | to_vector | actions::sort;

    const auto results =
            words | views::group_by(std::equal_to<>())
            | views::transform([](const auto &group) {
                const auto b = std::begin(group);
                const auto e = std::end(group);
                const auto count = distance(b, e);
                const auto word = *b;
                return std::make_pair(count, word);
            })
            | to_vector | actions::sort;

    int n = 10;
    for (const auto &value : results | views::reverse | views::take(n)) {
        std::cout << value.first << " " << value.second << std::endl;
    }
}
