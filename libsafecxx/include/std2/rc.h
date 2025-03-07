// Copyright 2024 Sean Baxter
// Copyright 2024 Christian Mazakas
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#feature on safety

#include <std2/utility.h>

namespace std2
{

template<class T+>
class [[unsafe::send(false)]] rc
{
  struct rc_inner;

  rc_inner* unsafe p_;

  struct rc_inner
  {
    manually_drop<T> data_;
    std::size_t strong_;
    std::size_t weak_;

    explicit
    rc_inner(T data) noexcept safe
      : data_(rel data)
      , strong_(1)
      , weak_(1)
    {
    }
  };


  public:

  explicit
  rc(T t) safe
  {
    unsafe { p_ = static_cast<rc_inner*>(::operator new(sizeof(rc_inner))); }
    new(p_) rc_inner(rel t);
  }

  rc(rc const^ rhs) safe
    : p_(rhs->p_)
  {
    ++p_->strong_;
  }

  [[unsafe::drop_only(T)]]
  ~rc() safe
  {
    std::size_t s = --p_->strong_;
    if (s == 0) {
      unsafe { mut p_->data_.destroy(); }

      std::size_t w = --p_->weak_;
      if (w == 0) {
        unsafe { ::operator delete(p_); }
      }
    }
  }

  T const^ operator->(self const^) noexcept safe {
    return *self->p_->data_.get();
  }

  T const^ operator*(self const^) noexcept safe {
    return *self->p_->data_.get();
  }
};

} // namespace std2
