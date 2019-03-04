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
#ifndef __GENERICVAR_HPP__
#define __GENERICVAR_HPP__

#include <iostream>
#include <map>

#include <randomvar.hpp>

namespace MetaSim {

    /**
       This random variable is used to model a generic distribution.
    */
    class GenericVar: public UniformVar {
        std::map<int, double> _pdf;
        void readPDF(std::ifstream &f, int mode = 0);// throw(Exc);
    public:
        GenericVar(const std::string &filename);

        CLONEABLE(RandomVar, GenericVar)
        
        static RandomVar *createInstance(std::vector<std::string> &par);
        
        virtual double get(void);

  };

} // namespace metasim

#endif /* __GENERICVAR_HPP__ */
