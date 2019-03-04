/***************************************************************************
    begin                : Thu Apr 24 15:54:58 CEST 2003
    copyright            : (C) 2003 by Giuseppe Lipari
    email                : lipari@sssup.it
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include <cstdlib>

#include <limits>
#include <cmath>

#include <randomvar.hpp>
#include <simul.hpp>
#include <strtoken.hpp>
#include <factory.hpp>
#include <regvar.hpp>

namespace MetaSim {

    using namespace std;
    using namespace parse_util;

    RandomGen RandomVar::_stdgen(1);

    RandomGen* RandomVar::_pstdgen(&_stdgen);

    const RandNum RandomGen::A = 16807;
    const RandNum RandomGen::M = 2147483647;
    const RandNum RandomGen::Q = 127773; // M div A
    const RandNum RandomGen::R = 2836;   // M mod A


    const char * const RandomVar::Exc::_FILEOPEN = "Unable to open RandFile";
    const char * const RandomVar::Exc::_FILECLOSE = "Too short RandFile";
    const char * const RandomVar::Exc::_WRONGPDF = "Malformed PDF";


    /*---------------------------------------------------*/

    RandomGen::RandomGen(RandNum s) : _seed(s), _xn(s)
    {
    }

    RandNum RandomGen::sample()
    {
        RandNum xq, xr;

        xq = _xn / Q;
        xr = _xn % Q;

        _xn = A * xr - R * xq;
        if (_xn < 0) _xn += M;

        return _xn;
    };

    void RandomGen::init(RandNum s)
    {
        _xn = _seed = s;
    }

    /*---------------------------------------------------*/

    const unsigned long PoissonVar::CUTOFF = 10000;

    RandomVar::RandomVar() : _gen(_pstdgen)
    {
      __regrandvar_init();
    }

    RandomVar::RandomVar(const RandomVar &r) : _gen(r._gen)
    {
    }

    RandomVar::~RandomVar()
    {
    }

    RandomGen* RandomVar::changeGenerator(RandomGen *g)
    { 
        RandomGen *old = _pstdgen;
        _pstdgen = g; 
        return old;
    }

    void RandomVar::restoreGenerator()
    {
        _pstdgen = &_stdgen;
    }


    /*-----------------------------------------------------*/

    unique_ptr<DeltaVar> DeltaVar::createInstance(vector<string> &par) 
    {
        if (par.size() != 1) 
            throw ParseExc("Wrong number of parameters", "DeltaVar");
        double a = atof(par[0].c_str());
        return unique_ptr<DeltaVar>(new DeltaVar(a));
    }

    /*-----------------------------------------------------*/

    double UniformVar::get()
    {
        double tmp;
        tmp = _gen->sample();
        tmp = tmp * (_max - _min) / _gen->getModule() + _min;
  
        return tmp;
    };

    unique_ptr<UniformVar> UniformVar::createInstance(vector<string> &par) 
    {
        double a,b;

        if (par.size() != 2)
            throw ParseExc("Wrong number of parameters", "UniformVar");

        a = atof(par[0].c_str());
        b = atof(par[1].c_str());
        return unique_ptr<UniformVar>(new UniformVar(a,b));
    }

    /*-----------------------------------------------------*/

    double ExponentialVar::get()
    {
        return -log(UniformVar::get()) / _lambda;
    }

    std::unique_ptr<ExponentialVar> ExponentialVar::createInstance(vector<string> &par)
    {
        if (par.size() != 1)
            throw ParseExc("Wrong number of parameters", "ExponentialVar");

        double a = atof(par[0].c_str());
        return unique_ptr<ExponentialVar>(new ExponentialVar(a));
    }

    /*-----------------------------------------------------*/

    double WeibullVar::get()
    {
        return _l * pow(-log(UniformVar::get()), 1.0 / _k);
    }

    std::unique_ptr<WeibullVar> WeibullVar::createInstance(vector<string> &par)
    {
        if (par.size() != 2)
            throw ParseExc("Wrong number of parameters", "WeibullVar");

        double a = atof(par[0].c_str());
        double b = atof(par[1].c_str());
        return unique_ptr<WeibullVar>(new WeibullVar(a, b));
    }

    /*-----------------------------------------------------*/


    double ParetoVar::get()
    {
        return _mu * pow (UniformVar::get(), -1/_order);
    };

    unique_ptr<ParetoVar> ParetoVar::createInstance(vector<string> &par) 
    {
        double a,b;

        if (par.size() != 2) 
            throw ParseExc("Wrong number of parameters", "ParetoVar");

        a = atof(par[0].c_str());
        b = atof(par[1].c_str());
        return unique_ptr<ParetoVar>(new ParetoVar(a,b));
    } 

    /*-----------------------------------------------------*/

    double NormalVar::get()
    {
        const double epsilon = std::numeric_limits<double>::min();
        const double two_pi = 2.0*3.14159265358979323846;

        static double z0, z1;
        static bool generate;
        generate = !generate;
        
        if (!generate)
            return z1 * _sigma + _mu;
        
        // generate two uniform samples
        double u1, u2;
        do
        {
            u1 = UniformVar::get();
            u2 = UniformVar::get();
        }
        while ( u1 <= epsilon );
        
        z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
        z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
        
        return z0 * _sigma + _mu;
    }


    std::unique_ptr<NormalVar> NormalVar::createInstance(vector<string> &par) 
    {
        double a,b;

        if (par.size() != 2) 
            throw ParseExc("Wrong number of parameters", "NormalVar");

        a = atof(par[0].c_str());
        b = atof(par[1].c_str());
        return unique_ptr<NormalVar>(new NormalVar(a,b));
    } 


    /*-----------------------------------------------------*/

    double PoissonVar::get() 
    {
        double u = UniformVar::get();
        double F = exp(-_lambda);
        double S = F;

        for (unsigned int i = 1; i < CUTOFF; ++i) {
            if (u < S) return i - 1;
            F = F * _lambda / double(i);
            S += F;
        }
        return CUTOFF;
    }

    unique_ptr<PoissonVar> PoissonVar::createInstance(vector<string> &par) 
    {
        double a;

        if (par.size() != 1)
            throw ParseExc("Wrong number of parameters", "PoissonVar");
        a = atof(par[0].c_str());
        return unique_ptr<PoissonVar>(new PoissonVar(a));
    } 


    /*-----------------------------------------------------*/

    DetVar::DetVar(const std::string &filename) :
        _array()
    {
        DBGENTER(_RANDOMVAR_DBG_LEV);
        ifstream inFile;
        double v;

        DBGPRINT_2("Reading from ", filename);

        inFile.open(filename.c_str());
        if (!inFile.is_open()) {
            string errMsg = Exc::_FILEOPEN  + string(filename) + "\n";
            throw Exc(errMsg, "DetVar");
        }
        while (!inFile.eof()) {
            inFile >> v;
            _array.push_back(v);
            DBGVAR(_array.back());
        }
        inFile.close();
        _count = 0;
    };

    DetVar::DetVar(vector<double> &a) : _array(a) 
    {
        _count = 0;
    }

    DetVar::DetVar(double *a, int s)
    {
        for (int i = 0; i < s; ++i) 
            _array.push_back(a[i]);
        _count = 0;
    }

    double DetVar::get() 
    {
        if (_count >= _array.size())
            _count = 0;
        return _array[_count++];
    }

    double DetVar::getMaximum() 
    {
        if (_array.empty()) return 0;
        double max = _array[0];
        for (unsigned int i = 1; i < _array.size(); i++)
            if (_array[i] > max) max = _array[i];
        return max;
    }

    double DetVar::getMinimum() 
    {
        if (_array.empty()) return 0;
        double min = _array[0];
        for (unsigned int i = 1; i < _array.size(); i++)
            if (_array[i] < min) min = _array[i];
        return min;
    }

    unique_ptr<DetVar> DetVar::createInstance(vector<string> &par) 
    {
        if (par.size() != 1) 
            throw ParseExc("Wrong number of parameters", "DetVar");

        return unique_ptr<DetVar>(new DetVar(par[0]));
    } 

    unique_ptr<RandomVar> RandomVar::parsevar(const std::string &str)
    {
        string token = get_token(str);
        DBGPRINT_2("token = ",  token);
                
        string p = get_param(str);
        DBGPRINT_2("parms = ", p);

        vector<string> parms = split_param(p);
  
        for (size_t i = 0; i < parms.size(); ++i) 
            DBGPRINT_4("par[", i, "] = ", parms[i]);
                
        unique_ptr<RandomVar> var(FACT(RandomVar).create(token,parms));
                
        if (var.get() == nullptr) throw ParseExc("parsevar", str);
                                
        return var;
    }
} // namespace MetaSim
