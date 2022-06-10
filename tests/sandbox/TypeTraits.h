/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides helping functions to know that provided type have the following
//  things:
//    - Some fields (e.g. value_type or difference_type)
//    - Perform a function (e.g. dereference, subscript operator)
//    - Perform an increment, decrement, post_increment or other algorithm
//        operations
//    - Perform a comparison operators (e.g. greater, less or less_or_equal)
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_TYPE_TRAITS_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_TYPE_TRAITS_H

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
struct has_subscript_operator : std::false_type {};

template <typename T>
struct has_subscript_operator<T, std::void_t<decltype(std::declval<T>()[0])>>
    : std::true_type {};

template <typename T>
using has_subscript_operator_t = typename has_subscript_operator<T>::type;

template <typename T>
inline constexpr bool has_subscript_operator_v =
    has_subscript_operator<T>::value;

// Provide code to verify that provided datatype has different fields
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

// Provide code to verify that provided datatype has compound assignment
namespace compound_assignment {
template <typename T, typename RightOperandT = int, typename = void>
struct addition : std::false_type {};

template <typename T, typename RightOperandT>
struct addition<
    T, RightOperandT,
    // Need reference here to handle rval of native C++ types like int
    std::void_t<decltype(std::declval<T&>() += std::declval<RightOperandT>())>>
    : std::true_type {};

template <typename T, typename RightOperandT = int>
using addition_t = typename addition<T, RightOperandT>::type;

template <typename T, typename RightOperandT = int>
inline constexpr bool addition_v = addition<T, RightOperandT>::value;

template <typename T, typename RightOperandT = int, typename = void>
struct subtraction : std::false_type {};

template <typename T, typename RightOperandT>
struct subtraction<
    T, RightOperandT,
    // Need reference here to handle rval of native C++ types like int
    std::void_t<decltype(std::declval<T&>() -= std::declval<RightOperandT>())>>
    : std::true_type {};

template <typename T, typename RightOperandT = int>
using subtraction_t = typename subtraction<T>::type;

template <typename T, typename RightOperandT = int>
inline constexpr bool subtraction_v = subtraction<T>::value;
}  // namespace compound_assignment

// Provide code to verify that provided datatype has arithmetic operators
namespace has_arithmetic {

template <typename LeftOperand, typename RightOperand, typename = void>
struct addition : std::false_type {};

template <typename LeftOperand, typename RightOperand>
struct addition<LeftOperand, RightOperand,
                std::void_t<decltype(std::declval<LeftOperand>() +
                                     std::declval<RightOperand>())>>
    : std::true_type {};

template <typename LeftOperand, typename RightOperand>
using addition_t = typename addition<LeftOperand, RightOperand>::type;

template <typename LeftOperand, typename RightOperand>
inline constexpr bool addition_v = addition<LeftOperand, RightOperand>::value;

template <typename LeftOperand, typename RightOperand, typename = void>
struct subtraction : std::false_type {};

template <typename LeftOperand, typename RightOperand>
struct subtraction<LeftOperand, RightOperand,
                   std::void_t<decltype(std::declval<LeftOperand>() -
                                        std::declval<RightOperand>())>>
    : std::true_type {};

template <typename LeftOperand, typename RightOperand>
using subtraction_t = typename subtraction<LeftOperand, RightOperand>::type;

template <typename LeftOperand, typename RightOperand>
inline constexpr bool subtraction_v =
    subtraction<LeftOperand, RightOperand>::value;

template <typename T, typename = void>
struct pre_increment : std::false_type {};

template <typename T>
// Need reference here to handle rval of native C++ types like int
struct pre_increment<T, std::void_t<decltype(++std::declval<T&>())>>
    : std::true_type {};

template <typename T>
using pre_increment_t = typename pre_increment<T>::type;

template <typename T>
inline constexpr bool pre_increment_v = pre_increment<T>::value;

template <typename T, typename = void>
struct post_increment : std::false_type {};

template <typename T>
// Need reference here to handle rval of native C++ types like int
struct post_increment<T, std::void_t<decltype(std::declval<T&>()++)>>
    : std::true_type {};

template <typename T>
using post_increment_t = typename post_increment<T>::type;

template <typename T>
inline constexpr bool post_increment_v = post_increment<T>::value;

template <typename T, typename = void>
struct post_decrement : std::false_type {};

template <typename T>
// Need reference here to handle rval of native C++ types like int
struct post_decrement<T, std::void_t<decltype(std::declval<T&>()--)>>
    : std::true_type {};

template <typename T>
using post_decrement_t = typename post_decrement<T>::type;

template <typename T>
inline constexpr bool post_decrement_v = post_decrement<T>::value;

template <typename T, typename = void>
struct pre_decrement : std::false_type {};

template <typename T>
// Need reference here to handle rval of native C++ types like int
struct pre_decrement<T, std::void_t<decltype(--std::declval<T&>())>>
    : std::true_type {};

template <typename T>
using pre_decrement_t = typename pre_decrement<T>::type;

template <typename T>
inline constexpr bool pre_decrement_v = pre_decrement<T>::value;
}  // namespace has_arithmetic

// Provide code to verify that provided datatype has comparison operators
namespace has_comparison {
template <typename T, typename = void>
struct is_equal : std::false_type {};

template <typename T>
struct is_equal<T,
                std::void_t<decltype(std::declval<T>() == std::declval<T>())>>
    : std::true_type {};

template <typename T>
using is_equal_t = typename is_equal<T>::type;

template <typename T>
inline constexpr bool is_equal_v = is_equal<T>::value;

template <typename T, typename = void>
struct not_equal : std::false_type {};

template <typename T>
struct not_equal<T,
                 std::void_t<decltype(std::declval<T>() != std::declval<T>())>>
    : std::true_type {};

template <typename T>
using not_equal_t = typename not_equal<T>::type;

template <typename T>
inline constexpr bool not_equal_v = not_equal<T>::value;

template <typename T, typename = void>
struct greater_than : std::false_type {};

template <typename T>
struct greater_than<
    T, std::void_t<decltype(std::declval<T>() > std::declval<T>())>>
    : std::true_type {};

template <typename T>
using greater_than_t = typename greater_than<T>::type;

template <typename T>
inline constexpr bool greater_than_v = greater_than<T>::value;

template <typename T, typename = void>
struct less_than : std::false_type {};

template <typename T>
struct less_than<T,
                 std::void_t<decltype(std::declval<T>() < std::declval<T>())>>
    : std::true_type {};

template <typename T>
using less_than_t = typename less_than<T>::type;

template <typename T>
inline constexpr bool less_than_v = less_than<T>::value;

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
struct less_or_equal : std::false_type {};

template <typename T>
struct less_or_equal<
    T, std::void_t<decltype(std::declval<T>() <= std::declval<T>())>>
    : std::true_type {};

template <typename T>
using less_or_equal_t = typename less_or_equal<T>::type;

template <typename T>
inline constexpr bool less_or_equal_v = less_or_equal<T>::value;

}  // namespace has_comparison
}  // namespace type_traits

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_TYPE_TRAITS_H
