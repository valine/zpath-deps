#ifndef CoCoA_io_H
#define CoCoA_io_H

//   Copyright (c)  2005,2009  John Abbott

//   This file is part of the source of CoCoALib, the CoCoA Library.

//   CoCoALib is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.

//   CoCoALib is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.

//   You should have received a copy of the GNU General Public License
//   along with CoCoALib.  If not, see <http://www.gnu.org/licenses/>.


// g++-4.2 requires inclusion of <iostream> for OutputRange -- seems to be a BUG to me.
#include <iostream>
// using std::istream;
// using std::ostream;
#include <vector>
//using std::vector;
#include <list>
//using std::list;

namespace CoCoA
{

  /*-----------------------------------------------------------------*/
  /** \include io.txt  */
  /*-----------------------------------------------------------------*/
  std::istream& GlobalInput();
  std::ostream& GlobalOutput();
  std::ostream& GlobalErrput();
  std::ostream& GlobalLogput();

  std::istream& SetGlobalInput(std::istream& in);
  std::ostream& SetGlobalOutput(std::ostream& out);
  std::ostream& SetGlobalErrput(std::ostream& err);
  std::ostream& SetGlobalLogput(std::ostream& log);


  void InputFailCheck(const std::istream& in, const char* const FnName);

  // This should print out a list or vector of any printable type.
  // Empty list appears as []; otherwise ",  " separated elements
  // between "[" and "]".
  template <typename FwdIterator_t>
  void OutputRange(std::ostream& out, FwdIterator_t start, const FwdIterator_t& end)
  {
    if (start == end) { out << "[]"; return; }
    out << "[" << *start;
    while (++start != end)
      out << ",  " << *start;
    out << "]";
  }

  // Use cout << v syntax to print out a std::vector of printable values.
  // Do I really want to do this globally?
  template <typename entry_t>
  inline std::ostream& operator<<(std::ostream& out, const std::vector<entry_t>& v)
  {
    OutputRange(out, v.begin(), v.end());
    return out;
  }

  // Use cout << l syntax to print out a std::list of printable values.
  // Do I really want to do this globally?
  template <typename entry_t>
  inline std::ostream& operator<<(std::ostream& out, const std::list<entry_t>& v)
  {
    OutputRange(out, v.begin(), v.end());
    return out;
  }

} // end of namespace CoCoA


// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/io.H,v 1.4 2009/06/04 14:31:01 abbott Exp $
// $Log: io.H,v $
// Revision 1.4  2009/06/04 14:31:01  abbott
// Added a comment (complaining about the need to include CoCoA/io.H)
//
// Revision 1.3  2009/05/20 14:23:48  abbott
// Added InputFailCheck function.
//
// Revision 1.2  2007/10/30 17:14:11  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.1.1.1  2007/03/09 15:16:11  abbott
// Imported files
//
// Revision 1.4  2006/12/06 17:17:44  cocoa
// -- removed #include "config.H"
//
// Revision 1.3  2006/10/06 14:04:15  cocoa
// Corrected position of #ifndef in header files.
// Separated CoCoA_ASSERT into assert.H from config.H;
// many minor consequential changes (have to #include assert.H).
// A little tidying of #include directives (esp. in Max's code).
//
// Revision 1.2  2006/08/17 09:46:02  cocoa
// -- added:  comma between list elements
//
// Revision 1.1.1.1  2006/05/30 11:39:36  cocoa
// Imported files
//
// Revision 1.2  2006/03/27 16:15:39  cocoa
// Checking in functions for printing lists and vectors of things,
// so that GPoly.C will compile.  Will reorganize things another day.
//
// Revision 1.1.1.1  2005/10/17 10:46:54  cocoa
// Imported files
//
// Revision 1.1.1.1  2005/05/03 15:47:30  cocoa
// Imported files
//
// Revision 1.2  2005/04/19 14:06:04  cocoa
// Added GPL and GFDL licence stuff.
//
// Revision 1.1.1.1  2005/01/27 15:12:13  cocoa
// Imported files
//
// Revision 1.3  2004/11/11 13:20:47  cocoa
// -- added \include *.txt for doxygen
//
// Revision 1.2  2004/06/29 17:10:22  cocoa
// Partially tidied use of "protected" and "private" in various
// base classes.  Checking in at the end of the day -- it works,
// and I wouldn't want it to be lost next time point's disk
// misbehaves.
//

#endif
