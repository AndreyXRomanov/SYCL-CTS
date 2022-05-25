// FIXME remove pragma after moving to cts
#pragma once

#include <type_traits>

namespace type_traits {
template <typename T, typename = void>
struct is_dereferenceable : std::false_type {};

template <typename T>
struct is_dereferenceable<T, std::void_t<decltype(*std::declval<T>())>>
    : std::true_type {};

template <typename T>
using is_dereferenceable_t = typename is_dereferenceable<T>::type;

template <typename T>
inline constexpr bool is_dereferenceable_v = is_dereferenceable<T>::value;

template <typename T, typename = void>
struct is_equality_comparable : std::false_type {};

template <typename T>
struct is_equality_comparable<
    T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>>
    : std::true_type {};

template <typename T>
using is_equality_comparable_t = typename is_equality_comparable<T>::type;

template <typename T>
inline constexpr bool is_equality_comparable_v =
    is_equality_comparable<T>::value;
////////////////////////////////////////////////////
namespace has_field {

template <typename T, typename = void>
struct value_type : std::false_type {};

template <typename T>
struct value_type<T, std::void_t<typename std::iterator_traits<T>::value_type>>
    : std::true_type {};

template <typename T>
using value_type_t = typename value_type<T>::type;

template <typename T>
inline constexpr bool value_type_v = value_type<T>::value;

template <typename T, typename = void>
struct difference_type : std::false_type {};

template <typename T>
struct difference_type<
    T, std::void_t<typename std::iterator_traits<T>::difference_type>>
    : std::true_type {};

template <typename T>
using difference_type_t = typename difference_type<T>::type;

template <typename T>
inline constexpr bool difference_type_v = difference_type<T>::value;

template <typename T, typename = void>
struct reference : std::false_type {};

template <typename T>
struct reference<T, std::void_t<typename std::iterator_traits<T>::reference>>
    : std::true_type {};

template <typename T>
using reference_t = typename reference<T>::type;

template <typename T>
inline constexpr bool reference_v = reference<T>::value;

template <typename T, typename = void>
struct pointer : std::false_type {};

template <typename T>
struct pointer<T, std::void_t<typename std::iterator_traits<T>::pointer>>
    : std::true_type {};

template <typename T>
using pointer_t = typename pointer<T>::type;

template <typename T>
inline constexpr bool pointer_v = pointer<T>::value;

template <typename T, typename = void>
struct iterator_category : std::false_type {};

template <typename T>
struct iterator_category<T,
                         std::void_t<typename std::iterator_traits<T>::pointer>>
    : std::true_type {};

template <typename T>
using iterator_category_t = typename iterator_category<T>::type;

template <typename T>
inline constexpr bool iterator_category_v = iterator_category<T>::value;

}  // namespace has_field
////////////////////////////////////////////////////

template <typename T, typename = void>
struct can_pre_increment : std::false_type {};

template <typename T>
struct can_pre_increment<T, std::void_t<decltype(++std::declval<T>())>>
    : std::true_type {};

template <typename T>
using can_pre_increment_t = typename can_pre_increment<T>::type;

template <typename T>
inline constexpr bool can_pre_increment_v = can_pre_increment<T>::value;

template <typename T, typename = void>
struct can_post_increment : std::false_type {};

template <typename T>
struct can_post_increment<T, std::void_t<decltype(std::declval<T>()++)>>
    : std::true_type {};

template <typename T>
using can_post_increment_t = typename can_post_increment<T>::type;

template <typename T>
inline constexpr bool can_post_increment_v = can_post_increment<T>::value;

template <typename T, typename = void>
struct can_post_decrement : std::false_type {};

template <typename T>
struct can_post_decrement<T, std::void_t<decltype(std::declval<T>()--)>>
    : std::true_type {};

template <typename T>
using can_post_decrement_t = typename can_post_decrement<T>::type;

template <typename T>
inline constexpr bool can_post_decrement_v = can_post_decrement<T>::value;

template <typename T, typename = void>
struct can_pre_decrement : std::false_type {};

template <typename T>
struct can_pre_decrement<T, std::void_t<decltype(--(std::declval<T>()))>>
    : std::true_type {};

template <typename T>
using can_pre_decrement_t = typename can_pre_decrement<T>::type;

template <typename T>
inline constexpr bool can_pre_decrement_v = can_pre_decrement<T>::value;

namespace has_operator {

template <typename T, typename = void>
struct append : std::false_type {};

template <typename T>
struct append<T, std::void_t<decltype(std::declval<T>() += 2)>>
    : std::true_type {};

template <typename T>
using append_t = typename append<T>::type;

template <typename T>
inline constexpr bool append_v = append<T>::value;

template <typename T, typename = void>
struct reduce : std::false_type {};

template <typename T>
struct reduce<T, std::void_t<decltype(std::declval<T>() -= 2)>>
    : std::true_type {};

template <typename T>
using reduce_t = typename reduce<T>::type;

template <typename T>
inline constexpr bool reduce_v = reduce<T>::value;

template <typename T, typename = void>
struct diff_type_plus_iterator : std::false_type {};

template <typename T>
struct diff_type_plus_iterator<T, std::void_t<decltype(1 + std::declval<T>())>>
    : std::true_type {};

template <typename T>
using diff_type_plus_iterator_t = typename diff_type_plus_iterator<T>::type;

template <typename T>
inline constexpr bool diff_type_plus_iterator_v =
    diff_type_plus_iterator<T>::value;

template <typename T, typename = void>
struct iterator_plus_diff_type : std::false_type {};

template <typename T>
struct iterator_plus_diff_type<T, std::void_t<decltype(std::declval<T>() + 1)>>
    : std::true_type {};

template <typename T>
using iterator_plus_diff_type_t = typename iterator_plus_diff_type<T>::type;

template <typename T>
inline constexpr bool iterator_plus_diff_type_v =
    iterator_plus_diff_type<T>::value;

template <typename T, typename = void>
struct iterator_minus_diff_type : std::false_type {};

template <typename T>
struct iterator_minus_diff_type<T, std::void_t<decltype(std::declval<T>() - 1)>>
    : std::true_type {};

template <typename T>
using iterator_minus_diff_type_t = typename iterator_minus_diff_type<T>::type;

template <typename T>
inline constexpr bool iterator_minus_diff_type_v =
    iterator_minus_diff_type<T>::value;

template <typename T, typename = void>
struct iterator_minus_iterator : std::false_type {};

template <typename T>
struct iterator_minus_iterator<
    T, std::void_t<decltype(std::declval<T>() - std::declval<T>())>>
    : std::true_type {};

template <typename T>
using iterator_minus_iterator_t = typename iterator_minus_iterator<T>::type;

template <typename T>
inline constexpr bool iterator_minus_iterator_v =
    iterator_minus_iterator<T>::value;

template <typename T, typename = void>
struct subscript : std::false_type {};

template <typename T>
struct subscript<T, std::void_t<decltype(std::declval<T>()[0])>>
    : std::true_type {};

template <typename T>
using subscript_t = typename subscript<T>::type;

template <typename T>
inline constexpr bool subscript_v = subscript<T>::value;

template <typename T, typename = void>
struct greater : std::false_type {};

template <typename T>
struct greater<T, std::void_t<decltype(std::declval<T>() > std::declval<T>())>>
    : std::true_type {};

template <typename T>
using greater_t = typename greater<T>::type;

template <typename T>
inline constexpr bool greater_v = greater<T>::value;

template <typename T, typename = void>
struct lower : std::false_type {};

template <typename T>
struct lower<T, std::void_t<decltype(std::declval<T>() < std::declval<T>())>>
    : std::true_type {};

template <typename T>
using lower_t = typename lower<T>::type;

template <typename T>
inline constexpr bool lower_v = lower<T>::value;

template <typename T, typename = void>
struct greater_or_equal : std::false_type {};

template <typename T>
struct greater_or_equal<
    T, std::void_t<decltype(std::declval<T>() >= std::declval<T>())>>
    : std::true_type {};

template <typename T>
using greater_or_equal_t = typename greater_or_equal<T>::type;

template <typename T>
inline constexpr bool greater_or_equal_v = greater_or_equal<T>::value;

template <typename T, typename = void>
struct lower_or_equal : std::false_type {};

template <typename T>
struct lower_or_equal<
    T, std::void_t<decltype(std::declval<T>() <= std::declval<T>())>>
    : std::true_type {};

template <typename T>
using lower_or_equal_t = typename lower_or_equal<T>::type;

template <typename T>
inline constexpr bool lower_or_equal_v = lower_or_equal<T>::value;

}  // namespace has_operator
}  // namespace type_traits
