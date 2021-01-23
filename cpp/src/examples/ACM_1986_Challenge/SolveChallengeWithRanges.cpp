#include "SolveChallengeWithRanges.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <locale> // tolower, isalnum
#include <fstream>
#include <iterator>
#include <exception>

#include <range/v3/view/istream.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/istream.hpp>
#include <range/v3/to_container.hpp>

using namespace ranges;

std::string readMainArgs(int argc, char *argv[]) {
    /// Read in path to text file
    std::vector<std::string> all_args;
    if (argc > 1) {
        all_args.assign(argv + 1, argv + argc);
        return all_args.at(0);
    } else {
        throw std::runtime_error("Please provide path to text file as input.");
    }
}

std::vector<std::string> createTxtStr(const std::string &pathToTxtFile) {
    std::ifstream reader{pathToTxtFile};
    std::istream_iterator<std::string> iter{reader}, eof;
    return {iter, eof};
}

auto createTxtRange(const std::string &pathToTxtFile) {
    std::ifstream reader{pathToTxtFile};
    std::istream_iterator<std::string> iter{reader}, eof;
    return ranges::subrange{iter, eof};
}

//std::string string_to_lower(const std::string &s) {
//    auto to_lower = [](const auto& c){ return std::tolower(c,std::locale());};
//    return s | ranges::view::transform(to_lower);
//}

//std::string string_only_alnum(const std::string &s) {
//    return s | view::filter(std::isalnum);
//}


int main(int argc, char *argv[]) {
    const auto pathToTxtFile = readMainArgs(argc, argv);
    auto txt = createTxtStr(pathToTxtFile);
//    auto txt = createTxtRange(pathToTxtFile);

    for (const auto &word : txt) {
        std::cout << word << "|";
    }

    auto to_lower = [](const auto &c) { return std::tolower(c, std::locale("en_US.UTF-8")); };
    auto string_only_alnum = [](const auto c) { return std::isalnum(c,std::locale("en_US.UTF-8")); };


    auto words = txt | view::transform(to_lower)
                 | view::remove_if(string_only_alnum);
//                                     | view::remove_if(&std::string::empty);

//    std::vector<std::string> words = txt
//                                     | view::transform(std::tolower)
//                                     | view::transform(std::isalnum)
//                                     | view::remove_if(&std::string::empty);

    for (const auto &word : words) {
        std::cout << word << "|";
    }

}
