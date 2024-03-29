#ifndef CoCoA_DenseUPolyClean_H
#define CoCoA_DenseUPolyClean_H

//   Copyright (c)  2007  Anna Bigatti

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


// Header file for the class DenseUPolyClean

#include "CoCoA/assert.H"
#include "CoCoA/ring.H"

#include <cstddef>
//using std::size_t;
#include <iosfwd>
// using std::ostream;
#include <vector>
// using std::vector;


namespace CoCoA
{


/*-- class DenseUPolyClean ----------------------------------------------*/
/**

  \brief Implementation of "clean" univariate polynomials

  \include DenseUPolyClean.txt
*/
/*-----------------------------------------------------------------*/
  class DenseUPolyClean
  {
  private:
    const ring myCoeffRingValue;   ///< the ring to which all the coeffs belong
    std::size_t myDegPlus1Value;   ///< degree as a size_t
    std::size_t mySizeValue;       ///< size as a size_t
    std::vector<RingElem> myCoeffsValue;  ///< vector of coefficients

  public:
    DenseUPolyClean(const ring& CoeffRing, std::size_t MinCapacity);
    DenseUPolyClean(const DenseUPolyClean& copy, std::size_t MinCapacity);
    DenseUPolyClean(const DenseUPolyClean& copy); ///< never defined, just to check
    ~DenseUPolyClean();
    DenseUPolyClean& operator=(const DenseUPolyClean& rhs);
    DenseUPolyClean& operator=(const MachineInt& rhs);
    DenseUPolyClean& operator=(const BigInt& rhs);
    DenseUPolyClean& operator=(const BigRat& rhs);

    std::size_t myDegPlus1() const  { return myDegPlus1Value; }
    std::size_t mySize() const  { return mySizeValue; }

    static void ourSwap(DenseUPolyClean&, DenseUPolyClean&);
    void myAssignZero();
    void myAssignZeroCoeff(std::size_t d); ///< f_d = 0, no check on size
    void myAssignNonZeroCoeff(ConstRefRingElem c, std::size_t d); ///< f_d = c, no check on size
    void myResize(std::size_t NewSize);
    void myResetDeg(); ///< reset the correct value of deg (assumed to be less than the current value)
    ConstRefRingElem myCoeff(std::size_t d) const;

    friend std::size_t NumTerms(const DenseUPolyClean& f);
    friend ConstRefRingElem LC(const DenseUPolyClean& f);
    void myAddMul(ConstRefRingElem c, std::size_t d, const DenseUPolyClean& g);
    //    void myAddClear(DenseUPolyClean& g);
    void myMulByCoeff(ConstRefRingElem rawc);  // EXCEPTION SAFE?
    void myDivByCoeff(ConstRefRingElem rawc);  // EXCEPTION SAFE?
    void myMulByXExp(int n);
    void myMulByXExp(const BigInt& N);
    void myMulBy1MinusXExp(int n);
    void myMulBy1MinusXExp(const BigInt& N);
    void myNegate();

    friend void add(DenseUPolyClean& lhs, const DenseUPolyClean& g, const DenseUPolyClean& h);
    friend void sub(DenseUPolyClean& lhs, const DenseUPolyClean& g, const DenseUPolyClean& h);
    friend bool div(DenseUPolyClean& lhs, const DenseUPolyClean& g, const DenseUPolyClean& h);
    friend void output(std::ostream& out, const DenseUPolyClean& f); ///< for debugging only
    friend bool IsMonomial(const DenseUPolyClean& f);
    friend bool IsCompatible(const DenseUPolyClean& f, const DenseUPolyClean& g);
    friend bool IsEqual(const DenseUPolyClean& f, const DenseUPolyClean& g);
    friend void deriv(DenseUPolyClean& lhs, const DenseUPolyClean&, std::size_t IndetIndex);

  };

  void deriv(DenseUPolyClean& lhs, const DenseUPolyClean&);


  // Friend functions - must also be declared outside the class (how very tedious).
  bool IsCompatible(const DenseUPolyClean& f, const DenseUPolyClean& g);
  std::size_t NumTerms(const DenseUPolyClean& f);
  ConstRefRingElem LC(const DenseUPolyClean& f);
  void add(DenseUPolyClean& lhs, const DenseUPolyClean& g, const DenseUPolyClean& h);
  void sub(DenseUPolyClean& lhs, const DenseUPolyClean& g, const DenseUPolyClean& h);
  bool div(DenseUPolyClean& lhs, const DenseUPolyClean& g, const DenseUPolyClean& h);
  bool IsZero(const DenseUPolyClean& f);
  bool IsEqual(const DenseUPolyClean& f, const DenseUPolyClean& g);
  void deriv(DenseUPolyClean& lhs, const DenseUPolyClean&, std::size_t IndetIndex);

  // Inline functions.

  inline ConstRefRingElem DenseUPolyClean::myCoeff(std::size_t d) const
  {
    return myCoeffsValue[d];
  }


  inline void swap(DenseUPolyClean& f, DenseUPolyClean& g)
  {
    DenseUPolyClean::ourSwap(f, g);
  }

} // end of namespace CoCoA


// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/DenseUPolyClean.H,v 1.12 2011/11/09 13:38:31 bigatti Exp $
// $Log: DenseUPolyClean.H,v $
// Revision 1.12  2011/11/09 13:38:31  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.11  2011/08/24 10:20:28  bigatti
// -- renamed QQ --> BigRat
//
// Revision 1.10  2011/08/14 15:52:18  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.9  2009/10/28 16:47:01  bigatti
// -- removed useless include MemPool.H
//
// Revision 1.8  2008/12/17 12:11:52  abbott
// Changed type from long to MachineInt in operations which use a machine integer
// in place of a RingElem.  The change is "superficial" but affects many files.
//
// Revision 1.7  2008/04/21 12:32:54  abbott
// Corrected size_t into std::size_t in several header files; in some cases,
// replaced size_t with MachineInt (with consequent changes to impl files).
//
// Revision 1.6  2008/01/29 16:38:47  bigatti
// -- changed: inlined myDegPlus1() and mySize()
//
// Revision 1.5  2007/11/29 17:43:58  bigatti
// -- fixed  operator=  which used automatic copy-ctor
// -- copy-ctor declared but not defined for checking
//
// Revision 1.4  2007/10/30 17:14:12  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.3  2007/10/19 10:04:23  bigatti
// -- RingDenseUPolyClean now allow to specify the MinCapacity for all
//    coeff vectors (to avoid too many reallocations)
//
// Revision 1.2  2007/10/10 14:02:37  bigatti
// -- added myMulBy1MinusXExp
// -- fixed a few little bugs
//
// Revision 1.1  2007/10/05 15:28:56  bigatti
// -- added abstract class DenseUPolyRing for representing dense
//    univariate polynomials
// -- added concrete class RingDenseUPolyClean, the cleanest
//    implementation
// -- just for testing, still horribly inefficient and incomplete
//

#endif
