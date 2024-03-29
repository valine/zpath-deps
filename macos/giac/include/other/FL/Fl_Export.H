/*
 * "$Id: Fl_Export.H 7903 2010-11-28 21:06:39Z matt $"
 *
 * WIN32 DLL export .
 *
 * Copyright 1998-2010 by Bill Spitzak and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems on the following page:
 *
 *     http://www.fltk.org/str.php
 */

#ifndef Fl_Export_H
#  define Fl_Export_H

/*
 * The following is only used when building DLLs under WIN32...
 */

#  if defined(FL_DLL)
#    ifdef FL_LIBRARY
#      define FL_EXPORT	__declspec(dllexport)
#    else
#      define FL_EXPORT	__declspec(dllimport)
#    endif /* FL_LIBRARY */
#  else
#    define FL_EXPORT
#  endif /* FL_DLL */

#endif /* !Fl_Export_H */

/*
 * End of "$Id: Fl_Export.H 7903 2010-11-28 21:06:39Z matt $".
 */
