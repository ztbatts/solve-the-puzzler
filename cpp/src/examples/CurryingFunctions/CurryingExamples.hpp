#pragma once

#include <type_traits>
#include <utility>
#include <tuple>

/// From Ivan Cukic's book ... giving some weird (uninitialized?) errors
template<typename Function, typename... CapturedArgs>
class CurriedCukic {
private:
    using CapturedArgsTuple =
    std::tuple<std::decay_t<CapturedArgs>...>;

    template<typename... Args>
    static auto capture_by_copy(Args &&... args) {
        return std::tuple<std::decay_t<Args>...>(
                std::forward<Args>(args)...);
    }

public:
    CurriedCukic(Function function, CapturedArgs... args)
            : m_function(function), m_captured(capture_by_copy(std::move(args)...)) {
    }

    CurriedCukic(Function function,
            std::tuple<CapturedArgs...> args)
            : m_function(function), m_captured(std::move(args)) {
    }

    template<typename... NewArgs>
    auto operator()(NewArgs &&... args) const {
        auto new_args = capture_by_copy(
                std::forward<NewArgs>(args)...);

        auto all_args = std::tuple_cat(
                m_captured, std::move(new_args));

        if constexpr(std::is_invocable_v<Function,
                CapturedArgs..., NewArgs...>) {

            return std::apply(m_function, all_args);

        } else {
            return CurriedCukic<Function,
                    CapturedArgs...,
                    NewArgs...>(
                    m_function, all_args);
        }
    }

private:
    Function m_function;
//    std::tuple<CapturedArgs...> m_captured;
    CapturedArgsTuple m_captured;
};






/// https://stackoverflow.com/questions/152005/how-can-currying-be-done-in-c/26768388#26768388
//template< class, class = std::void_t<> > struct
//needs_unapply : std::true_type { };
//
//template< class T > struct
//needs_unapply<T, std::void_t<decltype(std::declval<T>()())>> : std::false_type { };
//
//template <typename F> auto
//Curried(F&& f) {
//    /// Check if f() is a valid function call. If not we need
//    /// to curry at least one argument:
//    if constexpr (needs_unapply<decltype(f)>::value) {
//        return [=](auto&& x) {
//            return Curried(
//                    [=](auto&&...xs) -> decltype(f(x,xs...)) {
//                        return f(x,xs...);
//                    }
//            );
//        };
//    }
//    else {
//        /// If 'f()' is a valid call, just call it, we are done.
//        return f();
//    }
//}






/// https://stackoverflow.com/questions/152005/how-can-currying-be-done-in-c/26768388#26768388
/// https://gcc.godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAKxAEZTUAHAvVAOwGdK0AbVAV2J4OmAIIcAtiADkABmmk0Exnh6YA8mwDCCAIZtgmGfICUpDgOLIj0gKQAmAMx42yHvywBqW460EAnoyYAPoExLqEHD7YtrKiDs6u7l4%2BWgBm/K4s7Lo80bHxTi5uHpjevsgcBPio%2BXEFAPQN3k5YaS5lAArYAEoAYthaACrBWqKdQwCqPdjBAEIzogDSAMrBAOJaWgU7RWltnt39gyNjE9OzC9jLa5vb9U6eT20dnn3qPQDqoj0AIhAANR%2BAElRHMADLYEyeKroEAgNIkADuumI6FSWDcASCgJBYMhJmiuJ6oIhUN2jienhebDKZymM2C7y%2BP3%2BQJJ%2BKh1MwBAiPHhQWIaUwyAIwWQumYghCBAxIp42MwxNJBPyAHY5m8Pt8/srOdDbGrfhTMDwRBSqTSysydWy8WToeyVTEHpTnph2rTPPSLkztay9Q7PE7OSa2Pg0js4mxdBJMBxGLprNzeapvBqClTPE1moLhaLxZKCNLQp5hJ5eQBrTBsTxpYioCSeBAEAiMEBNKpJyuoABumCFfCRADolA1dA1HLQACy0WQADnnsga9gAbPY1/YAJyZqkETDKHi6fflLRuXQcDieIbRTz8DguYDeOJZvMisUSqXEGXlY0vrNUrC8JoOGhCsDGPChKkQEgMIwQ8L2uT8CE37Ct%2BriYKkN6ONg8KIe4mCkLuAEkaRpEwahA41tYwRIuEjCCtB1Twt%2BEh9ihHpURhUG%2BNhMQ4aQ175I4cxRqIWb7oex6Yb4njnpegnyVePi/DCzEgL2qB4OgPHbDh5QuuJgFhPwoqeLSmDoBwwSZJKjA8P4nggGpcIgCZMqBGUhqaoaxoiWJEkHvZ0mpHJR6XteBnEWpxCmQQ5mYJZ1m2QxDlYYJMGadpumYgqnkQDBuX4VhRImBAJiEjht7OTBaS5CIoSeemPlGj4on1K19RxJJwUnqkioxnGbx1KIuWKhAuj8EQ0LIIIxD%2BBAfQOKuy11gaGb/k8eBpHJ7BVJgAAejDEJ4EBYKm/IgBZVk2TGqX%2BHKWL5WklW4RpSGYOt7VGSR37FsQta2AArHMkaOL8PqMjaAYvcD/yTUQy2rQdX3RWRf2CLWs3EPNEBo2R3ggwdKmQ7M0O6ijglgxD4wMmT/q6rDQPw1NtRrstw6cwdHDQgAtLeY3PYtDP/JT5OizznPDhVzX4wTngYwDdbCyyFNmOLEDcyYUuVd98tZr5csAbrRuG/5m3pn%2BP2eKaIgKzymPKybHVWwUVSxWZEo8JB8Xeb5cm5Hk5vxN1QVHn1vgDbG1oC/K40I6gBpxNj80ABqLUja5rbLFuK4DIPU6Tfqq/8TMs4j7NZyjOfW08sRbttu2cPuR0nQV6lwRw0dMa5mK6P4OVx/lKPRIogc8W9%2BHIajFu/Q7StpOVbWm51tdUrbXkbWvWZ53Jc3%2BOnRskcDczE%2BDRca5TdYk7Tvoa2XE2s5nq5S1rnj8/pgs4ovl/qyLmuS05jLP2s99a7x/v/MWkDAHS2XqAsivlnbb0tnA62ZtvqGy6qIFw8UJARDYEvDqesqQJzrL%2BQmolmaPyIK/Hm79Y5PRxAnGea9667wfAAL0wKgNIUsAFIINq1YOBsLYpwPhAY6OCXp4w3AACVNHwFoQMogbjKg4ewnwSA8HRKoiAXseBILYfPLG%2B907SPUVoQO6i1EbgALKYV0eoz4hAEDWJkfYfQD1HEbjYPwCQAAjAcbj1E8OCRuVEwAVH2DKvowxq8xIFGkGYfk0ggYKDYDIWgChUAyG2PYUS%2BSYSWGTAkLJpACDGCSWYSsIAgZbmHLIIG055xbnXM06c9ggayDVNOUgKTpzpMqQwGQCguCyHKZUswcBYBICUCoNQZAKB6MbPMgcIBgBqg4HdDgCBUAEFIO0BUA4uAQH8UMpQcY2AEE0A5IZ%2BBvyijwP2LgcgFA4NNJMhgzBwIvN5rCFSyAHAFLmLQDh791D2CSX0mQaTSAZNecMuwThaCeCRC4zwB15yrl5quacnhgDIGQJ4NUp0tmSh2XskwCgKmvIqqQGpnThy0FaWqIGQM1SODXKuWgjg1TQukAMuFQycnSFGSAcZNLTCkGmYgEAAg2xTXINwFZqg1n0EsoQEgdBkkwsGQikVpTUXosxdi3F%2BLCXEtJds3ZBAqUTNpdUugQNhw9PnI4ZpshaAtJ5eyoG/LBXwvkIisVErJk6ukJCoV%2BqRn2tMGYfsxAHzsBANOIAA
#include <type_traits>
#include <functional>
#include <cstdio>

// #define PERFECT_CAPTURE_BREAKS_GCC

#ifdef PERFECT_CAPTURE_BREAKS_GCC
#   define FORWARD(VARIABLE) std::forward<decltype(VARIABLE)>(VARIABLE)
#   define CAPTURE_FORWARD(VARIABLE) detail::perfect_capture_t<decltype(VARIABLE)>{ FORWARD(VARIABLE) }
#else
#   define FORWARD(VARIABLE) VARIABLE
#   define CAPTURE_FORWARD(VARIABLE) VARIABLE
#endif

namespace detail {
    /// perfect_capture_t is taken from http://stackoverflow.com/a/31410880/2622629
    template <class T> using
    perfect_capture_t =
    std::conditional_t<std::is_lvalue_reference<T>::value,
            std::reference_wrapper<std::remove_reference_t<T>>, T>;

    template< class, class = std::void_t<> >
    struct needs_unapply : std::true_type { };

    template< class T >
    struct needs_unapply<T, std::void_t<decltype(std::declval<T>()())>> : std::false_type { };
}

template <typename F>
decltype(auto) CurriedJulian(F&& f) {
    if constexpr (detail::needs_unapply<decltype(f)>::value) {
        return [f=CAPTURE_FORWARD(f)](auto&& x) {
            return CurriedJulian(
                    [x=CAPTURE_FORWARD(x), f=CAPTURE_FORWARD(f)](auto&&...xs) -> decltype(f(FORWARD(x),FORWARD(xs)...)) {
                        return f(FORWARD(x),FORWARD(xs)...);
                    }
            );
        };
    }
    else return f();
}









//template<typename T, typename... Args>
//T create(Args... args) {
//    return T(args...);
//}


