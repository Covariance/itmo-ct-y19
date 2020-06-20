//
// Created by covariance on 16.05.2020.
//
#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include <cstddef>
#include <cstring>
#include <utility>

template<typename T>
class vector {
private:
  size_t size_;
  size_t capacity_;
  T* data_;

  static T* _safe_copy(const T* data, size_t copy_till, size_t initial_size) {
    size_t i;
    T* new_data = static_cast<T*>(operator new(initial_size * sizeof(T)));

    try {
      for (i = 0; i < copy_till; ++i) new(new_data + i) T(data[i]);
    } catch (...) {
      while (i--) new_data[i].~T();
      operator delete(new_data);
      throw;
    }

    return new_data;
  }

  void _update_size(size_t n) {
    size_t copy_till = (n > size_) ? size_ : n;
    T* new_data = _safe_copy(this->data_, copy_till, n);

    while (!empty()) pop_back();
    std::swap(data_, new_data);

    operator delete(new_data);

    size_ = copy_till;
    capacity_ = n;
  }

public:
  using iterator = T*;
  using const_iterator = T const*;

  // O(1) nothrow
  vector()
    : size_(0),
      capacity_(0),
      data_(nullptr) {}

  // O(N) strong
  vector(vector<T> const& rhs)
    : size_(rhs.size_),
      capacity_(rhs.size_),
      data_(nullptr) {
    if (size_ != 0) {
      T* new_data = _safe_copy(rhs.data_, rhs.size_, rhs.size_);
      data_ = new_data;
    }
  }

  // O(N) strong
  vector<T>& operator=(vector<T> const& other) {
    vector<T> temp(other);
    swap(temp);
    return *this;
  }

  // O(N) nothrow
  ~vector() {
    clear();
    operator delete(data_);
  }

  // O(1) nothrow
  T& operator[](size_t i) {
#ifdef _GLIBCXX_DEBUG
    assert(i < size_);
#endif
    return data_[i];
  }

  // O(1) nothrow
  T const& operator[](size_t i) const {
#ifdef _GLIBCXX_DEBUG
    assert(i < size_);
#endif
    return data_[i];
  }

  // O(1) nothrow
  T* data() {
    return data_;
  }

  // O(1) nothrow
  T const* data() const {
    return data_;
  }

  // O(1) nothrow
  size_t size() const {
    return size_;
  }

  // O(1) nothrow
  T& front() {
#ifdef _GLIBCXX_DEBUG
    assert(size_ > 0);
#endif
    return *data_;
  }

  // O(1) nothrow
  T const& front() const {
#ifdef _GLIBCXX_DEBUG
    assert(size_ > 0);
#endif
    return *data_;
  }

  // O(1) nothrow
  T& back() {
#ifdef _GLIBCXX_DEBUG
    assert(size_ > 0);
#endif
    return data_[size_ - 1];
  }

  // O(1) nothrow
  T const& back() const {
#ifdef _GLIBCXX_DEBUG
    assert(size_ > 0);
#endif
    return data_[size_ - 1];
  }

  // O(1)* strong
  void push_back(T const& value) {
    if (capacity_ == 0) {
      capacity_ = 1;
      data_ = static_cast<T*>(operator new(capacity_ * sizeof(T)));
    }

    if (size_ == capacity_) {
      T written = T(value);
      _update_size(2 * capacity_);
      new(data_ + size_) T(written);
    } else {
      new(data_ + size_) T(value);
    }
    size_++;
  };

  // O(1) nothrow
  inline void pop_back() {
#ifdef _GLIBCXX_DEBUG
    assert(size_ > 0);
#endif
    data_[--size_].~T();
  }

  // O(1) nothrow
  inline bool empty() const {
    return size_ == 0;
  }

  // O(1) nothrow
  size_t capacity() const {
    return capacity_;
  }

  // O(N) strong
  void reserve(size_t n) {
    if (n > capacity_) {
      _update_size(n);
    }
  }

  // O(N) strong
  void shrink_to_fit() {
    if (size_ == 0 && data_ != nullptr) {
      operator delete(data_);
      data_ = nullptr;
      capacity_ = 0;
    }
    if (capacity_ != size_) {
      _update_size(size_);
    }
  }


  // O(N) nothrow
  void clear() {
    while (!empty()) pop_back();
  }

  // O(1) nothrow
  void swap(vector<T>& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  // O(1) nothrow
  iterator begin() {
    return data_;
  }

  // O(1) nothrow
  iterator end() {
    return data_ + size_;
  }

  // O(1) nothrow
  const_iterator begin() const {
    return data_;
  }

  // O(1) nothrow
  const_iterator end() const {
    return data_ + size_;
  }

  // O(N) weak
  iterator insert(iterator pos, T const& value) {
    return insert(static_cast<vector<T>::const_iterator>(pos), value);
  }

  // O(N) weak
  iterator insert(const_iterator pos, T const& value) {
#ifdef _GLIBCXX_DEBUG
    assert(begin() <= pos);
    assert(pos <= end());
#endif
    size_t pos_ = pos - begin();
    push_back(value);

    for (size_t i = size_ - 1; i != pos_; --i) {
      std::swap(data_[i], data_[i - 1]);
    }

    return begin() + pos_;
  }

  // O(N) weak
  iterator erase(iterator pos) {
    return erase(static_cast<vector<T>::const_iterator>(pos));
  }

  // O(N) weak
  iterator erase(const_iterator pos) {
    return erase(pos, pos + 1);
  }

  // O(N) weak
  iterator erase(iterator first, iterator last) {
    return erase(static_cast<vector<T>::const_iterator>(first),
                 static_cast<vector<T>::const_iterator>(last));
  }

  // O(N) weak
  iterator erase(const_iterator first, const_iterator last) {
#ifdef _GLIBCXX_DEBUG
    assert(begin() <= first);
    assert(first < last);
    assert(last <= end());
#endif

    size_t delta = last - first;
    size_t end = last - begin();
    while (end != size_) {
      std::swap(data_[end - delta], data_[end]);
      end++;
    }
    while (delta--) pop_back();

    return begin() + (first - begin());
  }
};

#endif // VECTOR_H
