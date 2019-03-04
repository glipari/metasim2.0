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
#ifndef NULL
#define NULL 0
#endif

#ifndef __BASETYPE_HPP__
#define __BASETYPE_HPP__

#include <limits>
#include <tick.hpp>

namespace MetaSim {
  /* MAX_RUN is the maximum number of runs allowable in this simulator
   * it is an arbitrary value, feel free to increase it.
   */
  static const size_t MAX_RUN = 100000;
}

#endif
