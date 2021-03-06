#include <stan/math/prim/scal.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <string>

using stan::math::check_not_nan;

TEST(ErrorHandlingScalar, CheckNotNan) {
  const std::string function = "check_not_nan";
  double x = 0;

  EXPECT_NO_THROW(check_not_nan(function, "x", x))
    << "check_not_nan should be true with finite x: " << x;

  x = std::numeric_limits<double>::infinity();
  EXPECT_NO_THROW(check_not_nan(function, "x", x))
    << "check_not_nan should be true with x = Inf: " << x;

  x = -std::numeric_limits<double>::infinity();
  EXPECT_NO_THROW(check_not_nan(function, "x", x))
    << "check_not_nan should be true with x = -Inf: " << x;

  x = std::numeric_limits<double>::quiet_NaN();
  EXPECT_THROW(check_not_nan(function, "x", x), std::domain_error)
    << "check_not_nan should throw exception on NaN: " << x;
}
