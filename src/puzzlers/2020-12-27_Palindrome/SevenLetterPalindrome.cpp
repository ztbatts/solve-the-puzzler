#include "SevenLetterPalindrome.hpp"
#include "util.hpp"

#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <string>

#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/concat.hpp>

//std::vector<std::list<std::string>> palindromePhrase(const std::vector<util::Dictionary> &orderedDict) {
//    const int maxWordLength = orderedDict.size();
//    std::vector<std::list<std::string>> phrases;
//    std::list<std::string> phrase;
//
//    int i = maxWordLength;
//    while (i-- > 0) {
//        auto middleIdx = phrase.size() / 2; // truncates / rounds down
//        phrase.insert(middleIdx,)
//    }
//}


int main() {
    std::size_t wordSize = 7;
//    auto dict = palindrome7::createPalindromeDict("/home/zach/solve-the-puzzler/datasets/wordlist.10000.txt", wordSize);
    auto dict = util::createPalindromeDict("/home/zach/solve-the-puzzler/datasets/words_alpha.txt", wordSize);

    /// test dictionary
    std::cout << "Is apple a word? A: " << std::boolalpha << dict.isAWord("apple") << std::endl;
    std::cout << "Is a a word? A: " << std::boolalpha << dict.isAWord("a") << std::endl; // not if minWordSize > 1
    std::cout << "Is rotator a word? A: " << std::boolalpha << dict.isAWord("rotator") << std::endl;

    /// test isPalindromeString
    std::list<std::string> phrase{"madam", "im", "adam"};
//    auto phrase = ranges::views::concat("madam","im","adam");
    std::cout << "Is madam,im,adam a palindrome: " << std::boolalpha << util::isPalindromePhrase(phrase) << std::endl;
    std::string emptyStr;
    std::cout << "Is empty str a palindrome: " << std::boolalpha << util::isPalindromeString(emptyStr) << std::endl;

}


