//
// Created by zach on 12/20/20.
//

#include "BuenosAires.hpp"

#include <iostream>

#include <fstream>

bool buenos_aires::Dictionary::isAWord(const std::string &s) const {
    return std::binary_search(dict.begin(), dict.end(), s);
}

buenos_aires::Dictionary::Dictionary(const std::string &pathToDict, const int minWordSize) :
        dict{createDict(pathToDict,minWordSize)} {}

std::vector<std::string> buenos_aires::createDict(const std::string &pathToDict, const int minWordSize) {
    std::ifstream reader{pathToDict};
    std::istream_iterator<std::string> iter{reader}, eof;
    std::vector<std::string> dict{iter, eof};
    return dict | views::remove_if([minWordSize](const std::string& s){return s.size() < minWordSize;});;
}

std::vector<std::string> buenos_aires::createOrderings(const Dictionary &dict, const std::string& city) {

    const int N = city.size();

    auto cityRepeated = city | views::cycle; // inf cityRepeated ... ABCDABCDABCDABCD...
    auto partialCities = cityRepeated | views::chunk(N - 1) | views::take(N); // ABC | DAB | CDA | BCD

    auto getPermutations = [](const std::string &str)
    {
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
        const int minWordSize = 2;
        for (auto iter = str.begin() + minWordSize; iter < str.end()-minWordSize+1; ++iter) {
            const std::string first = {str.begin(), iter};
            const std::string second = {iter, str.end()};
            if (dict.isAWord(first) && dict.isAWord(second)) {
                return false;
            }

        }
        return true;
    };

    auto permutedPartialCities = partialCities | views::transform(getPermutations) | ranges::to<std::vector>;
    auto vec = permutedPartialCities | views::join | ranges::to<std::vector>;

    auto searchSize = vec.size() * (N-2);
    std::cout << "There are " << searchSize << "combinations to look thru...\n";
    std::vector<std::string> candidates;
    int i = 0;
    for (const auto& str : vec){
        if(!hasNoPairsOfWords(str)){
            candidates.push_back(str);
        }
        double progressPct = static_cast<double>(i++) / static_cast<double>(searchSize);
    }

//    auto candidates = vec | views::remove_if(hasNoPairsOfWords) | ranges::to<std::vector>;
    return candidates;
}


int main() {
    buenos_aires::Dictionary dict{"/home/zach/solve-the-puzzler/datasets/wordlist.10000.txt", 2};
    std::cout << "Is apple a word? A: " << std::boolalpha << dict.isAWord("apple") << std::endl;
    std::cout << "Is a a word? A: " << std::boolalpha << dict.isAWord("a") << std::endl;
    std::cout << "Is asckun a word? A: " << std::boolalpha << dict.isAWord("asckun") << std::endl;
    std::cout << "Is alsore a word? A: " << std::boolalpha << dict.isAWord("alsore") << std::endl;

    std::cout << "BuenosAires Puzzle candidates: \n";
//    const auto possibleAnswers = buenos_aires::createOrderings(dict, "asif");
    const auto possibleAnswers = buenos_aires::createOrderings(dict, "buenosaires");
    for (const auto &s : possibleAnswers) {
        std::cout << s << std::endl;
    }

}


