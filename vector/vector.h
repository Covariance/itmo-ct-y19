//
// Created by covariance on 16.05.2020.
//
#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <cstring>
#include <cassert>
#include <utility>

template<typename T>
struct vector {
  typedef T* iterator;
  typedef T const* const_iterator;

  vector();                               // O(1) nothrow
  vector(vector const&);                  // O(N) strong
  vector& operator=(vector const& other); // O(N) strong

  ~vector();                              // O(N) nothrow

  T& operator[](size_t i);                // O(1) nothrow
  T const& operator[](size_t i) const;    // O(1) nothrow

  T* data();                              // O(1) nothrow
  T const* data() const;                  // O(1) nothrow
  size_t size() const;                    // O(1) nothrow

  T& front();                             // O(1) nothrow
  T const& front() const;                 // O(1) nothrow

  T& back();                              // O(1) nothrow
  T const& back() const;                  // O(1) nothrow
  void push_back(T const&);               // O(1)* strong
  void pop_back();                        // O(1) nothrow

  bool empty() const;                     // O(1) nothrow

  size_t capacity() const;                // O(1) nothrow
  void resize(size_t);                    // O(n) strong
  void reserve(size_t);                   // O(N) strong
  void shrink_to_fit();                   // O(N) strong

  void clear();                           // O(N) nothrow

  void swap(vector&);                     // O(1) nothrow

  iterator begin();                       // O(1) nothrow
  iterator end();                         // O(1) nothrow

  const_iterator begin() const;           // O(1) nothrow
  const_iterator end() const;             // O(1) nothrow

  iterator insert(iterator pos, T const&); // O(N) weak
  iterator insert(const_iterator pos, T const&); // O(N) weak

  iterator erase(iterator pos);           // O(N) weak
  iterator erase(const_iterator pos);     // O(N) weak

  iterator erase(iterator first, iterator last); // O(N) weak
  iterator erase(const_iterator first, const_iterator last); // O(N) weak

private:
  size_t size_;
  size_t capacity_;
  T* data_;
};

template<typename T>
vector<T>::vector()
  : size_(0),
    capacity_(0),
    data_(nullptr) {}

template<typename T>
vector<T>::vector(vector<T> const& rhs)
  : size_(rhs.size_),
    capacity_(rhs.capacity_) {
  if (size_ != 0) {
    T* new_data = static_cast<T*>(operator new(rhs.capacity_ * sizeof(T)));
    for (size_t i = 0; i < rhs.size_; i++) {
      new(new_data + i) T(rhs.data_[i]);
    }
    data_ = new_data;
  } else {
    data_ = nullptr;
  }
}

template<typename T>
vector<T>& vector<T>::operator=(vector<T> const& other) {
  vector<T> temp(other);
  swap(temp);
  return *this;
}

template<typename T>
vector<T>::~vector() {
  clear();
  size_ = 0;
  capacity_ = 0;
  operator delete(data_);
}

template<typename T>
T& vector<T>::operator[](size_t i) {
  assert(i < size_);
  return data_[i];
}

template<typename T>
T const& vector<T>::operator[](size_t i) const {
  assert(i < size_);
  return data_[i];
}

template<typename T>
T* vector<T>::data() {
  return data_;
}

template<typename T>
T const* vector<T>::data() const {
  return data_;
}

template<typename T>
size_t vector<T>::size() const {
  return size_;
}

template<typename T>
T& vector<T>::front() {
  return *data_;
}

template<typename T>
T const& vector<T>::front() const {
  return *data_;
}

template<typename T>
T& vector<T>::back() {
  assert(size_ > 0);
  return data_[size_ - 1];
}

template<typename T>
T const& vector<T>::back() const {
  assert(size_ > 0);
  return data_[size_ - 1];
}

template<typename T>
void vector<T>::push_back(T const& value) {
  if (capacity_ == 0) {
    capacity_ = 2;
    data_ = static_cast<T*>(operator new(capacity_ * sizeof(T)));
  }
  T written = T(value);
  if (size_ == capacity_) {
    resize(2 * capacity_);
  }
  new(data_ + size_) T(written);
  size_++;
}

template<typename T>
void vector<T>::pop_back() {
  assert(size_ > 0);
  data_[--size_].~T();
}

template<typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template<typename T>
size_t vector<T>::capacity() const {
  return capacity_;
}

template<typename T>
void vector<T>::resize(size_t n) {
  T* new_data = static_cast<T*>(operator new(n * sizeof(T)));

  size_t copy_till = (n > size_) ? size_ : n;
  size_t i = 0;

  try {
    for (; i < copy_till; i++) {
      new(new_data + i) T(data_[i]);
    }
  } catch (...) {
    for (size_t j = 0; j < i; j++) {
      new_data[j].~T();
    }
    operator delete(new_data);
    throw;
  }

  for (size_t i = 0; i < size_; i++) {
    data_[i].~T();
  }
  std::swap(data_, new_data);
  operator delete(new_data);

  size_ = copy_till;
  capacity_ = n;
}

template<typename T>
void vector<T>::reserve(size_t n) {
  if (n > capacity_) {
    resize(n);
  }
}

template<typename T>
void vector<T>::shrink_to_fit() {
  if (size_ == 0 && data_ != nullptr) {
    operator delete(data_);
    data_ = nullptr;
    return;
  }
  if (capacity_ != size_) {
    resize(size_);
  }
}

template<typename T>
void vector<T>::clear() {
  for (size_t i = 0; i < size_; i++) {
    data_[i].~T();
  }
  size_ = 0;
}

template<typename T>
void vector<T>::swap(vector<T>& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template<typename T>
typename vector<T>::iterator vector<T>::begin() {
  return data_;
}

template<typename T>
typename vector<T>::iterator vector<T>::end() {
  return data_ + size_;
}

template<typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return data_;
}

template<typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return data_ + size_;
}

template<typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos, T const& value) {
  return insert(static_cast<vector<T>::const_iterator>(pos), value);
}

template<typename T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos, T const& value) {
  size_t pos_ = pos - begin();
  push_back(value);

  for (size_t i = size_ - 1; i != pos_; --i) {
    std::swap(data_[i], data_[i - 1]);
  }

  return begin() + pos_;
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(iterator pos) {
  return erase(static_cast<vector<T>::const_iterator>(pos));
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(const_iterator pos) {
  return erase(pos, pos + 1);
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(iterator first, iterator last) {
  return erase(static_cast<vector<T>::const_iterator>(first),
               static_cast<vector<T>::const_iterator>(last));
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(const_iterator first, const_iterator last) {
  assert(first < last);

  size_t delta = last - first;
  size_t end = last - begin();
  while (end != size_) {
    std::swap(data_[end - delta], data_[end]);
    end++;
  }
  while (delta--) {
    data_[--size_].~T();
  }

  return begin() + (first - begin());
}

#endif // VECTOR_H
