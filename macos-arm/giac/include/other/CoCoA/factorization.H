#ifndef CoCoA_factorization_H
#define CoCoA_factorization_H

//   Copyright (c)  2009  John Abbott

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
//   -------------------------------------------------------------------------

#include <vector>
// using std::vector;
#include <iostream>
//using std::ostream;  -- needed for the templated operator<<

namespace CoCoA
{

  // This is really just a struct: it merely contains the result of a factorization.
  template <typename T>
  class factorization
  {
  public:
    factorization(const std::vector<T>& factors, const std::vector<long>& exponents, const T& RemainingFactor):
        myFactors(factors),
        myExponents(exponents),
        myRemainingFactor(RemainingFactor)
      {}

    // Data members -- deliberately publicly readable & modifiable.
    std::vector<T> myFactors;
    std::vector<long> myExponents;
    T myRemainingFactor;
  };


  template <typename T>
  std::ostream& operator<<(std::ostream& out, const factorization<T>& facs)
  {
    return out << "factorization(myFactors=" << facs.myFactors
               << ", myExponents=" << facs.myExponents
               << ", myRemainingFactor=" << facs.myRemainingFactor << ")";
  }


} // end of namespace CoCoA



// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/factorization.H,v 1.3 2012/01/30 11:05:19 abbott Exp $
// $Log: factorization.H,v $
// Revision 1.3  2012/01/30 11:05:19  abbott
// Changed include "CoCoA/io.H" into include <iostream>
//
// Revision 1.2  2011/12/05 16:55:43  bigatti
// -- changed: MachineInteger --> MachineInt (just in comment)
//
// Revision 1.1  2009/06/05 12:14:55  abbott
// Major change:
//   created new files NumTheory.H/C  which contain basic number theory operations
//   removed several basic number theory operations from ZZ.H/C
//   removed gcd from MachineInt.H/C
//   changed names of some basic fns:
//      IsPPrime -> IsProbPrime
//      invmod -> InvMod    (changed signature too)
//      powermod -> PowerMod  (changed signature too)
//   added new fns
//      NextProbPrime & PrevProbPrime
//   consequent changes to other code and tests and examples
//
//

#endif
