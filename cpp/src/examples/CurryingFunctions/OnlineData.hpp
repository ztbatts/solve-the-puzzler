#pragma once

#include <tuple>
#include <utility>
#include <vector>

namespace av {

namespace detail {
// Helper function to call, in order, toVector on each element of the OnlineData
template<typename T, long unsigned... Is>
void for_each(const T& t, std::vector<double>& vec, std::integer_sequence<long unsigned, Is...>)
{
    auto l = {(std::get<Is>(t).toVector(vec), 0)...};
    (void)l;
}
} // namespace detail

/**
 * @brief A variadic class representing the OnlineData. Instantiate with the total vector length as first term,
 * and then the types of the various members as the following terms.
 * For example: MPCOnlineDataBase<60, Reference, Car, Cost, Constraints> foo;
 * Where 60 is the sum of the lenghts of Reference, Car, Cost, and Constraints
 */
template<size_t numParams, typename... Types>
class OnlineData
{
public:
    static std::size_t getDimension() { return numParams; }

    std::vector<double> toVector() const
    {
        std::vector<double> vec(numParams);
        detail::for_each(data_, vec, std::index_sequence_for<Types...>());
        return vec;
    }

    OnlineData(const Types&... t)
        : data_(t...)
    {}

    static OnlineData create(const Types&... args) // generic factory function
    {
        return OnlineData(args...);
    }

private:
    const std::tuple<Types...> data_;
};

} // namespace av