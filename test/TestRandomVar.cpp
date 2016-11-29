#include <randomvar.hpp>
#include <vector>

#include "catch.hpp"

using namespace MetaSim;

TEST_CASE("ExponentialVar - mean", "[exponential, mean]")
{
  const unsigned int testSamples = 1e6;
  for (double lambda = 0.1; lambda < 4; lambda += 0.3) {
    long double mean = 0;
    long double theoreticalMean = 1.0 / lambda;

    ExponentialVar ev(lambda);

    for (unsigned int i=0; i<testSamples; ++i)
      mean += ev.get();

    mean /= testSamples;

    REQUIRE (mean / theoreticalMean > 0.95);
    REQUIRE (mean / theoreticalMean < 1.05);
  }
}

TEST_CASE("ExponentialVar - PDF", "[exponential, PDF]")
{
  const unsigned int testSamples = 1e6;
  const unsigned int histogramDefinition = 10;

  for (double lambda = 0.1; lambda < 4; lambda += 0.3) {
    std::vector<unsigned int> v(histogramDefinition, 0);

    ExponentialVar ev(lambda);

    for (unsigned int i=0; i<testSamples; ++i) {
      double value = ev.get();
      if (value < histogramDefinition) {
        v[static_cast<unsigned int>(value)]++;
      }
    }

    for (unsigned int i=1; i<histogramDefinition; ++i) {
      REQUIRE (v[i-1] >= v[i]);
    }
  }
}
