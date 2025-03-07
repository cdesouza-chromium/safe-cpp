// Copyright 2024 Sean Baxter
// Copyright 2024 Christian Mazakas
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#feature on safety

#include <std2/iterator.h>
#include <std2/__slice/slice.h>

#include <cstddef>

namespace std2
{

template<class T>
class slice_iterator/(a)
{
  T* unsafe p_;
  T* end_;
  T^/a __phantom_data;

public:
  slice_iterator([T; dyn]^/a s) noexcept safe
    : p_((*s)~as_pointer), unsafe end_((*s)~as_pointer + (*s)~length)
  {
  }

  optional<T^/a> next(self^) noexcept safe {
    if (self->p_ == self->end_) { return .none; }
    return .some(^*self->p_++);
  }
};

template<class T>
impl slice_iterator<T>: iterator
{
  using item_type = T^;

  optional<item_type> next(self^) safe override {
    return self.next();
  }
};

template<class T>
impl slice_iterator<T>: make_iter {
  using iter_type = slice_iterator<T>;
  using iter_mut_type = slice_iterator<T>;
  using into_iter_type = slice_iterator<T>;

  iter_type      iter(const self^) safe override { return *self; }
  iter_mut_type  iter(self^) safe override { return *self; }
  into_iter_type iter(self) safe override { return self; }
};

} // namespace std2
