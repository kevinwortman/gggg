///////////////////////////////////////////////////////////////////////////////
// timer.hpp
//
// Timer class for code timing.
//
// This class depends only on the C++11 STL so it ought to be
// portable. It uses the std::clock() function which is precise to
// platform-dependent fractions of a second, as specified by
// CLOCKS_PER_SEC.
//
// How to use:
//
//    // do slow initialization before creating a Timer
//    Timer timer;
//    // timer is now running, immediately run the code you want timed
//    double elapsed = timer.elapsed();
//    cout << "Elapsed time in seconds: " << elapsed << endl;
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <chrono>

class Timer {
private:
  std::chrono::high_resolution_clock::time_point _start;

public:

  // Create a new Timer that is running as soon as it is created.
  Timer() {
    reset();
  }

  // Reset the timer.
  void reset() {
    _start = std::chrono::high_resolution_clock::now();
  }

  // Return the number of seconds since the timer was created, or the
  // last time it was reset.
  double elapsed() const {
    auto end = std::chrono::high_resolution_clock::now();
    assert(end >= _start);
    auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - _start);
    return time_span.count();
  }
};
