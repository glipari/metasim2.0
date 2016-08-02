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
#ifndef __BASEEXC_HPP__
#define __BASEEXC_HPP__

#include <stdexcept>
#include <string>
#include <sstream>

namespace MetaSim {

    /**
        \ingroup metasim_exc

        Basic exception class.

        This class is the base used for handling exceptions. Any
        exception of the simulator has to be derived from this class.

        @version 1.2
        @author Antonino Casile, Luigi Palopoli, Alessio Balsini
    */
    class BaseExc : public std::runtime_error {
    protected:
        /// Contains a brief description of the exception.
        std::string _what;

    public:
        /** Constructor.
         *  @param message contains the error message.
         *  @param cl contains the name of the class where the exception has been
         *  raised.
         *  @param md contains the name of the module where the exception
         *  has been raised.
         */
        BaseExc(const std::string &message,
                const std::string &cl="unknown",
                const std::string &md="unknown") :
          std::runtime_error("")
              {
                  std::stringstream ss;
                  ss << "Class=" << cl
                     << " Module=" << md
                     << " Message:" << message;
                  static_cast<std::runtime_error&>(*this) = std::runtime_error(ss.str());
              }

        virtual ~BaseExc() throw() {}
    };


    // a couple of useful macros
#define DECL_EXC(EXC, CLASS) \
    class EXC : public BaseExc { public: \
            EXC(const std::string &m) : BaseExc(m, CLASS, __FILE__) {} }

#define THROW_EXC(EXC, MSG) throw EXC(MSG  ":" __LINE__)

} // namespace MetaSim

#endif
