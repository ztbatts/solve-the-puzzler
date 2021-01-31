#include "common.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


#include <range/v3/action/sort.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/group_by.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/to_container.hpp>

using namespace ranges;

int main(int argc, char *argv[]) {
    const auto pathToTxtFile = readMainArgs(argc, argv);
    const auto rawStringVector = createTxtStr(pathToTxtFile);

    const auto words = rawStringVector | views::transform(to_lower_str)
                       | views::transform(only_alpha_str)
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

    int n = 10000;
    for (const auto &value : results | views::reverse | views::take(n)) {
        std::cout << value.first << " " << value.second << std::endl;
    }
}
