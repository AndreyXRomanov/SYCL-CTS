#pragma once
#include <initializer_list>
#include <type_traits>
#include <utility>
#include <vector>

struct LegacyIterator {
  std::vector<int> v;
  size_t index = 0;
  LegacyIterator(std::initializer_list<int> l) : v(l){};
  LegacyIterator& operator++() {
    index++;
    return *this;
  };
  int& operator*() { return v[index]; };
};

struct LegacyInputIterator {
  std::vector<int> v;
  size_t index = 0;
  LegacyInputIterator(std::initializer_list<int> l) : v(l){};
  LegacyInputIterator& operator++() {
    index++;
    return *this;
  };
  LegacyInputIterator& operator++(int) {
    index++;
    return *this;
  };

  friend bool operator!=(LegacyInputIterator a, LegacyInputIterator b) {
    return a.index != b.index;
  }
  friend bool operator==(LegacyInputIterator a, LegacyInputIterator b) {
    return a.index == b.index;
  }
  int& operator*() { return v[index]; };
};

struct LegacyOutputIterator {
  std::vector<int> v;
  size_t index = 0;
  LegacyOutputIterator(std::initializer_list<int> l) : v(l){};
  LegacyOutputIterator& operator++() {
    index++;
    return *this;
  };
  LegacyOutputIterator& operator++(int) {
    index++;
    return *this;
  };

  friend bool operator==(LegacyOutputIterator a, LegacyOutputIterator b) {
    return a.index == b.index;
  }
  int& operator*() { return v[index]; };
};

class LegacyForwardIterator {
 public:
  using T = int;

  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  LegacyForwardIterator() : v(), i(0) {}
  LegacyForwardIterator(std::initializer_list<int> l) : v(l){};

  reference operator*() { return v[i]; }

  LegacyForwardIterator& operator++() {
    ++i;
    return *this;
  }

  LegacyForwardIterator operator++(int) {
    LegacyForwardIterator r(*this);
    ++i;
    return r;
  }

  size_t size() { return 5; }

  bool operator!=(const LegacyForwardIterator& r) const { return i != r.i; }
  bool operator==(const LegacyForwardIterator& r) const { return i == r.i; }

 private:
  std::vector<int> v{};
  int i = 0;
};

class LegacyBidirectionalIterator {
 public:
  using T = int;

  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  LegacyBidirectionalIterator() : v(), i(0) {}
  LegacyBidirectionalIterator(std::initializer_list<int> l) : v(l){};

  reference operator*() { return v[i]; }
  pointer operator->() { return &(v[i]); }
  reference operator[](int m) { return v[i + m]; }

  LegacyBidirectionalIterator& operator++() {
    ++i;
    return *this;
  }
  LegacyBidirectionalIterator& operator--() {
    --i;
    return *this;
  }
  LegacyBidirectionalIterator operator++(int) {
    LegacyBidirectionalIterator r(*this);
    ++i;
    return r;
  }
  LegacyBidirectionalIterator operator--(int) {
    LegacyBidirectionalIterator r(*this);
    --i;
    return r;
  }

  size_t size() { return v.size(); }

  bool operator!=(const LegacyBidirectionalIterator& r) const {
    return i != r.i;
  }
  bool operator==(const LegacyBidirectionalIterator& r) const {
    return i == r.i;
  }

 private:
  std::vector<int> v{};
  int i = 0;
};

class LegacyRandomAccessIterator {
 public:
  using T = int;

  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  LegacyRandomAccessIterator() : i(0), v() {}
  LegacyRandomAccessIterator(std::initializer_list<int> l) : v(l){};

  reference operator*() { return v[i]; }
  pointer operator->() { return &(v[i]); }
  reference operator[](int m) { return v[i + m]; }

  LegacyRandomAccessIterator& operator++() {
    ++i;
    return *this;
  }
  LegacyRandomAccessIterator& operator--() {
    --i;
    return *this;
  }
  LegacyRandomAccessIterator operator++(int) {
    ++i;
    return *this;
  }
  LegacyRandomAccessIterator& operator--(int) {
    --i;
    return *this;
  }

  LegacyRandomAccessIterator& operator+=(difference_type n) {
    i += n;
    return *this;
  }
  LegacyRandomAccessIterator& operator-=(difference_type n) {
    i -= n;
    return *this;
  }

  LegacyRandomAccessIterator operator+(difference_type n) const {
    LegacyRandomAccessIterator r(*this);
    return r += n;
  }
  LegacyRandomAccessIterator operator-(difference_type n) const {
    LegacyRandomAccessIterator r(*this);
    return r -= n;
  }

  size_t size() { return v.size(); }

  bool operator<(LegacyRandomAccessIterator const& r) const { return i < r.i; }
  bool operator<=(LegacyRandomAccessIterator const& r) const {
    return i <= r.i;
  }
  bool operator>(LegacyRandomAccessIterator const& r) const { return i > r.i; }
  bool operator>=(LegacyRandomAccessIterator const& r) const {
    return i >= r.i;
  }
  bool operator!=(const LegacyRandomAccessIterator& r) const {
    return i != r.i;
  }
  bool operator==(const LegacyRandomAccessIterator& r) const {
    return i == r.i;
  }

  int i = 0;

 private:
  std::vector<int> v{};
};

template <>
struct std::iterator_traits<LegacyIterator> {
  using value_type = int;
  using difference_type = int;
  using pointer = int*;
  using reference = int&;
};
template <>
struct std::iterator_traits<LegacyOutputIterator> {
  using value_type = int;
  using difference_type = int;
  using pointer = int*;
  using reference = int&;
};
template <>
struct std::iterator_traits<LegacyInputIterator> {
  using value_type = int;
  using difference_type = int;
  using pointer = int*;
  using reference = int&;
};
template <>
struct std::iterator_traits<LegacyBidirectionalIterator> {
  using value_type = int;
  using difference_type = int;
  using pointer = int*;
  using reference = int&;
};
template <>
struct std::iterator_traits<LegacyRandomAccessIterator> {
  using value_type = int;
  using difference_type = int;
  using pointer = int*;
  using reference = int&;
};

using random_diff_t = typename std::iterator_traits<LegacyRandomAccessIterator>::difference_type;
LegacyRandomAccessIterator operator+(random_diff_t n,
                                     LegacyRandomAccessIterator iterator) {
  LegacyRandomAccessIterator temp = iterator;
  return iterator += n;
}
LegacyRandomAccessIterator operator-(random_diff_t n,
                                     LegacyRandomAccessIterator iterator) {
  LegacyRandomAccessIterator temp = iterator;
  return iterator -= n;
}
random_diff_t operator-(LegacyRandomAccessIterator a,
                        LegacyRandomAccessIterator b) {
  return a.i - b.i;
}
