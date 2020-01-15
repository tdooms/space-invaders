//============================================================================
// @name        : cooldown.h
// @author      : Thomas Dooms
// @date        : 12/4/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "stopwatch.h"
#include <iostream>

namespace util {
// a very useful class that uses the stopwatch to simulate a cooldown
struct Cooldown {
public:
  void start(std::chrono::milliseconds duration) {
    started = true;
    dur = duration;
    begin = Stopwatch::get().time();
  }

  void start() {
    started = true;
    begin = Stopwatch::get().time();
  }

  bool done() const {
    if (not started) {
      started = false;
      return true;
    } else {
      const auto diff = Stopwatch::get().time() - begin;
      return diff > dur;
    }
  }

  std::chrono::milliseconds msRemaining() const {
    if (done())
      return std::chrono::milliseconds(0);

    const auto remaining = std::chrono::system_clock::now() - begin;
    return std::chrono::duration_cast<std::chrono::milliseconds>(remaining);
  }

  std::chrono::milliseconds currentDuration() const {
    if (not started)
      return std::chrono::milliseconds(0);
    else
      return dur;
  }

private:
  std::chrono::system_clock::time_point begin;
  std::chrono::milliseconds dur;
  mutable bool started = false;
};
} // namespace util