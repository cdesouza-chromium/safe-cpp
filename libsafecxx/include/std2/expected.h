// Copyright 2024 Sean Baxter
// Copyright 2024 Christian Mazakas
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#feature on safety

#include <std2/panic.h>

namespace std2
{

template<class T+, class E+>
choice expected {
  [[safety::unwrap]] ok(T),
  err(E);

  T unwrap(self) noexcept safe {
    return match(self) -> T {
      .ok(t)  => rel t;
      .err(e) => panic("{} is err".format(expected~string));
    };
  }
};

} // namespace std2
