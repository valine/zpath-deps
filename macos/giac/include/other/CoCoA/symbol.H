#ifndef CoCoA_symbol_H
#define CoCoA_symbol_H

//   Copyright (c)  2005,2008  John Abbott

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


#include "CoCoA/MachineInt.H"

#include <vector>
//using std::vector;
#include <string>
//using std::string;
#include <iosfwd>
//using std::ostream;


namespace CoCoA
{

  class symbol
  {
  public:
    explicit symbol(const std::string& head);                         // symbolic name without indices
    symbol(const std::string& head, MachineInt index);            // symbolic name with 1 index
    symbol(const std::string& head, MachineInt index1, MachineInt index2); // symbolic name with 2 indexes
    symbol(const std::string& head, const std::vector<long>& indices); // symbolic name with many indices
    // Default copy ctor and assignment are fine.
    // Default dtor is fine.

    void myOutputSelf(std::ostream& out) const;
    void myInput(std::istream& in);

    int myCmp(const symbol& sym2) const;
    static bool IsValidHead(const std::string& head);
  private: // data members
    std::string myHead;
    std::vector<long> myIndices;
    friend const std::string& head(const symbol& sym);
    friend long NumIndices(const symbol& sym);
    friend long index(const symbol& sym, long n);
  };


  const std::string& head(const symbol& sym);                   // inline
  long NumIndices(const symbol& sym);                           // inline
  long index(const symbol& sym, long n);
  bool AreDistinct(const std::vector<symbol>& syms);
  bool AreArityConsistent(const std::vector<symbol>& syms);
  std::ostream& operator<<(std::ostream& out, const symbol& sym);
  std::istream& operator>>(std::istream& in, symbol& sym);
  int cmp(const symbol& sym1, const symbol& sym2);              // inline
  bool operator==(const symbol& sym1, const symbol& sym2);      // inline
  bool operator!=(const symbol& sym1, const symbol& sym2);      // inline
  bool operator<(const symbol& sym1, const symbol& sym2);       // inline
  bool operator<=(const symbol& sym1, const symbol& sym2);      // inline
  bool operator>(const symbol& sym1, const symbol& sym2);       // inline
  bool operator>=(const symbol& sym1, const symbol& sym2);      // inline

  std::vector<symbol> SymbolRange(const symbol& sym1, const symbol& sym2);
  std::vector<symbol> SymbolRange(const std::string& head, MachineInt lo, MachineInt hi); // <==> SymbolRange(symbol(head,lo),symbol(head,hi));
  // Four convenience functions -- make creating simple PolyRings easier.
  std::vector<symbol> symbols(const std::string& head1);
  std::vector<symbol> symbols(const std::string& head1, const std::string& head2);
  std::vector<symbol> symbols(const std::string& head1, const std::string& head2, const std::string& head3);
  std::vector<symbol> symbols(const std::string& head1, const std::string& head2, const std::string& head3, const std::string& head4);
  std::vector<symbol> symbols(const std::vector<std::string>& s);

  //---------------------------------------------------------------------------
  // Inline implementations

  inline const std::string& head(const symbol& sym)
  {
    return sym.myHead;
  }


  inline long NumIndices(const symbol& sym)
  {
    return sym.myIndices.size();
  }


  inline int cmp(const symbol& sym1, const symbol& sym2)
  {
    return sym1.myCmp(sym2);
  }

  inline bool operator==(const symbol& sym1, const symbol& sym2)
  {
    return sym1.myCmp(sym2) == 0;
  }

  inline bool operator!=(const symbol& sym1, const symbol& sym2)
  {
    return sym1.myCmp(sym2) != 0;
  }

  inline bool operator<(const symbol& sym1, const symbol& sym2)
  {
    return sym1.myCmp(sym2) < 0;
  }

  inline bool operator<=(const symbol& sym1, const symbol& sym2)
  {
    return sym1.myCmp(sym2) <= 0;
  }

  inline bool operator>(const symbol& sym1, const symbol& sym2)
  {
    return sym1.myCmp(sym2) > 0;
  }

  inline bool operator>=(const symbol& sym1, const symbol& sym2)
  {
    return sym1.myCmp(sym2) >= 0;
  }

} // end of namespace CoCoA



// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/symbol.H,v 1.11 2011/11/09 13:51:29 bigatti Exp $
// $Log: symbol.H,v $
// Revision 1.11  2011/11/09 13:51:29  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.10  2011/03/14 10:30:08  abbott
// Changed size_t into long (in fn interfaces).
//
// Revision 1.9  2011/02/16 14:58:10  bigatti
// -- added    symbols(vector<string> s)
//
// Revision 1.8  2008/12/11 20:12:32  abbott
// Now using MachineInt type in ctors to specify the values of symbol indexes
// (but we check that the values fit into a long).  Corrected two bugs in
// SymbolRange (an undetected overflow and an off-by-1 error).
//
// Revision 1.7  2008/12/11 10:54:01  abbott
// Now indices are [long] values rather than [int].  The extra range will probably
// never be useful, but I prefer to offer it all the same.
//
// Revision 1.6  2008/11/21 21:16:14  abbott
// Added ctor for symbols with 2 indices.
//
// Revision 1.5  2008/04/21 12:32:54  abbott
// Corrected size_t into std::size_t in several header files; in some cases,
// replaced size_t with MachineInt (with consequent changes to impl files).
//
// Revision 1.4  2007/10/30 17:14:11  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.3  2007/05/31 14:50:09  bigatti
// -- added AreDistinct and AreArityConsistent
//
// Revision 1.1.1.1  2007/03/09 15:16:11  abbott
// Imported files
//
// Revision 1.6  2007/03/08 16:55:06  cocoa
// Changed name of "range" function to "SymbolRange".
//
// Revision 1.5  2007/03/08 14:38:07  cocoa
// Added new range function in symbol.H, and tidied many calls to PolyRing
// pseudo ctors (as a consequence).
//
// Revision 1.4  2006/11/27 14:20:09  cocoa
// -- removed #include "CoCoA/config.H"
//
// Revision 1.3  2006/10/27 19:09:45  cocoa
// Replaced some member functions of CoCoA::symbol by friend functions.
// Removed some include dependency on symbol.H
//
// Revision 1.2  2006/10/06 14:04:15  cocoa
// Corrected position of #ifndef in header files.
// Separated CoCoA_ASSERT into assert.H from config.H;
// many minor consequential changes (have to #include assert.H).
// A little tidying of #include directives (esp. in Max's code).
//
// Revision 1.1.1.1  2006/05/30 11:39:37  cocoa
// Imported files
//
// Revision 1.2  2006/03/15 18:09:31  cocoa
// Changed names of member functions which print out their object
// into myOutputSelf -- hope this will appease the Intel C++ compiler.
//
// Revision 1.1.1.1  2005/10/17 10:46:54  cocoa
// Imported files
//
// Revision 1.1  2005/07/08 15:09:29  cocoa
// Added new symbol class (to represent names of indets).
// Integrated the new class into concrete polynomial rings
// and PPMonoid -- many consequential changes.
// Change ctors for the "inline" sparse poly rings: they no
// longer expect a PPMonoid, but build their own instead
// (has to be a PPMonoidOv).
//

#endif
