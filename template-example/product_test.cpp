///////////////////////////////////////////////////////////////////////////////
// product_test.cpp
//
// Unit tests for code declared in product.hpp.
//
///////////////////////////////////////////////////////////////////////////////

#include "gtest/gtest.h"

#include "product.hpp"

TEST(ProductPositive, ProductPositive) {

  EXPECT_EQ(12, product(3, 4));
  EXPECT_EQ(25, product(5, 5));
}

TEST(ProductZero, ProductZero) {

  EXPECT_EQ(0, product(5, 0));
  EXPECT_EQ(0, product(-5, 0));
  EXPECT_EQ(0, product(0, 0));
}

TEST(ProductNegative, ProductNegative) {

  EXPECT_EQ(-12, product(-3, 4));
  EXPECT_EQ(-25, product(5, -5));
}
