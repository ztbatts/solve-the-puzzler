#pragma once

#include <string>
#include <vector>
#include <exception>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cctype> // tolower, isalnum

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
std::string to_lower_str(std::string c) {
    std::transform(c.begin(), c.end(), c.begin(),
                   [](char e) { return std::tolower(e); });
    return c;
}

/// wrapper for std::isalpha, since it only works on chars
std::string only_alpha_str(std::string s) {
    auto char_only_alum = [](auto c) {
        return !std::isalpha(static_cast<unsigned char>(c));
    };
    s.erase(std::remove_if(s.begin(), s.end(), char_only_alum), s.end());
    return s;
}