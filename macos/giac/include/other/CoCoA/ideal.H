#ifndef CoCoA_ideal_H
#define CoCoA_ideal_H

//   Copyright (c)  2003-2010  John Abbott

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


// Header file for the abstract class ideal


#include "CoCoA/ring.H"
#include "CoCoA/bool3.H"
#include "CoCoA/SmartPtrIRC.H"

#include <cstddef>
//using std::size_t;
#include <iosfwd>
//using std::ostream;
#include <vector>
//using std::vector;

namespace CoCoA
{

  class OpenMathOutput; // fwd decl -- defined in OpenMath.H
  class IdealBase;      // fwd decl -- defined later in this file

  class ideal
  {
  public:
    explicit ideal(IdealBase* IPtr);    //??? public???
    explicit ideal(ConstRefRingElem r);                      // make a principal ideal
    ideal(ConstRefRingElem r1, ConstRefRingElem r2);
    ideal(ConstRefRingElem r1, ConstRefRingElem r2, ConstRefRingElem r3);
    ideal(ConstRefRingElem r1, ConstRefRingElem r2, ConstRefRingElem r3, ConstRefRingElem r4);
    explicit ideal(const std::vector<RingElem>& gens);       // make the ideal gen'd by gens !={}
    ideal(const ring& R, const std::vector<RingElem>& gens); // make the ideal generated by gens
    ideal(const ideal& copy);
    ideal& operator=(const ideal& rhs);
    ~ideal();

    const IdealBase* myIdealPtr() const;
//???    IdealBase* operator->();              // allow non-const member fns to be called
    const IdealBase* operator->() const;  // allow const member fns to be called
  private:
    IdealBase* myPtr;
    friend IdealBase* MakeUnique(ideal& I);
  };

//   class IdealBase; // fwd decl, defn immediately below.
//   typedef SmartPtrIRC<const IdealBase> ideal;  //???? const???

  class IdealBase  //???: protected IntrusiveReferenceCount
  {
  protected: // ref count accessible only to friends and derived classes.
    friend class ideal;
    friend IdealBase* MakeUnique(ideal& I); // so it can call RefCountIsOne
    mutable std::size_t myRefCount; // every ideal has an intrusive reference count
    void myRefCountInc() const;
    void myRefCountDec() const;
    bool myRefCountIsOne() const;

  protected:
    mutable bool3 IamPrimeFlag;       // NB these two values are NOT INDEPENDENT
    mutable bool3 IamMaximalFlag;     // (because maximality implies primality)

  protected:
    IdealBase(): myRefCount(0), IamPrimeFlag(), IamMaximalFlag() {};
    virtual ~IdealBase();

  public:
    virtual IdealBase* myClone() const = 0;
//???    virtual void swap(ideal& other) = 0;

    virtual const ring& myAmbientRing() const = 0;
    virtual bool IamZero() const = 0;
    virtual bool IamOne() const;                 ///< virtual + default impl

    virtual bool IhaveElem(RingElemConstRawPtr rawx) const = 0;
    bool IamMaximal() const;
    virtual void mySetMaximalFlag(bool b) const; ///< virtual + default impl
    bool IamPrime() const;
    virtual void mySetPrimeFlag(bool b) const;   ///< virtual + default impl

    virtual void myReduceMod(RingElemRawPtr rawx) const = 0; ///< r elem of R, where I is ideal in R
    virtual void myAdd(const ideal&) = 0;
    virtual void myMul(const ideal&) = 0;
    virtual void myIntersect(const ideal&) = 0;
    virtual void myColon(const ideal&) = 0;
    virtual void mySaturate(const ideal&);
    virtual void myElim(const std::vector<RingElem>& v); // default: error
    virtual void myDivMod(RingElemRawPtr rawlhs, RingElemConstRawPtr rawnum, RingElemConstRawPtr rawden) const = 0; // lhs = num/den modulo the ideal  (lhs = 0 if quotient does not exist)

    virtual const std::vector<RingElem>& myGens() const = 0; // gens as specified by user
    virtual const std::vector<RingElem>& myTidyGens() const = 0; // tidier set of gens

    virtual void myOutputSelf(std::ostream& out) const;
    virtual void myOutputSelf(OpenMathOutput& OMOut) const;
  protected:
    virtual void myMaximalTest() const = 0; // sets IamMaximalFlag accordingly, may also set IamPrimeFlag to true
    virtual void myPrimeTest() const = 0;   // sets IamPrimeFlag accordingly, may also set IamMaximalFlag to false
  };


  RingElem operator%(const MachineInt& n, const ideal& I);   ///< reduce n modulo I
  RingElem operator%(const BigInt& N, const ideal& I);    ///< reduce N modulo I
  RingElem operator%(const BigRat& Q, const ideal& I);        ///< reduce N modulo I
  RingElem operator%(ConstRefRingElem r, const ideal& I); ///< reduce r modulo I
  RingElem NF(ConstRefRingElem r, const ideal& I); ///< reduce r modulo I, same as %
  const ring& AmbientRing(const ideal& I);
  const ideal operator+(const ideal& I, const ideal& J);
  const ideal operator*(const ideal& I, const ideal& J);
  ideal& operator+=(ideal& I, const ideal& J);
  ideal& operator*=(ideal& I, const ideal& J);
  ideal power(const ideal& I, const MachineInt& n);
  ideal power(const ideal& I, const BigInt& N);

  const ideal intersect(const ideal& I, const ideal& J);
  const ideal colon(const ideal& I, const ideal& J);
  bool IsContained(const ideal& I, const ideal& J);  // Is ideal I contained in ideal J?
  bool operator==(const ideal& I, const ideal& J);
  inline bool operator!=(const ideal& I, const ideal& J) { return !(I==J); }
  bool IsElem(ConstRefRingElem r, const ideal& I);
  bool IsElem(const BigInt& r, const ideal& I);
  bool IsElem(const BigRat& r, const ideal& I);
  bool IsElem(const MachineInt& r, const ideal& I);
  std::ostream& operator<<(std::ostream& out, const ideal& I);
  OpenMathOutput& operator<<(OpenMathOutput& OMOut, const ideal& I);

  //---------------------------------------------------------------------------
  // Inline functions

  inline void IdealBase::myRefCountInc() const { ++myRefCount; }
  inline void IdealBase::myRefCountDec() const { if (--myRefCount == 0) delete this; }
  inline bool IdealBase::myRefCountIsOne() const { return myRefCount == 1; }


  inline const IdealBase* ideal::myIdealPtr() const
  { return myPtr; }


//   inline IdealBase* ideal::operator->()              // allow non-const member fns to be called
//   {
//     CoCoA_ASSERT(myPtr->RefCountIsOne());
//     return myPtr;
//   }


  inline const IdealBase* ideal::operator->() const  // allow const member fns to be called
  { return myPtr; }


  inline bool IsZero(const ideal& I)
  {
    return I->IamZero();
  }


  inline bool IsOne(const ideal& I)
  {
    return I->IamOne();
  }


  inline bool IsMaximal(const ideal& I)
  {
    return I->IamMaximal();
  }


  inline bool IsPrime(const ideal& I)
  {
    return I->IamPrime();
  }


  inline const std::vector<RingElem>& gens(const ideal& I)
  {
    return I->myGens();
  }


  inline const std::vector<RingElem>& TidyGens(const ideal& I)
  {
    return I->myTidyGens();
  }


  inline const ring& AmbientRing(const ideal& I)
  {
    return I->myAmbientRing();
  }


  inline RingElem NF(ConstRefRingElem r, const ideal& I)
  {
    return r%I;
  }

} // end of namespace CoCoA




// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/ideal.H,v 1.20 2011/11/09 13:51:29 bigatti Exp $
// $Log: ideal.H,v $
// Revision 1.20  2011/11/09 13:51:29  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.19  2011/08/24 10:22:45  bigatti
// -- renamed QQ --> BigRat
//
// Revision 1.18  2011/08/14 15:52:17  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.17  2011/05/24 14:52:39  abbott
// Removed several "old style" pseudo ctors for principal ideals.
// Cleaned defn of power.
//
// Revision 1.16  2011/05/23 12:35:30  bigatti
// -- added power(ideal, long/ZZ)
//
// Revision 1.15  2011/03/11 10:54:42  bigatti
// -- added mySaturate
// -- added IsElem for integer values
//
// Revision 1.14  2011/02/28 16:46:06  bigatti
// -- added operator!=
//
// Revision 1.13  2011/01/28 17:58:07  bigatti
// -- added myElim
//
// Revision 1.12  2010/12/17 16:12:40  abbott
// Added two missing "explicit" keywords.
//
// Revision 1.11  2010/09/02 13:05:42  bigatti
// -- changed comment "fwd decl"
//
// Revision 1.10  2010/06/10 08:00:02  bigatti
// -- fixed naming conventions
//
// Revision 1.9  2010/03/18 13:55:25  abbott
// Added pseudo-ctors for principal ideals from QQs.
//
// Revision 1.8  2010/02/04 10:02:39  bigatti
// -- added "mul" (implemented only for SparsePolyRing)
//
// Revision 1.7  2009/12/03 17:35:43  abbott
// Moved IsElem fn from .H to .C file, so that .H does not need
// to include CoCoA/error.H.
//
// Revision 1.6  2009/07/30 15:36:28  bigatti
// -- added convenience constructor for ideals with 2, 3, 4 generators.
//
// Revision 1.5  2009/07/24 15:12:33  bigatti
// -- new constructors: ideal(r), ideal(gens)
//
// Revision 1.4  2008/12/17 12:11:52  abbott
// Changed type from long to MachineInt in operations which use a machine integer
// in place of a RingElem.  The change is "superficial" but affects many files.
//
// Revision 1.3  2007/12/07 15:27:01  bigatti
// -- default implementation of "IamOne" in ideal.C
//
// Revision 1.2  2007/10/30 17:14:11  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.1.1.1  2007/03/09 15:16:11  abbott
// Imported files
//
// Revision 1.6  2007/01/15 13:33:34  cocoa
// -- added prefix "raw" to RawPtr arguments names
//
// Revision 1.5  2006/12/06 17:17:44  cocoa
// -- removed #include "config.H"
//
// Revision 1.4  2006/11/24 17:40:58  cocoa
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
// Revision 1.1.1.1  2006/05/30 11:39:36  cocoa
// Imported files
//
// Revision 1.5  2006/05/12 16:10:58  cocoa
// Added OpenMathFwd.H, and tidied OpenMath.H.
// Many consequential but trivial changes.
//
// Revision 1.4  2006/03/21 09:43:14  cocoa
// Changed names of some member fns of ideals (dealing with setting and testing
// the flags for primeness and maximality).  Hope icc will complain less now.
//
// Revision 1.3  2006/03/15 18:09:31  cocoa
// Changed names of member functions which print out their object
// into myOutputSelf -- hope this will appease the Intel C++ compiler.
//
// Revision 1.2  2006/01/19 16:34:42  cocoa
// -- added NF, myReduceMod functions (not yet tested)
//
// Revision 1.1.1.1  2005/10/17 10:46:54  cocoa
// Imported files
//
// Revision 1.1.1.1  2005/05/03 15:47:30  cocoa
// Imported files
//
// Revision 1.5  2005/04/29 15:42:02  cocoa
// Improved documentation for GMPAllocator.
// Added example program for GMPAllocator.
// Added example program for simple ops on polynomials.
// Added two new ctors for (principal) ideals (from long, and from ZZ).
// Added (crude) printing for PPMonoids.
// Updated library.H (#included GMPAllocator.H).
//
// Revision 1.4  2005/04/20 15:40:48  cocoa
// Major change: modified the standard way errors are to be signalled
// (now via a macro which records filename and line number).  Updated
// documentation in error.txt accordingly.
//
// Improved the documentation in matrix.txt (still more work to be done).
//
// Revision 1.3  2005/04/19 14:06:04  cocoa
// Added GPL and GFDL licence stuff.
//
// Revision 1.2  2005/02/11 14:15:20  cocoa
// New style ring elements and references to ring elements;
// I hope I have finally got it right!
//
// Revision 1.1.1.1  2005/01/27 15:12:13  cocoa
// Imported files
//
// Revision 1.11  2004/11/12 15:49:29  cocoa
// Tidying prior to 0.90 release.
// (a) documentation improved (or marked as poor)
// (b) sundry minor improvements to the code
//
// Revision 1.10  2004/11/11 13:02:16  cocoa
// -- added \include *.txt for doxygen
//
// Revision 1.9  2004/11/05 15:30:57  cocoa
// Separated FieldIdealImpl from the "abstract" classes ideal and
// IdealBase.
//
// Revision 1.8  2004/07/20 15:04:06  cocoa
// The next step in the new "ring element" conversion process:
// handling the case of creating a "const RefRingElem" object
// (since C++ refuses to do this properly itself).
//
// Revision 1.7  2004/06/29 17:10:22  cocoa
// Partially tidied use of "protected" and "private" in various
// base classes.  Checking in at the end of the day -- it works,
// and I wouldn't want it to be lost next time point's disk
// misbehaves.
//
// Revision 1.6  2004/06/25 16:04:37  cocoa
// -- removed 1 comma for new compiler on vector
//
// Revision 1.5  2004/05/27 16:14:02  cocoa
// Minor revision for new coding conventions.
//
// Revision 1.4  2004/03/20 17:46:10  cocoa
// Check in prior to departure to RWCA
//
// Revision 1.3  2003/10/17 10:51:06  cocoa
// Major cleaning, and new naming convention.
//
// Revision 1.2  2003/10/09 12:16:38  cocoa
// New coding convention for rings.
//
// Revision 1.3  2003/06/23 17:00:21  abbott
// Minor cleaning prior to public release.
//
// Revision 1.2  2003/05/30 11:59:35  abbott
// Corrected ctor for a principal ideal (was missing const).
//
// Revision 1.1  2003/04/24 14:43:23  abbott
// Initial revision
//
//

#endif
