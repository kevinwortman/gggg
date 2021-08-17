///////////////////////////////////////////////////////////////////////////////
// product_timing.cpp
//
// Example code showing how to precisely measure the runtime of code.
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>

#include "product.hpp"
#include "timer.hpp"

void print_bar() {
  std::cout << std::string(79, '-') << std::endl;
}

int main() {

  // Feel free to change these constants to suit your needs.
  const size_t ITERATIONS = 10 * 1000*1000; // 10 million
  assert(ITERATIONS > 0);

  Timer timer;
  // start of timing critical section

  for (size_t i = 0; i < ITERATIONS; ++i) {
    product(10, 20);
  }

  // end of timing critical section
  double elapsed = timer.elapsed();

  print_bar();
  std::cout << "elapsed time for " << ITERATIONS << " iterations = "
	    << elapsed << " sec " << std::endl
            << "average for one iteration = "
	    << elapsed / ITERATIONS
	    << " sec" << std::endl;
  print_bar();

  return 0;
}
