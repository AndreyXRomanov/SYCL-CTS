#pragma once

struct LegacyIterator {
  std::vector<int> v;
  size_t index = 0;
  LegacyIterator(std::initializer_list<int> l) : v(l){};
  LegacyIterator& operator++() {
    index++;
    return *this;
  };
  LegacyIterator& operator++(int) {
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

  friend bool operator!=(LegacyOutputIterator a, LegacyOutputIterator b) {
    return a.index != b.index;
  }
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
  // Default Copy/Move Are Fine.
  // Default Destructor fine.

  reference operator*() { return v[i]; }
  pointer operator->() { return &(v[i]); }
  reference operator[](int m) { return v[i + m]; }

  LegacyForwardIterator& operator++() {
    ++i;
    return *this;
  }
  LegacyForwardIterator& operator--() {
    --i;
    return *this;
  }
  LegacyForwardIterator operator++(int) {
    LegacyForwardIterator r(*this);
    ++i;
    return r;
  }
  LegacyForwardIterator operator--(int) {
    LegacyForwardIterator r(*this);
    --i;
    return r;
  }

  LegacyForwardIterator& operator+=(int n) {
    i += n;
    return *this;
  }
  LegacyForwardIterator& operator-=(int n) {
    i -= n;
    return *this;
  }

  LegacyForwardIterator operator+(int n) const {
    LegacyForwardIterator r(*this);
    return r += n;
  }
  LegacyForwardIterator operator-(int n) const {
    LegacyForwardIterator r(*this);
    return r -= n;
  }

  difference_type operator-(LegacyForwardIterator const& r) const {
    return i - r.i;
  }
  size_t size() { return 5; }

  bool operator<(LegacyForwardIterator const& r) const { return i < r.i; }
  bool operator<=(LegacyForwardIterator const& r) const { return i <= r.i; }
  bool operator>(LegacyForwardIterator const& r) const { return i > r.i; }
  bool operator>=(LegacyForwardIterator const& r) const { return i >= r.i; }
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

  LegacyBidirectionalIterator& operator+=(int n) {
    i += n;
    return *this;
  }
  LegacyBidirectionalIterator& operator-=(int n) {
    i -= n;
    return *this;
  }

  LegacyBidirectionalIterator operator+(int n) const {
    LegacyBidirectionalIterator r(*this);
    return r += n;
  }
  LegacyBidirectionalIterator operator-(int n) const {
    LegacyBidirectionalIterator r(*this);
    return r -= n;
  }

  difference_type operator-(LegacyBidirectionalIterator const& r) const {
    return i - r.i;
  }

  size_t size() { return v.size(); }

  // Note: comparing iterator from different containers
  //       is undefined behavior so we don't need to check
  //       if they are the same container.
  bool operator<(LegacyBidirectionalIterator const& r) const { return i < r.i; }
  bool operator<=(LegacyBidirectionalIterator const& r) const {
    return i <= r.i;
  }
  bool operator>(LegacyBidirectionalIterator const& r) const { return i > r.i; }
  bool operator>=(LegacyBidirectionalIterator const& r) const {
    return i >= r.i;
  }
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

template <>
struct std::iterator_traits<LegacyBidirectionalIterator> {
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
struct std::iterator_traits<LegacyIterator> {
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

class LegacyRandomAccessIterator;

template <>
struct std::iterator_traits<LegacyRandomAccessIterator> {
  using value_type = int;
  using difference_type = int;
  using pointer = int*;
  using reference = int&;
};

using diff_t =
    typename std::iterator_traits<LegacyRandomAccessIterator>::difference_type;

class LegacyRandomAccessIterator {
 public:
  using T = int;

  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  LegacyRandomAccessIterator() : v(), i(0) {}
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
    LegacyRandomAccessIterator r(*this);
    ++i;
    return r;
  }
  LegacyRandomAccessIterator operator--(int) {
    LegacyRandomAccessIterator r(*this);
    --i;
    return r;
  }

  LegacyRandomAccessIterator& operator+=(
      typename std::iterator_traits<LegacyRandomAccessIterator>::difference_type
          n) {
    i += n;
    return *this;
  }
  LegacyRandomAccessIterator& operator-=(
      typename std::iterator_traits<LegacyRandomAccessIterator>::difference_type
          n) {
    i -= n;
    return *this;
  }

  LegacyRandomAccessIterator operator+(diff_t n) const {
    LegacyRandomAccessIterator r(*this);
    return r += n;
  }
  LegacyRandomAccessIterator operator-(diff_t n) const {
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

LegacyRandomAccessIterator operator+(diff_t n,
                                     LegacyRandomAccessIterator iterator) {
  LegacyRandomAccessIterator temp = iterator;
  return iterator += n;
}
LegacyRandomAccessIterator operator-(diff_t n,
                                     LegacyRandomAccessIterator iterator) {
  LegacyRandomAccessIterator temp = iterator;
  return iterator -= n;
}
diff_t operator-(LegacyRandomAccessIterator a, LegacyRandomAccessIterator b) {
  return a.i - b.i;
}
