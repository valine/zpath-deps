#ifndef CoCoA_tmp_H
#define CoCoA_tmp_H

//   Copyright (c)  2006  John Abbott

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


// This contains sundry things which may eventually become stable parts of
// the CoCoA library.


#include "CoCoA/error.H"

#include <list>
//using std::list;
#include <vector>
//using std::vector;
#include <algorithm>
//using std::for_each;
//using std::find_if;

namespace CoCoA
{

  ////////////////////////////////////////////////////////////
  // Functions for computing products of lists and vectors.

  // This class is simply to permit use of std::for_each.
  template <typename arith_t>
  class SeqProd
  {
  public:
    SeqProd(const arith_t& InitialValue): myProdSoFar(InitialValue) {}
    // Default copy ctor, assignment, and dtor are all OK.
    void operator()(const arith_t& NextValue) { myProdSoFar *= NextValue; }
    const arith_t& myCurrentValue() const { return myProdSoFar; }
  private:
    arith_t myProdSoFar;
  };

  template <typename InputIterator, typename arith_t>
  arith_t product(InputIterator begin, InputIterator end, const arith_t& InitialValue)
  {
    return std::for_each(begin, end, SeqProd<arith_t>(InitialValue)).myCurrentValue();
  }

  template <typename ListOrVector>
  typename ListOrVector::value_type product(const ListOrVector& V)
  {
    if (V.empty()) CoCoA_ERROR("Untyped empty product", "product(list or vector)");
    return product(++V.begin(), V.end(), V.front());
  }


  ////////////////////////////////////////////////////////////
  // Functions for computing sums of lists and vectors.

  // This class is simply to permit use of for_each.
  template <typename arith_t>
  class SeqSum
  {
  public:
    SeqSum(const arith_t& InitialValue): mySumSoFar(InitialValue) {}
    // Default copy ctor, assignment, and dtor are all OK.
    void operator()(const arith_t& NextValue) { mySumSoFar += NextValue; }
    const arith_t& myCurrentValue() const { return mySumSoFar; }
  private:
    arith_t mySumSoFar;
  };

  template <typename InputIterator, typename arith_t>
  arith_t sum(InputIterator begin, InputIterator end, const arith_t& InitialValue)
  {
    return std::for_each(begin, end, SeqSum<arith_t>(InitialValue)).myCurrentValue();
  }

  template <typename ListOrVector>
  typename ListOrVector::value_type sum(const ListOrVector& V)
  {
    if (V.empty()) CoCoA_ERROR("Untyped empty sum", "sum(list or vector)");
    return sum(++V.begin(), V.end(), V.front());
  }


  ////////////////////////////////////////////////////////////
  // Functions for checking all elements have the same owner

// This class is simply to permit use of find_if.
  template <class elem_t>
  class HasDifferentOwner  // ??? ANNA: struct or class?
  {
  public:
    HasDifferentOwner(const elem_t& x): myValue(x) {};
    // Default copy ctor, assignment, and dtor are all OK.
    bool operator() (const elem_t& x) const { return owner(x) != owner(myValue); }
  private:
    elem_t myValue;
  };

  template <class elem_t>
  bool HasUniqueOwner(const std::vector<elem_t>& v)
  {
    //    if (v.empty()) CoCoA_ERROR("empty list/vector", "HasUniqueOwner(vector)");
    if (v.empty()) return true;
    return find_if(++v.begin(), v.end(), HasDifferentOwner<elem_t>(v.front()))
      == v.end();
  }


} // end of namespace CoCoA



// RCS header/log in the next few lines.
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/tmp.H,v 1.6 2011/02/10 15:25:39 bigatti Exp $
// $Log: tmp.H,v $
// Revision 1.6  2011/02/10 15:25:39  bigatti
// -- fixed HasUniqueOwner for empty lists
//
// Revision 1.5  2009/11/20 15:52:43  bigatti
// -- fixed string
//
// Revision 1.4  2009/07/24 15:15:58  bigatti
// -- unified sum (and product) for C++ lists and vectors
// -- added: HasUniqueOwner for vector of elements with function "owner"
//
// Revision 1.3  2009/05/20 14:26:19  abbott
// CVS says something has changed, but I cannot see what (maybe whitespace?).
//
// Revision 1.2  2007/10/30 17:14:11  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.1.1.1  2007/03/09 15:16:11  abbott
// Imported files
//
// Revision 1.3  2006/12/06 17:18:40  cocoa
// -- removed #include "config.H"
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
// Revision 1.3  2006/03/27 16:15:39  cocoa
// Checking in functions for printing lists and vectors of things,
// so that GPoly.C will compile.  Will reorganize things another day.
//
// Revision 1.2  2006/03/27 12:21:25  cocoa
// Minor silly changes to reduce number of complaints from some compiler or other.
//
// Revision 1.1  2006/01/20 17:44:20  cocoa
// Friday afternoon check-in: you have been warned!
// Fixed ref counting bug in SmartPtrIRC.
// Added sum/product functions in tmp.H.
// Minor tidying here and there.
//

#endif
