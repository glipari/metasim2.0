#include <randomvar.hpp>
#include <vector>

#include <iostream>

#include "catch.hpp"

using namespace MetaSim;

TEST_CASE("TestRandomVar - mean", "[random, mean]")
{
  const unsigned int testSamples = 1e6;
  for (double lambda = 1; lambda < 10; lambda += 0.3) {
    long double mean = 0;
    long double theoreticalMean = 1.0 / lambda;

    ExponentialVar ev(lambda);

    for (unsigned int i=0; i<testSamples; ++i)
      mean += ev.get();

    mean /= testSamples;

    REQUIRE (mean / theoreticalMean > 0.99);
    REQUIRE (mean / theoreticalMean < 1.01);
  }
}

TEST_CASE("TestRandomVar - PDF", "[random, PDF]")
{
  const unsigned int testSamples = 1e6;
  const unsigned int histogramDefinition = 10;

  for (double lambda = 1; lambda < 10; lambda += 0.3) {
    std::vector<unsigned int> v(histogramDefinition, 0);

    ExponentialVar ev(lambda);

    for (unsigned int i=0; i<testSamples; ++i) {
      for (unsigned int j=0; j<histogramDefinition; ++j) {
        if (ev.get() < j+1) {
          v[j]++;
          break;
        }
      }
    }

    for (unsigned int i=1; i<histogramDefinition; ++i) {
      REQUIRE (v[i-1] >= v[i]);
    }
  }
}
