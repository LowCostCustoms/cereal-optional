#ifndef CEREAL_OPTIONAL_OPTIONAL_NVP_HPP
#define CEREAL_OPTIONAL_OPTIONAL_NVP_HPP

#include "cereal/cereal.hpp"

namespace cereal {

/// @struct OptionalNameValuePair
/// @brief Name-value pair that can be default-initialized in case of name search failure
/// @tparam T Property type
/// @tparam TV Property value type
template<class T, class TV>
struct OptionalNameValuePair {
  // same as the cereal::NameValuePair::Type cause it's private
  using Type = typename std::conditional<std::is_array<typename std::remove_reference<T>::type>::value,
      typename std::remove_cv<T>::type,
      typename std::conditional<std::is_lvalue_reference<T>::value,
          T,
          typename std::decay<T>::type>::type>::type;
  
  
  // source property
  Type value;
  
  // default property value
  TV defaultValue;
  
  // property name
  const char *name;
  
  
  OptionalNameValuePair(const char *name, T &&value, TV &&defaultValue)
      : name(name), value(std::forward<T>(value)), defaultValue(std::forward<TV>(defaultValue)) { }
  
  /// Delete default copy constructor
  OptionalNameValuePair(const OptionalNameValuePair &) = delete;
  
  /// And enable move constructor by default
  OptionalNameValuePair(OptionalNameValuePair &&) = default;
};

/// Makes optional name-value pair
/// @param name Property name
/// @param option Property
/// @param default_value Default property value
/// @return Optional NVP
template<class T, class TV>
OptionalNameValuePair<T, TV> make_optional_nvp(const char *name, T &&option, TV &&defaultValue) {
    return { name, std::forward<T>(option), std::forward<TV>(defaultValue) };
};

/// Optional name-value pair builder method overload for std::string property name
template<class T, class TV>
OptionalNameValuePair<T, TV> make_optional_nvp(const std::string &name, T &&option, TV &&defaultValue) {
    return { name.c_str(), std::forward<T>(option), std::forward<TV>(defaultValue) };
};
}

#define NUM_ARGS_(_1, _2, TOTAL, ...) TOTAL
#define NUM_ARGS(...) NUM_ARGS_(__VA_ARGS__, 2, 1)

#define CONCATE_(X, Y) X##Y
#define CONCATE(MACRO, NUMBER) CONCATE_(MACRO, NUMBER)
#define VA_MACRO(MACRO, ...) CONCATE(MACRO, NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#define CEREAL_OPTIONAL_NVP_IMPL_1(T) ::cereal::make_optional_nvp(#T, T, typename std::remove_cv<typename std::remove_reference<decltype(T)>::type>::type())
#define CEREAL_OPTIONAL_NVP_IMPL_2(T, Default) ::cereal::make_optional_nvp(#T, T, Default)

/// Makes OptionalNameValuePair
/// first overload uses just property option like CEREAL_NVP, ex. CEREAL_OPTIONAL_NVP(x)
/// second overload uses property option and its fallback(default) value, ex. CEREAL_OPTIONAL_NVP(y, std::string())
#define CEREAL_OPTIONAL_NVP(...) VA_MACRO(CEREAL_OPTIONAL_NVP_IMPL_, __VA_ARGS__)


#endif //CEREAL_OPTIONAL_OPTIONAL_NVP_HPP
