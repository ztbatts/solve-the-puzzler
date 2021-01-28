#include "common.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <iostream>
#include <functional>
#include <type_traits>

std::vector<std::string> only_alpha(std::vector<std::string> items) {
    std::transform(items.begin(), items.end(), items.begin(), only_alpha_str);
    return items;
}

std::vector<std::string> to_lower(std::vector<std::string> items) {
    std::transform(items.begin(), items.end(), items.begin(), to_lower_str);
    return items;
}

template<typename T>
std::unordered_map<T, unsigned int> count_occurrences(const std::vector<T> &items) {
    std::unordered_map<T, unsigned int> mapped_items;  // mutable...
    for (const auto &item : items) {
        ++mapped_items[item];
    }
    return mapped_items;
}

template<typename C,
        typename P1 = typename std::remove_cv<typename C::value_type::first_type>::type, // why isn't deduction working?
        typename P2 = typename C::value_type::second_type>
std::vector<std::pair<P2, P1>> reverse_pairs(const C &items) {
    std::vector<std::pair<P2, P1>> result;

    std::transform(
            std::begin(items), std::end(items),
            std::back_inserter(result),
            [](const std::pair<const P1, P2> &p) {
                return std::make_pair(p.second, p.first);
            }
    );

    return result;
}

template<typename P1, typename P2>
std::vector<std::pair<P1, P2>> sort_by_frequency(std::vector<std::pair<P1, P2>> items) {
    std::sort(items.begin(), items.end());  // assumes P1 = count
    return items;
}

template<typename P1, typename P2>
void print_pairs(const std::vector<std::pair<P1, P2>> &items) {
    for (const auto &item : items) {
        std::cout << "(" << item.first << ") : " << item.second << "\n";
    }
}

void print_common_words(const std::vector<std::string> &text) {
    print_pairs(
            sort_by_frequency(
                    reverse_pairs(
                            count_occurrences(
                                    to_lower(
                                            only_alpha(text)
                                    )
                            )
                    )
            )
    );
}

int main(int argc, char *argv[]) {
    const auto pathToTxtFile = readMainArgs(argc, argv);
    const auto rawStringVector = createTxtStr(pathToTxtFile);
    print_common_words(rawStringVector);
}


