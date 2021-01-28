#include "CurryingExamples.hpp"

#include <iostream>
#include <utility>
#include <vector>
#include <string>

/// greater : (double, double, double) → bool
bool greater(double first, double second, double third) {
    return first > second && second > third;
}

/// greaterManualCurried : double → (double → (double → bool))
auto greaterManualCurried(double first) {
    return [first](double second) {
        return [first, second](double third) {
            return first > second && second > third;
        };
    };
}

int main() {
    /// Currying -- the manual way
    std::cout << "3 > 2 > 1? " << std::boolalpha << greater(3, 2, 1) << "\n";

    std::cout << "3 > 2 > 1?  " << std::boolalpha << greaterManualCurried(3)(2)(1) << "\n";

    auto threeGt = greaterManualCurried(3);
    auto threeGtTwoGt = threeGt(2);
    std::cout << "3 > 2 > 1?  " << std::boolalpha << threeGtTwoGt(1) << "\n";

    /// Currying -- the automatic way
    auto gtAuto = CurriedCukic(greater);
    std::cout << "3 > 2 > 1?  " << std::boolalpha << gtAuto(3)(2)(1) << "\n";
    std::cout << "3 > 2 > 1?  " << std::boolalpha << gtAuto(3, 2, 1) << "\n";
    std::cout << "3 > 2 > 1?  " << std::boolalpha << gtAuto(3, 2)(1) << "\n";
    std::cout << "3 > 2 > 1?  " << std::boolalpha << gtAuto(3)(2, 1) << "\n";

}