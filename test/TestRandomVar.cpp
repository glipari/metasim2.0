#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <randomvar.hpp>
#include <regvar.hpp>
#include "catch.hpp"

using namespace std;
using namespace MetaSim;

TEST_CASE("Test random vars", "[random, factory]")
{

    SECTION ("Testing delta") {
        unique_ptr<MetaSim::RandomVar> p = MetaSim::RandomVar::parsevar("delta(5)");
        
        REQUIRE(p->get() == 5);
        REQUIRE(p->getMaximum() == 5);
        REQUIRE(p->getMinimum() == 5);
    }
    SECTION ("Testing exp") {
        unique_ptr<MetaSim::RandomVar> q = MetaSim::RandomVar::parsevar("exponential(5)");

        double v = q->get();
        REQUIRE (v <= 59);
        REQUIRE (v >= 58);
        REQUIRE (q->getMinimum() == 0);
        REQUIRE_THROWS(q->getMaximum());
    }

    SECTION ("Testing a vector of random vars") {
        vector<unique_ptr<MetaSim::RandomVar> > v_obj;
        unique_ptr<MetaSim::RandomVar> p = MetaSim::RandomVar::parsevar("delta(2)");
        unique_ptr<MetaSim::RandomVar> q = MetaSim::RandomVar::parsevar("exp(5)");

        v_obj.push_back(std::move(p));
        v_obj.push_back(std::move(q));

        REQUIRE(v_obj[0]->get() == 2);
        REQUIRE_THROWS(v_obj[1]->getMaximum());
    }
    SECTION ("Testing a vector of random vars with shared_ptr<>") {
        vector<shared_ptr<MetaSim::RandomVar> > v_obj;
        unique_ptr<MetaSim::RandomVar> p = MetaSim::RandomVar::parsevar("delta(2)");
        unique_ptr<MetaSim::RandomVar> q = MetaSim::RandomVar::parsevar("exp(5)");

        v_obj.push_back(shared_ptr<MetaSim::RandomVar>(std::move(p)));
        v_obj.push_back(shared_ptr<MetaSim::RandomVar>(std::move(q)));

        vector<shared_ptr<MetaSim::RandomVar> > v2_obj(v_obj);
        REQUIRE(v2_obj[0]->get() == 2);
        REQUIRE_THROWS(v2_obj[1]->getMaximum());
    }
}

template<class T>
T expPDF(T lambda, T x)
{
  if (x >= 0)
    return lambda * exp(-lambda * x);
  return 0;
}

template<class T>
T weibullPDF(T lambda, T kappa, T x)
{
  if (x >= 0)
    return (kappa / lambda) * pow(x / lambda, kappa - 1.0) * exp( - pow(x / lambda, kappa));
  return 0;
}

TEST_CASE("TestRandomVar - mean", "[random, mean]")
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
  long double binSize = 0.2;
  long double startingValue = 0;
  long double finishingValue = 4;

  const unsigned int testSamples = 1e6;

  const unsigned int histogramDefinition = (finishingValue - startingValue) / binSize;

  for (long double lambda = 0.1; lambda < 3; lambda += 0.3) {
    std::vector<unsigned int> v(histogramDefinition, 0);

    ExponentialVar ev(lambda);

    for (unsigned int i=0; i<testSamples; ++i) {
      double value = ev.get();

      unsigned int counter = 0;
      for (double bin_floor = startingValue; bin_floor < finishingValue; bin_floor += binSize) {
        if (value >= bin_floor && value < bin_floor + binSize) {
          v[counter]++;
          break;
        }
        counter++;
      }
    }

    int counter = 0;
    for (auto vi : v) {
      long double vPDF = static_cast<double>(vi) / testSamples / binSize;
      long double ePDF = expPDF(lambda, binSize * counter + binSize / 2.0);

      if (vPDF < 0.01 || ePDF < 0.01)
        continue;

      REQUIRE (vPDF / ePDF < 1.1);
      REQUIRE (vPDF / ePDF > 0.9);
      counter++;
    }
  }
}

TEST_CASE("WeibullVar - mean", "[weibull, mean]")
{
  const unsigned int testSamples = 1e6;
  for (long double lambda = 0.5; lambda < 1.5; lambda += 0.3) {
    for (long double kappa = 0.5; kappa < 5; kappa += 0.3) {
      long double mean = 0;
      long double theoreticalMean = lambda * tgammal(1.0 + 1.0 / kappa);

      WeibullVar ev(lambda, kappa);

      for (unsigned int i=0; i<testSamples; ++i)
        mean += ev.get();

      mean /= testSamples;

      REQUIRE (mean / theoreticalMean > 0.95);
      REQUIRE (mean / theoreticalMean < 1.05);
    }
  }
}

TEST_CASE("WeibullVar - PDF", "[weibull, CDF]")
{
  long double binSize = 0.4;
  long double startingValue = 0;
  long double finishingValue = 3;

  const unsigned int testSamples = 1e6;

  const unsigned int histogramDefinition = (finishingValue - startingValue) / binSize;

  for (long double lambda = 0.5; lambda < 1.5; lambda += 0.3) {
    for (long double kappa = 0.5; kappa < 5; kappa += 0.3) {
      std::vector<unsigned int> v(histogramDefinition, 0);

      WeibullVar ev(lambda, kappa);

      for (unsigned int i=0; i<testSamples; ++i) {
        double value = ev.get();

        unsigned int counter = 0;
        for (double bin_floor = startingValue; bin_floor < finishingValue; bin_floor += binSize) {
          if (value >= bin_floor && value < bin_floor + binSize) {
            v[counter]++;
            break;
          }
          counter++;
        }
      }

      double vPDFSum = 0;
      for (auto vi : v) {
        vPDFSum += static_cast<double>(vi) / testSamples / binSize;
      }

      int counter = 0;
      for (auto vi : v) {
        long double vPDF = static_cast<double>(vi) / testSamples / binSize / vPDFSum;
        long double ePDF = weibullPDF(lambda, kappa, binSize * counter + binSize / 2.0);

        if (vPDF < 0.01 || ePDF < 0.01)
          continue;

        if (abs(vPDF - ePDF) > 1.5 && (vPDF / ePDF > 1.3 || vPDF / ePDF < 0.7)) {
          REQUIRE (false);
        }
        counter++;
      }
    }
  }
}
