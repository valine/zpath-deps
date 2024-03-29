//
// "$Id: Fl_JPEG_Image.H 7903 2010-11-28 21:06:39Z matt $"
//
// JPEG image header file for the Fast Light Tool Kit (FLTK).
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
   Fl_JPEG_Image class . */

#ifndef Fl_JPEG_Image_H
#define Fl_JPEG_Image_H
#  include "Fl_Image.H"

/**
  The Fl_JPEG_Image class supports loading, caching,
  and drawing of Joint Photographic Experts Group (JPEG) File
  Interchange Format (JFIF) images. The class supports grayscale
  and color (RGB) JPEG image files.
*/
class FL_EXPORT Fl_JPEG_Image : public Fl_RGB_Image {

public:

  Fl_JPEG_Image(const char *filename);
  Fl_JPEG_Image(const char *name, const unsigned char *data);
};

#endif

//
// End of "$Id: Fl_JPEG_Image.H 7903 2010-11-28 21:06:39Z matt $".
//
