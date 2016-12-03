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
#include <regvar.hpp>
#include <genericvar.hpp>
#include <factory.hpp>

using namespace std;

namespace MetaSim {
    
    const RandomVar::BASE_KEY_TYPE DeltaName("delta");
    const RandomVar::BASE_KEY_TYPE UnifName1 ("unif");
    const RandomVar::BASE_KEY_TYPE UnifName2 ("uniform");
    const RandomVar::BASE_KEY_TYPE NormalName1 ("normal");
    const RandomVar::BASE_KEY_TYPE NormalName2 ("gauss");
    const RandomVar::BASE_KEY_TYPE ExponentialName1 ("exp");
    const RandomVar::BASE_KEY_TYPE ExponentialName2 ("exponential");
    const RandomVar::BASE_KEY_TYPE ParetoName ("pareto");
    const RandomVar::BASE_KEY_TYPE PoissonName ("poisson");
    const RandomVar::BASE_KEY_TYPE DetName ("trace");
    const RandomVar::BASE_KEY_TYPE GenericName ("PDF");

    /**
       This namespace should not be visible, and in any case, users
       should never access objects of this namefile. This is used just
       for initialization of the objects needed for the abstract
       factory that creates RandomVars.
    */
    namespace __var_stub
    {
        static registerInFactory<RandomVar, 
                                 DeltaVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerDelta(DeltaName);
    
        static registerInFactory<RandomVar,
                                 UniformVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerUnif1(UnifName1);
    
        static registerInFactory<RandomVar,
                                 UniformVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerUnif2(UnifName2);
  
        static registerInFactory<RandomVar,
                                 NormalVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerNormal1(NormalName1);
  
        static registerInFactory<RandomVar,
                                 NormalVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerNormal2(NormalName2);
  
        static registerInFactory<RandomVar,
                                 ExponentialVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerExp1(ExponentialName1);
  
        static registerInFactory<RandomVar,
                                 ExponentialVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerExp2(ExponentialName2);
    
        static registerInFactory<RandomVar,
                                 ParetoVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerPareto(ParetoName);
        
        static registerInFactory<RandomVar,
                                 PoissonVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerPoisson(PoissonName);
        
        static registerInFactory<RandomVar,
                                 DetVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerDet(DetName);
        
        static registerInFactory<RandomVar,
                                 GenericVar,
                                 RandomVar::BASE_KEY_TYPE>
        registerGeneric(GenericName);
    } // namespace __var_stub

    void __regrandvar_init() {}

} // namespace MetaSim
