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
}  // namespace type_traits
