#ifndef CoCoA_BigInt_H
#define CoCoA_BigInt_H

//   Copyright (c)  2003-2011  John Abbott

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


#include <iosfwd> // already included in MachineInt.H
//using std::ostream;
//using std::istream;
#include <string>

#include "gmp.h"

namespace CoCoA
{

  /*-----------------------------------------------------------------*/
  /** \include BigInt.txt  */
  /*-----------------------------------------------------------------*/

  class MachineInt;      // fwd decl -- defined in MachineInt.H
  class OpenMathOutput;  // fwd decl -- defined in OpenMath.H
  class OpenMathInput;   // fwd decl -- defined in OpenMath.H

//???  enum CopyFromMPZMarker { CopyFromMPZ }; // just used for a BigInt ctor

  class BigInt
  {
  private:  // data member
    friend mpz_t& mpzref(BigInt& N);
    friend const mpz_t& mpzref(const BigInt& N);
    mpz_t myRepr;

  public:
    BigInt();
    explicit BigInt(const MachineInt& n);
    explicit BigInt(const std::string& str);
//???AMBIGUATES BigInt(0)    explicit BigInt(const char* str);
    explicit BigInt(const mpz_t N); // copies the mpz_t value!
//???    BigInt(MP_INT to_be_owned); // for efficient return values in operator+ etc.
//???    BigInt(CopyFromMPZMarker, const mpz_t to_be_copied);
    BigInt(const BigInt& from);  // std copy ctor
// BigInt& clone() const;

    ~BigInt();

    BigInt& operator=(const BigInt& rhs);

    // -------- functions that modify at least one argument or `*this' ----------

    BigInt& operator+=(const BigInt& rhs);
    BigInt& operator-=(const BigInt& rhs);
    BigInt& operator*=(const BigInt& rhs);
    BigInt& operator/=(const BigInt& rhs);
    BigInt& operator%=(const BigInt& rhs);
  			
    // Same but with RHS a MachineInt...
    BigInt& operator= (const MachineInt& rhs);
    BigInt& operator+=(const MachineInt& rhs);
    BigInt& operator-=(const MachineInt& rhs);
    BigInt& operator*=(const MachineInt& rhs);
    BigInt& operator/=(const MachineInt& rhs);
    BigInt& operator%=(const MachineInt& rhs);


    BigInt& operator++( );
    BigInt& operator--( );
    const BigInt operator++(int); // INEFFICIENT
    const BigInt operator--(int); // INEFFICIENT

  };


  // I/O FUNCTIONS

  std::ostream& operator<<(std::ostream& out, const BigInt& N);
  std::istream& operator>>(std::istream& in, BigInt& N);

  OpenMathOutput& operator<<(OpenMathOutput& OMOut, const BigInt& N);
  OpenMathInput& operator>>(OpenMathInput& OMIn, BigInt& N);


  // STANDARD ARITHMETIC OPERATIONS

  void swap(BigInt& a, BigInt& b);

  const BigInt abs(const BigInt& N);
  const BigInt operator-(const BigInt& N);

  const BigInt operator+(const BigInt& N1, const BigInt& N2);
  const BigInt operator-(const BigInt& N1, const BigInt& N2);
  const BigInt operator*(const BigInt& N1, const BigInt& N2);
  const BigInt operator/(const BigInt& N1, const BigInt& N2);
  const BigInt operator%(const BigInt& N1, const BigInt& N2);
  const BigInt operator+(const BigInt& N1, const MachineInt& n2);
  const BigInt operator-(const BigInt& N1, const MachineInt& n2);
  const BigInt operator*(const BigInt& N1, const MachineInt& n2);
  const BigInt operator/(const BigInt& N1, const MachineInt& n2);
  long operator%(const BigInt& N1, const MachineInt& n2);
  const BigInt operator+(const MachineInt& n1, const BigInt& N2);
  const BigInt operator-(const MachineInt& n1, const BigInt& N2);
  const BigInt operator*(const MachineInt& n1, const BigInt& N2);
  const BigInt operator/(const MachineInt& n1, const BigInt& N2);
  const BigInt operator%(const MachineInt& n1, const BigInt& N2);
  const BigInt power(const BigInt& base, const BigInt& exponent);
  const BigInt power(const BigInt& base, const MachineInt& exponent);
  const BigInt power(const MachineInt& base, const BigInt& exponent);
  const BigInt power(const MachineInt& base, const MachineInt& exponent);


  // Efficient arithmetic functions...

  void add(BigInt& lhs, const BigInt& N1, const BigInt& N2);
  void sub(BigInt& lhs, const BigInt& N1, const BigInt& N2);
  void mul(BigInt& lhs, const BigInt& N1, const BigInt& N2);
  void div(BigInt& lhs, const BigInt& N1, const BigInt& N2);
  void mod(BigInt& lhs, const BigInt& N1, const BigInt& N2);
  void quorem(BigInt& quo, BigInt& rem, const BigInt& num, const BigInt& den);
  void divexact(BigInt& lhs, const BigInt& N1, const BigInt& N2);

  void add(BigInt& lhs, const BigInt& N1, const MachineInt& n2);
  void sub(BigInt& lhs, const BigInt& N1, const MachineInt& n2);
  void mul(BigInt& lhs, const BigInt& N1, const MachineInt& n2);
  void div(BigInt& lhs, const BigInt& N1, const MachineInt& n2);
  void mod(BigInt& lhs, const BigInt& N1, const MachineInt& n2);
  void quorem(BigInt& quo, BigInt& rem, const BigInt& num, const MachineInt& den); // why is rem not of type MachineInt???
  //???divexact???

  void add(BigInt& lhs, const MachineInt& n1, const BigInt& N2);
  void sub(BigInt& lhs, const MachineInt& n1, const BigInt& N2);
  void mul(BigInt& lhs, const MachineInt& n1, const BigInt& N2);
  void div(BigInt& lhs, const MachineInt& n1, const BigInt& N2);
  void mod(BigInt& lhs, const MachineInt& n1, const BigInt& N2);
  void quorem(BigInt& quo, BigInt& rem, const MachineInt& num, const BigInt& den);
  //???divexact???

  void negate(BigInt& N);
//  void neg(BigInt& lhs, const BigInt& rhs);
//  void abs(BigInt& lhs, const BigInt& rhs);


  // SUNDRY PREDICATES.

  bool IsZero(const BigInt& N);
  bool IsOne(const BigInt& N);
  bool IsMinusOne(const BigInt& N);
  int sign(const BigInt& N);
  bool IsOdd(const BigInt& N);
  bool IsEven(const BigInt& N);
//bool IsPerfectSquare(const BigInt& N);

  // Some of these predicates for MachineInts are in utils.H, the rest are here:
// bool IsPerfectSquare(const MachineInt& n);


  // COMPARISON FUNCTIONS

  int cmp(const BigInt& N1, const BigInt& N2);
  int cmp(const BigInt& N1, const MachineInt& n2);
  int cmp(const MachineInt& n1, const BigInt& N2);

  bool operator==(const BigInt& N1, const BigInt& N2);
  bool operator!=(const BigInt& N1, const BigInt& N2);
  bool operator> (const BigInt& N1, const BigInt& N2);
  bool operator>=(const BigInt& N1, const BigInt& N2);
  bool operator< (const BigInt& N1, const BigInt& N2);
  bool operator<=(const BigInt& N1, const BigInt& N2);
			
  bool operator==(const BigInt& N1, const MachineInt& n2);
  bool operator!=(const BigInt& N1, const MachineInt& n2);
  bool operator> (const BigInt& N1, const MachineInt& n2);
  bool operator>=(const BigInt& N1, const MachineInt& n2);
  bool operator< (const BigInt& N1, const MachineInt& n2);
  bool operator<=(const BigInt& N1, const MachineInt& n2);
      		
  bool operator==(const MachineInt& n1, const BigInt& N2);
  bool operator!=(const MachineInt& n1, const BigInt& N2);
  bool operator> (const MachineInt& n1, const BigInt& N2);
  bool operator>=(const MachineInt& n1, const BigInt& N2);
  bool operator< (const MachineInt& n1, const BigInt& N2);
  bool operator<=(const MachineInt& n1, const BigInt& N2);
			

  // MISCELLANEOUS FUNCTIONS

  double mantissa(const BigInt& N);
  long exponent(const BigInt& N);

  long NumDigits(const BigInt& N, long base=2);
  double log(const BigInt& N);
  long ILogBase(const MachineInt& n, const MachineInt& base);
  long ILogBase(const MachineInt& n, const BigInt& base);
  long ILogBase(const BigInt& N, const MachineInt& base);
  long ILogBase(const BigInt& N, const BigInt& base);

  BigInt RangeFactorial(const MachineInt& lo, const MachineInt& hi); // computes lo*(lo+1)*(lo+2)*...*hi
  const BigInt factorial(const BigInt& N);
  const BigInt factorial(const MachineInt& n);
  const BigInt binomial(const BigInt& N, const BigInt& R);
  const BigInt binomial(const MachineInt& n, const BigInt& R);
  const BigInt binomial(const BigInt& N, const MachineInt& r);
  const BigInt binomial(const MachineInt& n, const MachineInt& r);
  const BigInt fibonacci(const BigInt& N);
  const BigInt fibonacci(const MachineInt& n);

//   const BigInt random(const BigInt& lo, const BigInt& hi);                         ///< rnd number in range lo to hi (incl).
//   const BigInt random(const MachineInt& lo, const MachineInt& hi); ///< rnd number in range lo to hi (incl).
//   const BigInt random(const MachineInt& lo, const BigInt& hi);             ///< rnd number in range lo to hi (incl).
//   const BigInt random(const BigInt& lo, const MachineInt& hi);             ///< rnd number in range lo to hi (incl).

  const BigInt RoundDiv(const BigInt& num, const MachineInt& den); ///< round num/den to an integer (halves round toward +infinity)
  const BigInt RoundDiv(const MachineInt& num, const BigInt& den); ///< round num/den to an integer (halves round toward +infinity)
  const BigInt RoundDiv(const BigInt& num, const BigInt& den);             ///< round num/den to an integer (halves round toward +infinity)

  const BigInt iroot(const MachineInt& n, const MachineInt& r);
  const BigInt iroot(const MachineInt& n, const BigInt& R);
  const BigInt iroot(const BigInt& N, const MachineInt& r);
  const BigInt iroot(const BigInt& N, const BigInt& R);
  bool IsExactIroot(long& ans, const MachineInt& n, const MachineInt& r);
  bool IsExactIroot(BigInt& ans, const MachineInt& n, const MachineInt& r);
  bool IsExactIroot(long& ans, const MachineInt& n, const BigInt& R);
  bool IsExactIroot(BigInt& ans, const MachineInt& n, const BigInt& R);
//???  bool IsExactIroot(long& ans, const BigInt& N, const MachineInt& r);
  bool IsExactIroot(BigInt& ans, const BigInt& N, const MachineInt& r);
//???  bool IsExactIroot(long& ans, const BigInt& N, const BigInt& R);
  bool IsExactIroot(BigInt& ans, const BigInt& N, const BigInt& R);
  long isqrt(const MachineInt& n);
  const BigInt isqrt(const BigInt& N);
  bool IsSquare(const MachineInt& n);
  bool IsSquare(const BigInt& N);
  bool IsPower(const MachineInt& n);
  bool IsPower(const BigInt& N);

  int CmpAbs(const BigInt& N1, const BigInt& N2);
  int CmpAbs(const BigInt& N1, const MachineInt& n2);
  int CmpAbs(const MachineInt& n1, const BigInt& N2);
  int CmpAbs(const MachineInt& n1, const MachineInt& n2);

/*
  friend void           SqrtRem(BigInt& sqrt, BigInt& rem, const BigInt& b);
BigInt         Div2Exp(const BigInt& b, const MachineInt& exponent_of_2);
BigInt         Mod2Exp(const BigInt& b, const MachineInt& exponent_of_2);
BigInt         Mul2Exp(const BigInt& b, const MachineInt& exponent_of_2);
*/


  /////////////////////////////////////////////////////////////////////////////
  // Inline functions

  inline mpz_t& mpzref(BigInt& N)
  {
    return N.myRepr;
  }

  inline const mpz_t& mpzref(const BigInt& N)
  {
    return N.myRepr;
  }


  inline void negate(BigInt& lhs)
  {
    mpz_neg(mpzref(lhs), mpzref(lhs));
  }


  inline BigInt::~BigInt()
  {
    mpz_clear(myRepr);
  }


} // end of namespace CoCoA



// The next few lines contain RCS header/log information.
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/BigInt.H,v 1.7 2012/02/08 13:16:45 bigatti Exp $
// $Log: BigInt.H,v $
// Revision 1.7  2012/02/08 13:16:45  bigatti
// - fixed comment (... starting with -- ...)
//
// Revision 1.6  2012/02/02 15:55:19  abbott
// Replaced include of MachineInt by fwd decl; reactivated include of <iosfwd>
//
// Revision 1.5  2011/11/09 13:38:31  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.4  2011/08/23 14:29:38  bigatti
// -- added log for old name "ZZ.H"
//
// Revision 1.3  2011/08/14 15:52:18  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.2  2011/08/12 16:31:03  abbott
// COMMENTED OUT SOME FNS SO THAT BigInt CAN EXIST ALONGSIDE ZZ
// FOR THE TIME BEING.
//
// Revision 1.1  2011/08/12 15:21:26  abbott
// Added BigInt impl (derived from ZZ); not used by anyone yet.
//
// *************** log for old name: "ZZ.H" ***************
// Revision 1.23  2011/03/21 11:13:25  abbott
// Changed return type for operator%(ZZ,MachineInt) from
// unsigned long to long to fit in with the new coding conventions.
//
// Revision 1.22  2011/03/16 15:32:00  abbott
// Changed arg type "unsigned long" into "const MachineInt&"
// (in commented out code).
//
// Revision 1.21  2011/03/14 10:32:22  abbott
// Changed size_t into long (return types of NumDigits & exponent).
//
// Revision 1.20  2011/01/14 17:21:15  abbott
// Added isqrt, iroot, IsExactIroot, IsSquare, IsPower.
//
// Revision 1.19  2010/12/26 13:03:16  abbott
// Added ILogBase function (to ZZ & QQ).
//
// Revision 1.18  2010/03/22 11:50:31  abbott
// Added ctor from a string.
// Fixed stupid bug in operator-.
//
// Revision 1.17  2010/03/18 13:54:20  abbott
// Added openmath output fns (moved from OpenMath files).
//
// Revision 1.16  2010/03/05 21:35:48  abbott
// Removed unnecessary include of assert.H
//
// Revision 1.15  2010/02/16 10:22:21  abbott
// Changed include directive for gmp.h -- uses quotes instead of <...>
//
// Revision 1.14  2009/12/29 22:44:32  abbott
// Removed buggy proxy class ZZ::rtn.
// Consequent changes for function prototypes also in NumTheory.
// Corrected some minor buglets in NumTheory.
//
// Revision 1.13  2009/11/26 16:18:00  bigatti
// -- including string ZZ.C instead of ZZ.H
//
// Revision 1.12  2009/10/08 13:41:19  abbott
// Renamed "round" into "RoundDiv".
// Added two new signatures for "RoundDiv".
//
// Revision 1.11  2009/06/11 14:05:29  abbott
// CLEANING: Removed several functions which are now gathered in NumTheory.H/C
//           (for example: gcd, lcm, PowerMod, InvMod).
//
// Revision 1.10  2009/06/05 12:08:28  abbott
// Changed return type of operator%(ZZ,MachineInt); it is now unsigned long
// instead of ZZ.
//
// Revision 1.9  2008/12/16 21:14:47  abbott
// In functions taking a machine integer changed arg type from MachineInt
// to const-ref-MachineInt.
//
// Revision 1.8  2008/11/18 10:25:48  abbott
// Added function round.
//
// Revision 1.7  2008/04/22 13:09:16  abbott
// Removed IsPositive and IsNegative functions for ZZs.
// Comparison between RingElem and 0 is now handled specially (specially fast?).
//
// Revision 1.6  2007/10/30 17:14:11  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.5  2007/05/22 22:51:39  abbott
// Changed name of fn ndigits to NumDigits.
// Changed return type of exponent and NumDigits.
// Changed some exceptions from nonstandard to the appropriate standard one.
//
// Revision 1.4  2007/05/21 12:57:28  abbott
// New class for passing machine integers as args; includes some simple
// operations on machine integers (cmp, gcd, IsNegative,...).  Operations
// between ZZ and machine integers modified to use the new class.  Inexact
// integer division (of a ZZ) by a negative value now triggers an error;
// new error for reporting inexact integer division by a negative value.
//
// Revision 1.3  2007/03/23 18:38:43  abbott
// Separated the "convert" functions (and CheckedCast) into their own files.
// Many consequential changes.  Also corrected conversion to doubles.
//
// Revision 1.2  2007/03/16 17:43:05  abbott
// Added new convert function (from ZZ to double).
//
// Revision 1.1.1.1  2007/03/09 15:16:11  abbott
// Imported files
//
// Revision 1.10  2007/03/08 18:42:05  cocoa
// Cleaned up whitespace.
//
// Revision 1.9  2007/01/13 14:14:34  cocoa
// Overhaul of RingHom code: it nows uses SmartPtrIRC, and printing is more logical.
// Have not yet updated the documentation.
//
// Revision 1.8  2006/12/06 17:17:44  cocoa
// -- removed #include "config.H"
//
// Revision 1.7  2006/11/29 11:59:35  cocoa
// -- fixed: convert(double& z, const ZZ& num, const ZZ& den) now returns
//    bool (was void) and does not throw errors
//
// Revision 1.6  2006/11/27 13:38:18  cocoa
// -- added #include <cstddef> //using std::size_t
//
// Revision 1.5  2006/11/27 13:06:23  cocoa
// Anna and Michael made me check without writing a proper message.
//
// Revision 1.4  2006/10/06 14:04:15  cocoa
// Corrected position of #ifndef in header files.
// Separated CoCoA_ASSERT into assert.H from config.H;
// many minor consequential changes (have to #include assert.H).
// A little tidying of #include directives (esp. in Max's code).
//
// Revision 1.3  2006/09/29 11:46:54  cocoa
// Corrected bug in convert(ZZ, ZZ, double) -- now correct and simpler.
// Previously went into infinite loop on negative doubles.
//
// Revision 1.2  2006/06/21 17:08:04  cocoa
// Removed a pointless const.
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
// Revision 1.2  2006/03/14 15:01:49  cocoa
// Improved the implementation of ring member fns for computing powers.
// Should keep Intel C++ compiler quieter too.
//
// Revision 1.1.1.1  2005/10/17 10:46:54  cocoa
// Imported files
//
// Revision 1.2  2005/08/08 16:36:32  cocoa
// Just checking in before going on holiday.
// Don't really recall what changes have been made.
// Added IsIndet function for RingElem, PPMonoidElem,
// and a member function of OrdvArith.
// Improved the way failed assertions are handled.
//
// Revision 1.1.1.1  2005/05/03 15:47:31  cocoa
// Imported files
//
// Revision 1.2  2005/04/19 14:06:04  cocoa
// Added GPL and GFDL licence stuff.
//
// Revision 1.1.1.1  2005/01/27 15:12:13  cocoa
// Imported files
//
// Revision 1.7  2004/11/12 15:49:29  cocoa
// Tidying prior to 0.90 release.
// (a) documentation improved (or marked as poor)
// (b) sundry minor improvements to the code
//
// Revision 1.6  2004/11/11 13:20:47  cocoa
// -- added \include *.txt for doxygen
//
// Revision 1.5  2004/11/04 18:47:42  cocoa
// (1) Ring member functions which previously expected mpz_t args
//     now expect ZZ args.  Numerous minor consequential changes.
// (2) Renamed function which gives access to the mpz_t value inside
//     a ZZ object: previously was raw(...), now is mpzref(...).
//     Plenty of calls had to be altered.
//
// Revision 1.4  2004/05/27 16:14:02  cocoa
// Minor revision for new coding conventions.
//
// Revision 1.3  2004/02/03 16:16:20  cocoa
// Removed pointless IamGCDDomain functions from several concrete rings.
// Added IamOrderedDomain functions where appropriate.
// Tidied ctors for the small finite fields.
//
// Revision 1.2  2003/10/17 10:51:06  cocoa
// Major cleaning, and new naming convention.
//
// Revision 1.1.1.1  2003/09/24 12:55:43  cocoa
// Imported files
//
// Revision 1.2  2003/06/23 16:12:44  abbott
// Minor cleaning prior to public release.
//
// Revision 1.1  2003/05/14 17:12:35  abbott
// Initial revision
//
//

#endif
