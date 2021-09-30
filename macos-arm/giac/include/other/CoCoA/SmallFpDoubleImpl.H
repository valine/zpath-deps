#ifndef CoCoA_SmallFpDoubleImpl_H
#define CoCoA_SmallFpDoubleImpl_H

//   Copyright (c)  2005,2009,2011  John Abbott

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


// Header file for the class SmallFpDoubleImpl


#include "CoCoA/assert.H"
#include "CoCoA/GlobalManager.H"
#include "CoCoA/MachineInt.H"

#include <cmath>
//using std::floor;
//using std::fmod;


namespace CoCoA
{

  class BigInt;         // fwd decl -- defined in BigInt.H
  class OpenMathOutput; // fwd decl -- defined in OpenMath.H

  /*-----------------------------------------------------------------*/
  /** \include SmallFpDoubleImpl.txt  */
  /*-----------------------------------------------------------------*/
  class SmallFpDoubleImpl
  {
  public:
    explicit SmallFpDoubleImpl(long p, GlobalSettings::ResidueSetting ResidueChoice = DefaultResidueSetting());
    static bool IsGoodCtorArg(long p);
//      SmallFpDoubleImpl(const BigInt& P);      // complains if P is too big or negative
  private:
    SmallFpDoubleImpl(const SmallFpDoubleImpl&);            // NEVER DEFINED -- copy ctor disabled
    SmallFpDoubleImpl& operator=(const SmallFpDoubleImpl&); // NEVER DEFINED -- assignment disabled

  public:
    typedef double value_t;
    static const int ourDatumSize = sizeof(value_t);

    long myModulus() const;
    void myAssignZero(value_t& lhs) const;                        ///< lhs = 0
    void myAssign(value_t& lhs, value_t x) const;                 ///< lhs = x
    void myAssign(value_t& lhs, const MachineInt& n) const;   ///< lhs = n
    void myAssign(value_t& lhs, const BigInt& N) const;           ///< lhs = N
    void myAssign(value_t& lhs, const BigRat& q) const;           ///< lhs = q
    void myNegate(value_t& lhs, value_t x) const;                 ///< lhs = -x
    void myAdd(value_t& lhs, value_t x, value_t y) const;         ///< lhs = x+y
    void mySub(value_t& lhs, value_t x, value_t y) const;         ///< lhs = x-y
    void myMul(value_t& lhs, value_t x, value_t y) const;         ///< lhs = x*y
    void myDiv(value_t& lhs, value_t x, value_t y) const;         ///< lhs = x/y
    bool myIsDivisible(value_t& lhs, value_t x, value_t y) const; ///< lhs = x/y, if y is non-zero
    void myPower(value_t& lhs, value_t x, long n) const;          ///< lhs = x^n
    value_t myReduceMod(const MachineInt& n) const;           ///< computes n % myModulus

    bool myIsZero(value_t x) const;                        ///< x == 0
    bool myIsOne(value_t x) const;                         ///< x == 1
    bool myIsMinusOne(value_t x) const;                    ///< x == -1
    long myExport(value_t x) const;                        ///< exports x into a long (according to myResiduesAreSymm)
    bool myIsZeroAddMul(value_t& lhs, value_t y, value_t z) const;// lhs += y*z, result says whether lhs == 0.
    bool myIsEqual(value_t x, value_t y) const;  // x == y

  private: // Data members
    const value_t myModulusValue;
    const value_t myDrop;     // PUBLIC???
    const value_t myIterLimit;// PUBLIC???
    const bool myResiduesAreSymm;  // Used only in myExport

  private: // auxiliary functions
    static value_t CheckCtorArg(long p);
    static value_t CheckCtorArg(const BigInt& P);
    static value_t CalcDrop(value_t p);
    static value_t CalcIterLimit(value_t p);
    static value_t MaxInt();
  };  // end of class SmallFpDoubleImpl


  std::ostream& operator<<(std::ostream& out, const SmallFpDoubleImpl& arith);


  //------------------------------------------------------------
  // SmallFpDoubleImpl inline functions
  //------------------------------------------------------------

  inline long SmallFpDoubleImpl::myModulus() const
  {
    return static_cast<long>(myModulusValue);
  }


  inline void SmallFpDoubleImpl::myAssignZero(value_t& lhs) const
  {
    lhs = 0;
  }


  inline void SmallFpDoubleImpl::myAssign(value_t& lhs, value_t x) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    lhs = x;
  }


  inline void SmallFpDoubleImpl::myAssign(value_t& lhs, const MachineInt& n) const
  {
    lhs = myReduceMod(n);
  }


  inline void SmallFpDoubleImpl::myNegate(value_t& lhs, value_t x) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    if (x == 0) lhs = x;
    else lhs = myModulusValue-x;
  }


  inline void SmallFpDoubleImpl::myAdd(value_t& lhs, value_t x, value_t y) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    CoCoA_ASSERT(0 <= y && y < myModulusValue && y == std::floor(y));
    lhs = x+y;
    if (lhs >= myModulusValue) lhs -= myModulusValue;
  }


  inline void SmallFpDoubleImpl::mySub(value_t& lhs, value_t x, value_t y) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    CoCoA_ASSERT(0 <= y && y < myModulusValue && y == std::floor(y));
    if (x < y) lhs = x + (myModulusValue-y);  // avoid trying to create a negative value
    else lhs = x-y;
  }


  inline void SmallFpDoubleImpl::myMul(value_t& lhs, value_t x, value_t y) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    CoCoA_ASSERT(0 <= y && y < myModulusValue && y == std::floor(y));
    lhs = std::fmod(x*y, myModulusValue);
    CoCoA_ASSERT(0 <= lhs && lhs < myModulusValue && lhs == std::floor(lhs));
  }


  inline bool SmallFpDoubleImpl::myIsDivisible(value_t& lhs, value_t x, value_t y) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    CoCoA_ASSERT(0 <= y && y < myModulusValue && y == std::floor(y));
    if (y == 0.0) return false; // cannot call myIsZero here: it is defined below.
    myDiv(lhs, x, y);
    return true;
  }


  inline bool SmallFpDoubleImpl::myIsZero(value_t x) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    return x == 0.0;
  }


  inline bool SmallFpDoubleImpl::myIsOne(value_t x) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    return x == 1.0;
  }


  inline bool SmallFpDoubleImpl::myIsMinusOne(value_t x) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    return x == myModulusValue-1.0;
  }


  inline long SmallFpDoubleImpl::myExport(value_t x) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    if (!myResiduesAreSymm || x <= myModulusValue/2.0)
      return static_cast<long>(x);
    return static_cast<long>(x - myModulusValue);
  }


  inline bool SmallFpDoubleImpl::myIsZeroAddMul(value_t& lhs, value_t x, value_t y) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    CoCoA_ASSERT(0 <= y && y < myModulusValue && y == std::floor(y));
    lhs = fmod(lhs+x*y, myModulusValue);
    CoCoA_ASSERT(0 <= lhs && lhs < myModulusValue && lhs == std::floor(lhs));
    return myIsZero(lhs);
  }


  inline bool SmallFpDoubleImpl::myIsEqual(value_t x, value_t y) const
  {
    CoCoA_ASSERT(0 <= x && x < myModulusValue && x == std::floor(x));
    CoCoA_ASSERT(0 <= y && y < myModulusValue && y == std::floor(y));
    return x==y;
  }


} // end of namespace CoCoA


// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/SmallFpDoubleImpl.H,v 1.15 2012/01/30 11:01:11 abbott Exp $
// $Log: SmallFpDoubleImpl.H,v $
// Revision 1.15  2012/01/30 11:01:11  abbott
// Added naive printing fn (just to help during debugging).
//
// Revision 1.14  2011/11/09 13:50:01  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.13  2011/08/24 10:21:09  bigatti
// -- renamed QQ --> BigRat
//
// Revision 1.12  2011/08/17 11:56:12  abbott
// Added two static_casts to keep compiler quiet.
//
// Revision 1.11  2011/08/14 15:52:17  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.10  2011/05/20 19:26:05  abbott
// Updated SmallFp*Impl: removed all output-related fns (must use myExport instead).
//
// Revision 1.9  2011/05/20 09:44:20  abbott
// Removed some no-longer-useful bits of code.
//
// Revision 1.8  2011/05/19 14:38:27  abbott
// Updated small prime finite field impls to allow user to specify
// separately for each whether to use symmetric or non-negative
// residues for export operations (myExport and printing).
//
// Revision 1.7  2011/03/22 20:06:13  abbott
// Added static mem fn IsGoodCtorArg (called by RingFp pseudo-ctors).
// Commented out ctors which take ZZ arg -- seems useless.
//
// Revision 1.6  2011/03/16 15:30:55  abbott
// Changed arg type from MachineInt into const MachineInt&.
//
// Revision 1.5  2011/03/14 10:28:15  abbott
// Changed unsigned long into long (and unsigned short into short).
//
// Revision 1.4  2009/05/14 09:39:29  abbott
// Added possibility to specify "symmetric" or "non-negative" residues
// in quotients of ZZ.  Affects printing of elements in quotients of ZZ
// (also changed printing of elements in general quotient rings).
// Consequent changes in several tests.
//
// Revision 1.3  2008/12/17 12:11:52  abbott
// Changed type from long to MachineInt in operations which use a machine integer
// in place of a RingElem.  The change is "superficial" but affects many files.
//
// Revision 1.2  2007/10/30 17:14:11  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.1.1.1  2007/03/09 15:16:11  abbott
// Imported files
//
// Revision 1.7  2007/03/08 18:42:05  cocoa
// Cleaned up whitespace.
//
// Revision 1.6  2007/01/11 14:07:42  cocoa
// -- changed names to arguments called "rsh"
//
// Revision 1.5  2006/12/06 17:27:29  cocoa
// -- removed #include "config.H"
//
// Revision 1.4  2006/11/24 17:22:05  cocoa
// -- removed OpenMathFwd.H
//
// Revision 1.3  2006/11/02 13:25:44  cocoa
// Simplification of header files: the OpenMath classes have been renamed.
// Many minor consequential changes.
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
// Revision 1.4  2006/05/12 16:10:58  cocoa
// Added OpenMathFwd.H, and tidied OpenMath.H.
// Many consequential but trivial changes.
//
// Revision 1.3  2006/03/27 12:21:26  cocoa
// Minor silly changes to reduce number of complaints from some compiler or other.
//
// Revision 1.2  2006/03/12 21:28:34  cocoa
// Major check in after many changes
//
// Revision 1.1.1.1  2005/10/17 10:46:54  cocoa
// Imported files
//
// Revision 1.4  2005/10/14 15:25:07  cocoa
// Major tidying and cleaning to small prime finite fields.
// Several consequential changes.  Improved their documentation.
//
// Added Makefile and script to include/CoCoA/ directory to
// keep library.H up to date.
//
// Revision 1.3  2005/10/12 15:52:09  cocoa
// Completed test-RingFp1 and corrected/cleaned the SmallFp*
// and RingFp* files.
//
// Some minor tidying elsewhere.
//
// Revision 1.2  2005/10/11 16:37:30  cocoa
// Added new small prime finite field class (see RingFpDouble).
//
// Cleaned makefiles and configuration script.
//
// Tidied PPMonoid code (to eliminate compiler warnings).
//
// Fixed bug in RingFloat::myIsInteger.
//
// Revision 1.1  2005/09/22 18:04:17  cocoa
// It compiles; the tests run OK.  The examples compile.
// No documentation -- the mindless eurocrats have rendered
// me mindless too.
//

#endif
