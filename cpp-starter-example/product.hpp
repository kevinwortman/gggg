///////////////////////////////////////////////////////////////////////////////
// product.hpp
//
// Example of starter code distributed to students and evaluated with gggg.
///////////////////////////////////////////////////////////////////////////////

#pragma once

// Return x1 times x2.
int product(int x1, int x2) {

  /* This commented-out section is what the body of this funciton would look
  like in the starter code given to students.

  // TODO: IMPLEMENT THIS FUNCTION SO THAT IT ACTUALLY WORKS, AND THEN DELETE
  // THIS COMMENT. YOU WILL PROBABLY NEED TO REWRITE THE RETURN STATEMENT BELOW.
  return 0;

  */

  // This is an implementation that has a deliberate bug (can't produce negative
  // outputs) to illustrate partial credit.
  int result = x1 * x2;
  if (result < 0) {
    result = -result;
  }
  return result;

}
