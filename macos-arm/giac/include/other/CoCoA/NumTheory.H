#ifndef CoCoA_NumTheory_H
#define CoCoA_NumTheory_H

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


#include "CoCoA/BigRat.H"
#include "CoCoA/factorization.H"

namespace CoCoA
{
  
//  class BigInt;     // fwd decl -- defined in BigInt.H
  class MachineInt; // fed decl -- defined in MachineInt.H

  // Frankly 8 separate cases seems a bit excessive!
  long PowerMod(const MachineInt& base, const MachineInt& exp, const MachineInt& modulus);
  long PowerMod(const MachineInt& base, const BigInt& exp, const MachineInt& modulus);
  long PowerMod(const BigInt& base, const MachineInt& exp, const MachineInt& modulus);
  long PowerMod(const BigInt& base, const BigInt& exp, const MachineInt& modulus);
  BigInt PowerMod(const MachineInt& base, const MachineInt& exp, const BigInt& modulus);
  BigInt PowerMod(const BigInt& base, const MachineInt& exp, const BigInt& modulus);
  BigInt PowerMod(const MachineInt& base, const BigInt& exp, const BigInt& modulus);
  BigInt PowerMod(const BigInt& base, const BigInt& exp, const BigInt& modulus);

  long gcd(const MachineInt& a, const MachineInt& b);
  const BigInt gcd(const BigInt& A, const MachineInt& b);
  const BigInt gcd(const MachineInt& a, const BigInt& B);
  const BigInt gcd(const BigInt& A, const BigInt& B);

  long ExtGcd(long& CofacA, long& CofacB, const MachineInt& a, const MachineInt& b);
//???? signature???  BigInt ExtGcd(BigInt& CoFacA, BigInt& CofacB, const MachineInt& A, const BigInt& B);
//???? signature???  BigInt ExtGcd(BigInt& CoFacA, BigInt& CofacB, const BigInt& A, const MachineInt& B);
  BigInt ExtGcd(BigInt& CoFacA, BigInt& CofacB, const BigInt& A, const BigInt& B);

  long InvMod(const MachineInt& r, const MachineInt& m);
  long InvMod(const BigInt& r, const MachineInt& m);
  BigInt InvMod(const MachineInt& r, const BigInt& m);
  BigInt InvMod(const BigInt& r, const BigInt& m);

  long lcm(const MachineInt& a, const MachineInt& b);
  const BigInt lcm(const BigInt& A, const MachineInt& b);
  const BigInt lcm(const MachineInt& a, const BigInt& B);
  const BigInt lcm(const BigInt& a, const BigInt& b);


  bool IsPrime(const MachineInt& n);
  bool IsPrime(const BigInt& N); // might be very slow!!
  bool IsProbPrime(const MachineInt& n); // probably not very useful
  bool IsProbPrime(const MachineInt& n, const MachineInt& NumIters); // probably not very useful
  bool IsProbPrime(const BigInt& N);
  bool IsProbPrime(const BigInt& N, const MachineInt& NumIters);

  long NextPrime(const MachineInt& n); ///< next prime number after n or 0 if there is none, must have n>0
  long PrevPrime(const MachineInt& n); ///< previous prime number before n or 0 if there is none, must have n>0

  // !!No NextPrime for BigInt!!  Use NextProbPrime and call IsPrime if you want a (costly) guarantee of primality.
  BigInt NextProbPrime(const BigInt& N); ///< next probable prime number after N, requires N > 1
  BigInt NextProbPrime(BigInt N, const MachineInt& NumIters); ///< next probable prime number after N, requires N > 1
  BigInt PrevProbPrime(const BigInt& N); ///< previous probable prime number before N, requires N > 1
  BigInt PrevProbPrime(BigInt N, const MachineInt& NumIters); ///< previous probable prime number before N, requires N > 1


  factorization<long> SmoothFactor(const MachineInt& N, const MachineInt& TrialLimit);
  factorization<BigInt>   SmoothFactor(const BigInt& N, const MachineInt& TrialLimit);
  factorization<BigInt>   SmoothFactor(const BigInt& N, const BigInt& TrialLimit);

  factorization<long> factor(const MachineInt& N);
  factorization<BigInt>   factor(const BigInt& N);

  long EulerPhi(const MachineInt& n);
  BigInt EulerPhi(const BigInt& N);

  long MultiplicativeOrderMod(const MachineInt& residue, const MachineInt& modulus);
  long MultiplicativeOrderMod(const BigInt& residue, const MachineInt& modulus);
  BigInt MultiplicativeOrderMod(const MachineInt& residue, const BigInt& modulus);
  BigInt MultiplicativeOrderMod(const BigInt& residue, const BigInt& modulus);
  int PrimitiveRoot(const MachineInt& p);
  int PrimitiveRoot(const BigInt& P);

  //////////////////////////////////////////////////////////////////////

  class ContFracIter
  {
  public:
    explicit ContFracIter(const BigRat& Q);
    const BigInt& operator*() const;
    ContFracIter& operator++();
    ContFracIter operator++(int);
    friend bool IsEnded(const ContFracIter& CFIter) { return IsZero(CFIter.myQuot) && IsZero(CFIter.myFrac); }
  private: // data members
    BigRat myFrac;
    BigInt myQuot;
  };

  class CFApproximantsIter
  {
  public:
    explicit CFApproximantsIter(const BigRat& Q);
    explicit CFApproximantsIter(const ContFracIter& CFIter);
    const BigRat& operator*() const { return myApproximant; }
    CFApproximantsIter& operator++();
    CFApproximantsIter operator++(int);
    friend bool IsEnded(const CFApproximantsIter& CFAIter) { return IsEnded(CFAIter.myCFIter); }
  private: // data members
    ContFracIter myCFIter;
    BigRat myApproximant;
    BigInt myPrevNum; // cannot use a BigRat here because initial value is 1/0
    BigInt myPrevDen;
  };

  std::ostream& operator<<(std::ostream& out, const ContFracIter& CFIter);
  std::ostream& operator<<(std::ostream& out, const CFApproximantsIter& CFAIter);

  BigRat CFApprox(const BigRat& q, const BigRat& MaxRelErr);


} // end of namespace CoCoA



// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/NumTheory.H,v 1.10 2012/03/16 15:40:12 abbott Exp $
// $Log: NumTheory.H,v $
// Revision 1.10  2012/03/16 15:40:12  abbott
// Merged contents of NumTheoryQQ (continued fraction functions) into NumTheory.
// Merged the doc too.
//
// Revision 1.9  2011/11/09 13:47:56  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.8  2011/08/14 15:52:18  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.7  2011/03/23 21:00:46  abbott
// Removed FindPrimRoot from NumTheory.H because it was already
// available as PrimitiveRoot (a better name).
// Updated documentation for NumTheory.
//
// Revision 1.6  2011/03/22 20:17:18  abbott
// Added fn FindPrimRoot.
// Merged impls from obsolescent SmallPrime.C.
//
// Revision 1.5  2011/03/16 13:26:36  abbott
// Removed all "unsigned" from fn interfaces, and many unsigned from inside fn impls.
//
// Revision 1.4  2010/03/03 10:43:34  abbott
// Added PrimitiveRoot for big primes (might be very slow).
// Added MultiplicativeOrderMod (currently very SLUGGY implementation).
//
// Revision 1.3  2009/12/29 22:44:32  abbott
// Removed buggy proxy class ZZ::rtn.
// Consequent changes for function prototypes also in NumTheory.
// Corrected some minor buglets in NumTheory.
//
// Revision 1.2  2009/07/02 16:28:10  abbott
// Fairly extensive change to NumTheory (at least internally and philosophically).
// Improved and cleaned NumTheory.  Added documentation.
// Clarified the exact behaviour of most functions.
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
