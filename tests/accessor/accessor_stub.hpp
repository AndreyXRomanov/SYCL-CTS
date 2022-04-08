/*******************************************************************************
//
//  Stub for verifying that there are no syntax mistakes in test.
//  Can be ignored during review process.
//
*******************************************************************************/
#ifndef SYCL_CTS_ACCESSOR_STUB
#define SYCL_CTS_ACCESSOR_STUB

#include <iterator>
#include <sycl.hpp>
#include <type_traits>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"

namespace sycl_stub {

struct read_type {};
struct write_type {};
struct readwrite_type {};
struct read_host_task_type {};
struct write_host_task_type {};
struct readwrite_host_task_type {};

inline constexpr read_type read_only;
inline constexpr write_type write_only;
inline constexpr readwrite_type read_write;
inline constexpr read_host_task_type read_only_host_task;
inline constexpr write_host_task_type write_only_host_task;
inline constexpr readwrite_host_task_type read_write_host_task;

enum class target {
  device,
  host_task,
  global_buffer = device,  // Deprecated
  constant_buffer,         // Deprecated
  local,                   // Deprecated
  host_buffer              // Deprecated
};

namespace access {
// The legacy type "access::target" is deprecated.
using sycl::target;

enum class placeholder {  // Deprecated
  false_t,
  true_t
};

}  // namespace access

template <typename DataT, int Dimensions = 1,
          sycl::access_mode AccessMode =
              (std::is_const_v<DataT> ? sycl::access_mode::read
                                      : sycl::access_mode::read_write),
          target AccessTarget = target::device,
          access::placeholder isPlaceholder = access::placeholder::false_t>
class accessor;

template <typename DataT, int Dimensions, sycl::access_mode AccessMode,
          target AccessTarget, access::placeholder isPlaceholder>
class accessor {
 public:
  using value_type = DataT;
  using reference = value_type &;
  using const_reference = DataT &;

  template <sycl::access::decorated IsDecorated>
  using accessor_ptr = std::shared_ptr<DataT>;
  using iterator = typename std::array<DataT, 1>::const_iterator;
  using const_iterator = typename std::array<DataT, 1>::const_iterator;
  using reverse_iterator =
      typename std::array<DataT, 1>::const_reverse_iterator;
  using const_reverse_iterator =
      typename std::array<DataT, 1>::const_reverse_iterator;

  accessor() {}

  /* Available only when: (Dimensions > 0) */
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef) {}

  /* Available only when: (Dimensions > 0) */
  template <typename TagT>
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef, TagT tag) {}

  /* Available only when: (Dimensions > 0) */
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef,
           sycl::handler &commandGroupHandlerRef) {}

  /* Available only when: (Dimensions > 0) */
  template <typename TagT>
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef,
           sycl::handler &commandGroupHandlerRef, TagT tag) {}

  /* Available only when: (Dimensions > 0) */
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef,
           sycl::range<Dimensions> accessRange) {}

  /* Available only when: (Dimensions > 0) */
  template <typename TagT>
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef,
           sycl::range<Dimensions> accessRange, TagT tag) {}

  /* Available only when: (Dimensions > 0) */
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef,
           sycl::range<Dimensions> accessRange,
           sycl::id<Dimensions> accessOffset) {}

  /* Available only when: (Dimensions > 0) */
  template <typename TagT>
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef,
           sycl::range<Dimensions> accessRange,
           sycl::id<Dimensions> accessOffset, TagT tag) {}

  /* Available only when: (Dimensions > 0) */
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef,
           sycl::handler &commandGroupHandlerRef,
           sycl::range<Dimensions> accessRange) {}

  /* Available only when: (Dimensions > 0) */
  template <typename TagT>
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef,
           sycl::handler &commandGroupHandlerRef,
           sycl::range<Dimensions> accessRange, TagT tag) {}

  /* Available only when: (Dimensions > 0) */
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef,
           sycl::handler &commandGroupHandlerRef,
           sycl::range<Dimensions> accessRange,
           sycl::id<Dimensions> accessOffset) {}

  /* Available only when: (Dimensions > 0) */
  template <typename TagT>
  accessor(sycl::buffer<DataT, Dimensions> &bufferRef,
           sycl::handler &commandGroupHandlerRef,
           sycl::range<Dimensions> accessRange,
           sycl::id<Dimensions> accessOffset, TagT tag) {}

  /* -- common interface members -- */

  void swap(accessor &other) {}

  bool is_placeholder() const { return 0; }

  size_t byte_size() const noexcept { return 0; }

  size_t size() const noexcept { return 0; }

  size_t max_size() const noexcept { return 0; }

  // Deprecated
  size_t get_size() const { return 0; }

  // Deprecated
  size_t get_count() const { return 0; }

  bool empty() const noexcept { return 0; }

  /* Available only when: (Dimensions > 0) */
  sycl::range<Dimensions> get_range() const {}

  /* Available only when: (Dimensions > 0) */
  sycl::id<Dimensions> get_offset() const {}

  DataT &operator[](sycl::id<Dimensions> index) {
    DataT ret_val;
    return ret_val;
  }

  /* Available only when: (Dimensions > 0) */
  DataT &operator[](sycl::id<Dimensions> index) const {
    DataT ret_val;
    return ret_val;
  }

  /* Available only when: (Dimensions > 1) */
  DataT &operator[](size_t index) {
    DataT ret_val;
    return ret_val;
  }

  const DataT &operator[](size_t index) const {
    DataT ret_val;
    return ret_val;
  }

  //   add_pointer_t<value_type> get_pointer() const noexcept
  //   {}

  //   template <access::decorated IsDecorated>
  //   accessor_ptr<IsDecorated> get_multi_ptr() const noexcept {}

  iterator begin() const noexcept { return arr.cbegin(); }

  iterator end() const noexcept { return arr.cend(); }

  const_iterator cbegin() const noexcept { return arr.cbegin(); }

  const_iterator cend() const noexcept { return arr.cend(); }

  reverse_iterator rbegin() const noexcept { return arr.crbegin(); }

  reverse_iterator rend() const noexcept { return arr.crend(); }

  const_reverse_iterator crbegin() const noexcept { return arr.crbegin(); }

  const_reverse_iterator crend() const noexcept { return arr.crend(); }

  DataT stub;
  std::array<DataT, 1> arr;
};

template <typename DataT, sycl::access_mode AccessMode, target AccessTarget,
          access::placeholder isPlaceholder>
class accessor<DataT, 0, AccessMode, AccessTarget, isPlaceholder> {
 public:
  using value_type = DataT;
  using reference = value_type &;
  using const_reference = DataT &;

  template <sycl::access::decorated IsDecorated>
  using accessor_ptr = std::shared_ptr<DataT>;

  using iterator = typename std::vector<DataT>::iterator;
  using const_iterator = typename std::vector<DataT>::const_iterator;
  using reverse_iterator = typename std::vector<DataT>::reverse_iterator;
  using const_reverse_iterator =
      typename std::vector<DataT>::const_reverse_iterator;

  accessor() {}

  /* Available only when: (Dimensions == 0) */
  accessor(sycl::buffer<DataT, 1> &bufferRef) {}

  /* Available only when: (Dimensions == 0) */
  accessor(sycl::buffer<DataT, 1> &bufferRef,
           sycl::handler &commandGroupHandlerRef) {}

  /* -- common interface members -- */

  void swap(accessor &other) {}

  bool is_placeholder() const { return 0; }

  size_t byte_size() const noexcept { return 0; }

  size_t size() const noexcept { return 0; }

  size_t max_size() const noexcept { return 0; }

  // Deprecated
  size_t get_size() const { return 0; }

  // Deprecated
  size_t get_count() const { return 0; }

  bool empty() const noexcept { return 0; }

  /* Available only when: (Dimensions == 0) */
  operator DataT &() const {
    DataT ret_val;
    return ret_val;
  }

  const DataT &operator[](size_t index) const {
    DataT ret_val;
    return ret_val;
  }

  //   add_pointer_t<value_type> get_pointer() const noexcept
  //   {}

  //   template <access::decorated IsDecorated>
  //   accessor_ptr<IsDecorated> get_multi_ptr() const noexcept {}

  iterator begin() const noexcept { return arr.cbegin(); }

  iterator end() const noexcept { return arr.cend(); }

  const_iterator cbegin() const noexcept { return arr.cbegin(); }

  const_iterator cend() const noexcept { return arr.cend(); }

  reverse_iterator rbegin() const noexcept { return arr.crbegin(); }

  reverse_iterator rend() const noexcept { return arr.crend(); }

  const_reverse_iterator crbegin() const noexcept { return arr.crbegin(); }

  const_reverse_iterator crend() const noexcept { return arr.crend(); }

  DataT stub;
  std::array<DataT, 1> arr;
};

template <typename DataT, int Dimensions = 1>
class local_accessor;

template <typename DataT, int Dimensions>
class local_accessor {
 public:
  using value_type = DataT;
  using reference = value_type &;
  using const_reference = DataT &;

  template <sycl::access::decorated IsDecorated>
  using accessor_ptr = std::shared_ptr<DataT>;
  using iterator = typename std::array<DataT, 1>::const_iterator;
  using const_iterator = typename std::array<DataT, 1>::const_iterator;
  using reverse_iterator =
      typename std::array<DataT, 1>::const_reverse_iterator;
  using const_reverse_iterator =
      typename std::array<DataT, 1>::const_reverse_iterator;

  local_accessor() {}

  /* Available only when: (Dimensions > 0) */
  local_accessor(sycl::range<Dimensions> allocationSize,
                 sycl::handler &commandGroupHandlerRef){}

  /* -- common interface members -- */

  void swap(local_accessor &other) {}

  size_t byte_size() const noexcept { return 0; }

  size_t size() const noexcept { return 0; }

  size_t max_size() const noexcept { return 0; }

  bool empty() const noexcept { return 0; }

  /* Available only when: (Dimensions > 0) */
  sycl::range<Dimensions> get_range() const {}

  DataT &operator[](sycl::id<Dimensions> index) {
    DataT ret_val;
    return ret_val;
  }

  /* Available only when: (Dimensions > 0) */
  DataT &operator[](sycl::id<Dimensions> index) const {
    DataT ret_val;
    return ret_val;
  }

  /* Available only when: (Dimensions > 1) */
  DataT &operator[](size_t index) {
    DataT ret_val;
    return ret_val;
  }

  const DataT &operator[](size_t index) const {
    DataT ret_val;
    return ret_val;
  }

  //   add_pointer_t<value_type> get_pointer() const noexcept
  //   {}

  //   template <access::decorated IsDecorated>
  //   accessor_ptr<IsDecorated> get_multi_ptr() const noexcept {}

  iterator begin() const noexcept { return arr.cbegin(); }

  iterator end() const noexcept { return arr.cend(); }

  const_iterator cbegin() const noexcept { return arr.cbegin(); }

  const_iterator cend() const noexcept { return arr.cend(); }

  reverse_iterator rbegin() const noexcept { return arr.crbegin(); }

  reverse_iterator rend() const noexcept { return arr.crend(); }

  const_reverse_iterator crbegin() const noexcept { return arr.crbegin(); }

  const_reverse_iterator crend() const noexcept { return arr.crend(); }

  DataT stub;
  std::array<DataT, 1> arr;
};

template <typename DataT>
class local_accessor<DataT, 0> {
 public:
  using value_type = DataT;
  using reference = value_type &;
  using const_reference = DataT &;

  template <sycl::access::decorated IsDecorated>
  using accessor_ptr = std::shared_ptr<DataT>;
  using iterator = typename std::array<DataT, 1>::const_iterator;
  using const_iterator = typename std::array<DataT, 1>::const_iterator;
  using reverse_iterator =
      typename std::array<DataT, 1>::const_reverse_iterator;
  using const_reverse_iterator =
      typename std::array<DataT, 1>::const_reverse_iterator;

  local_accessor() {}

  /* Available only when: (Dimensions == 0) */
  local_accessor(sycl::handler &commandGroupHandlerRef){}

  /* -- common interface members -- */

  void swap(local_accessor &other) {}

  size_t byte_size() const noexcept { return 0; }

  size_t size() const noexcept { return 0; }

  size_t max_size() const noexcept { return 0; }

  bool empty() const noexcept { return 0; }

  /* Available only when: (Dimensions == 0) */
  operator DataT &() const {
    DataT ret_val;
    return ret_val;
  }

  //   add_pointer_t<value_type> get_pointer() const noexcept
  //   {}

  //   template <access::decorated IsDecorated>
  //   accessor_ptr<IsDecorated> get_multi_ptr() const noexcept {}

  iterator begin() const noexcept { return arr.cbegin(); }

  iterator end() const noexcept { return arr.cend(); }

  const_iterator cbegin() const noexcept { return arr.cbegin(); }

  const_iterator cend() const noexcept { return arr.cend(); }

  reverse_iterator rbegin() const noexcept { return arr.crbegin(); }

  reverse_iterator rend() const noexcept { return arr.crend(); }

  const_reverse_iterator crbegin() const noexcept { return arr.crbegin(); }

  const_reverse_iterator crend() const noexcept { return arr.crend(); }

  DataT stub;
  std::array<DataT, 1> arr;
};

}  // namespace sycl_stub
#pragma clang diagnostic pop
#endif  // SYCL_CTS_ACCESSOR_STUB
