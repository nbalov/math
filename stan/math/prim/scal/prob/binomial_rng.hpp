#ifndef STAN_MATH_PRIM_SCAL_PROB_BINOMIAL_RNG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_BINOMIAL_RNG_HPP

#include <boost/random/binomial_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <stan/math/prim/scal/err/check_consistent_sizes.hpp>
#include <stan/math/prim/scal/err/check_bounded.hpp>
#include <stan/math/prim/scal/err/check_finite.hpp>
#include <stan/math/prim/scal/err/check_greater_or_equal.hpp>
#include <stan/math/prim/scal/err/check_less_or_equal.hpp>
#include <stan/math/prim/scal/err/check_nonnegative.hpp>
#include <stan/math/prim/scal/fun/constants.hpp>
#include <stan/math/prim/scal/fun/inv_logit.hpp>
#include <stan/math/prim/scal/fun/log1m.hpp>
#include <stan/math/prim/scal/fun/log_inv_logit.hpp>
#include <stan/math/prim/scal/fun/multiply_log.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <stan/math/prim/scal/fun/binomial_coefficient_log.hpp>
#include <stan/math/prim/scal/fun/lbeta.hpp>
#include <stan/math/prim/scal/meta/include_summand.hpp>
#include <stan/math/prim/scal/fun/inc_beta.hpp>
#include <string>

namespace stan {
  namespace math {

    /**
     * Return a pseudorandom Binomial random variable for the given population
     * size and chance of success parameters using the specified random number
     * generator.
     *
     * @tparam RNG class of rng
     * @param N population size parameter
     * @param theta chance of success parameter
     * @param rng random number generator
     * @return Binomial random variate
     * @throw std::domain_error if N is negative
     * @throw std::domain_error if theta is not a valid probability
     */
    template <class RNG>
    inline int
    binomial_rng(int N,
                 double theta,
                 RNG& rng) {
      using boost::variate_generator;
      using boost::binomial_distribution;

      static const std::string function = "binomial_rng";

      check_nonnegative(function, "Population size parameter", N);
      check_finite(function, "Probability parameter", theta);
      check_less_or_equal(function, "Probability parameter", theta, 1.0);
      check_greater_or_equal(function, "Probability parameter", theta, 0.0);

      variate_generator<RNG&, binomial_distribution<> >
        binomial_rng(rng, binomial_distribution<>(N, theta));
      return binomial_rng();
    }

  }
}
#endif
