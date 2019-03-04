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
        auto p = MetaSim::RandomVar::parsevar("delta(5)");
        
        REQUIRE(p->get() == 5);
        REQUIRE(p->getMaximum() == 5);
        REQUIRE(p->getMinimum() == 5);
    }
    SECTION ("Testing exp") {
        auto q = MetaSim::RandomVar::parsevar("exponential(5)");

        double v = q->get();
        REQUIRE (v <= 1e6);
        REQUIRE (v >= 0);
        REQUIRE (q->getMinimum() == 0);
        REQUIRE_THROWS(q->getMaximum());
    }

    SECTION ("Testing a vector of random vars") {
        vector<unique_ptr<MetaSim::RandomVar> > v_obj;
        auto p = MetaSim::RandomVar::parsevar("delta(2)");
        auto q = MetaSim::RandomVar::parsevar("exp(5)");

        v_obj.push_back(std::move(p));
        v_obj.push_back(std::move(q));

        REQUIRE(v_obj[0]->get() == 2);
        REQUIRE_THROWS(v_obj[1]->getMaximum());
    }
    SECTION ("Testing a vector of random vars with shared_ptr<>") {
        vector<shared_ptr<MetaSim::RandomVar> > v_obj;
        auto p = MetaSim::RandomVar::parsevar("delta(2)");
        auto q = MetaSim::RandomVar::parsevar("exp(5)");

        v_obj.push_back(shared_ptr<MetaSim::RandomVar>(std::move(p)));
        v_obj.push_back(shared_ptr<MetaSim::RandomVar>(std::move(q)));

        vector<shared_ptr<MetaSim::RandomVar> > v2_obj(v_obj);
        REQUIRE(v2_obj[0]->get() == 2);
        REQUIRE_THROWS(v2_obj[1]->getMaximum());
    }
}

class Histogram {
    double _bucketSize;
    double _startValue;
    double _endValue;
    unsigned int _samples;

    std::vector<unsigned int> _histogram;
    unsigned int _buckets;

public:
    Histogram(double bucketSize, double startValue, double endValue) :
        _bucketSize(bucketSize), _startValue(startValue), _endValue(endValue), _samples(0)
        {
            _buckets = static_cast<unsigned int>(ceil((_endValue - _startValue) / _bucketSize));
            _histogram.resize(_buckets);
            fill(_histogram.begin(), _histogram.end(), 0);
        }

    inline void add(double v)
        {
            if (v < _startValue || v > _endValue)
                return;

            unsigned int index = static_cast<unsigned int>(floor(v / _bucketSize));
            _histogram[index]++;
            _samples++;
        }

    long double sum() const
        {
            long double PDFSum = 0.0;

            for (auto v : _histogram)
                PDFSum += static_cast<long double>(v) / _samples / _bucketSize;

            return PDFSum;
        }

    inline const unsigned int &operator[](std::size_t idx) const { return _histogram[idx]; }
    inline unsigned int size() const { return _buckets; }
    inline unsigned int samples() const { return _samples; }
    inline long double pdf(unsigned int index) const { return static_cast<double>(_histogram[index]) / _samples / _bucketSize; }
};

template<class T>
inline T expPDF(T lambda, T x)
{
    if (x >= 0)
        return lambda * exp(-lambda * x);
    return 0;
}

template<class T>
inline T weibullPDF(T lambda, T kappa, T x)
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
    long double bucketSize = 0.2;
    long double startingValue = 0;
    long double finishingValue = 4;

    const unsigned int testSamples = 1e6;

    for (long double lambda = 0.1; lambda < 3; lambda += 0.3) {
        Histogram h(bucketSize, startingValue, finishingValue);
        ExponentialVar ev(lambda);

        for (unsigned int i=0; i<testSamples; ++i)
            h.add(ev.get());

        long double mse = 0;
        for (unsigned int i=0; i<h.size(); ++i) {
            long double vPDF = h.pdf(i);
            long double ePDF = expPDF(lambda, bucketSize * (i + 0.5));

            mse += (vPDF - ePDF) * (vPDF - ePDF);
        }
        mse /= h.size();

        REQUIRE(mse < 0.1);
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

TEST_CASE("WeibullVar - PDF", "[weibull, PDF]")
{
    long double bucketSize = 0.2;
    long double startingValue = 0;
    long double finishingValue = 3;

    const unsigned int testSamples = 1e6;

    for (long double lambda = 0.5; lambda < 1.5; lambda += 0.3) {
        for (long double kappa = 0.5; kappa < 5; kappa += 0.3) {
            Histogram h(bucketSize, startingValue, finishingValue);
            WeibullVar ev(lambda, kappa);

            for (unsigned int i=0; i<testSamples; ++i)
                h.add(ev.get());

            long double mse = 0;
            for (unsigned int i=0; i<h.size(); ++i) {
                long double vPDF = h.pdf(i);
                long double ePDF = weibullPDF(lambda, kappa, bucketSize * (i + 0.5));

                mse += (vPDF - ePDF) * (vPDF - ePDF);
            }
            mse /= h.size();

            REQUIRE(mse < 0.1);
        }
    }
}


TEST_CASE("RandomVar Cloning", "[RandomVar, Cloning]")
{
    auto v1 = RandomVar::parsevar("delta(3)");
    auto v2 = v1->clone();

    auto v3 = RandomVar::parsevar("unif(5,6)");
    auto v4 = v3->clone();
    
    REQUIRE(v1->get() == v2->get());
    REQUIRE(v1->get() != v3->get());
    REQUIRE(v1->get() != v4->get());

    v1.release();

    REQUIRE(3 == v2->get());
}
