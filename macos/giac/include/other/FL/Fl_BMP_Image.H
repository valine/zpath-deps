//
// "$Id: Fl_BMP_Image.H 7903 2010-11-28 21:06:39Z matt $"
//
// BMP image header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

/* \file
   Fl_BMP_Image widget . */

#ifndef Fl_BMP_Image_H
#define Fl_BMP_Image_H
#  include "Fl_Image.H"

/**
  The Fl_BMP_Image class supports loading, caching,
  and drawing of Windows Bitmap (BMP) image files.
*/
class FL_EXPORT Fl_BMP_Image : public Fl_RGB_Image {

  public:

  Fl_BMP_Image(const char* filename);
};

#endif

//
// End of "$Id: Fl_BMP_Image.H 7903 2010-11-28 21:06:39Z matt $".
//
