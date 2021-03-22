#ifndef CoCoA_RandomSource_H
#define CoCoA_RandomSource_H

//   Copyright (c)  2010  John Abbott

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

#include "CoCoA/BigInt.H"

#include "gmp.h"
#include <iosfwd>
//using std::ostream;

namespace CoCoA
{
  class MachineInt; // fwd decl -- defined in MachineInt.H

  class RandomSource
  {
  public:
    explicit RandomSource(const MachineInt& seed);
    explicit RandomSource(const BigInt& seed = BigInt(0));
    RandomSource(const RandomSource& copy);
    RandomSource& operator=(const RandomSource& rhs);
    ~RandomSource();
    friend bool RandomBool(RandomSource& RndSrc);
    //    friend long RandomLong(RandomSource& RndSrc);
    friend long RandomLong(RandomSource& RndSrc, const MachineInt& lwb, const MachineInt& upb);
    friend BigInt RandomBigInt(RandomSource& RndSrc, const MachineInt& lwb, const MachineInt& upb);
    friend BigInt RandomBigInt(RandomSource& RndSrc, const MachineInt& lwb, const BigInt& upb);
    friend BigInt RandomBigInt(RandomSource& RndSrc, const BigInt& lwb, const MachineInt& upb);
    friend BigInt RandomBigInt(RandomSource& RndSrc, const BigInt& lwb, const BigInt& upb);
//    friend BigInt RandomBigIntmod(RandomSource& RndSrc, const BigInt& M);  // range is 0..M-1
    friend void reseed(RandomSource& RndSrc, const MachineInt& seed);
    friend void reseed(RandomSource& RndSrc, const BigInt& seed);
    friend std::ostream& operator<<(std::ostream& out, const RandomSource& RndSrc);
  private:  // data members
    BigInt mySeed;
    gmp_randstate_t myState;
//     long myBoolCounter;
//     long myLongCounter;
//     long myBigIntCounter;
  };


  inline bool RandomBool(RandomSource& RndSrc)
  {
    return gmp_urandomb_ui(RndSrc.myState, 1) == 1;
  }

  // using GlobalRandomSource()
  bool   RandomBool();
  long   RandomLong(const MachineInt& lwb, const MachineInt& upb);
  BigInt RandomBigInt(const MachineInt& lwb, const MachineInt& upb);
  BigInt RandomBigInt(const MachineInt& lwb, const BigInt& upb);
  BigInt RandomBigInt(const BigInt& lwb, const MachineInt& upb);
  BigInt RandomBigInt(const BigInt& lwb, const BigInt& upb);

} // end of namespace CoCoA



// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/RandomSource.H,v 1.7 2012/02/03 10:18:46 bigatti Exp $
// $Log: RandomSource.H,v $
// Revision 1.7  2012/02/03 10:18:46  bigatti
// -- added random functions with implicit use of GlobalRandomSource()
//
// Revision 1.6  2012/02/02 15:57:39  abbott
// Relpaced include of MachineInt by fwd decl.
// Renamed some formal parameters.
// Moved default value for ctor arg (consequence of MachineInt no longer fully defined)
//
// Revision 1.5  2011/11/09 13:50:01  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.4  2011/08/14 15:52:18  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.3  2011/05/03 09:52:50  abbott
// Changed default initial seed to 0 (was previsouly 1).
// Added reseeding functions.
// Seeding from a ZZ is now possible.
//
// Revision 1.2  2011/03/14 10:26:22  abbott
// Changed size_t into long.
//
// Revision 1.1  2010/12/17 16:03:15  abbott
// Added new class RandomSource.
//
//

#endif
