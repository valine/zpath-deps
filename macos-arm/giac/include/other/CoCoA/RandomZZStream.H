#ifndef CoCoA_RandomBigIntStream_H
#define CoCoA_RandomBigIntStream_H

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


#include "CoCoA/MachineInt.H"
#include "CoCoA/BigInt.H"

#include <iosfwd>
//using std::ostream;
#include "gmp.h"

namespace CoCoA
{

  class RandomBigIntStream
  {
  public:
    RandomBigIntStream(const MachineInt& lwb, const MachineInt& upb, const MachineInt& seed = 0);
    RandomBigIntStream(const MachineInt& lwb, const BigInt& upb, const MachineInt& seed = 0);
    RandomBigIntStream(const BigInt& lwb, const MachineInt& upb, const MachineInt& seed = 0);
    RandomBigIntStream(const BigInt& lwb, const BigInt& upb, const MachineInt& seed = 0);
    RandomBigIntStream(const RandomBigIntStream& copy);
    RandomBigIntStream& operator=(const RandomBigIntStream& rhs);
    ~RandomBigIntStream();
    const BigInt& operator*() const;
    RandomBigIntStream& operator++();
    RandomBigIntStream operator++(int);
    long myIndex() const;
  private:
    void myGenValue(); // fills myValue with a newly generated random value.
  private: // data members
    BigInt myLwb;   // morally const, changed only by assignment
    BigInt myUpb;   // morally const, changed only by assignment
    BigInt myRange; // morally const, changed only by assignment
    BigInt myValue;
    long myCounter;
    unsigned long mySeed;
    gmp_randstate_t myState;
    friend std::ostream& operator<<(std::ostream& out, const RandomBigIntStream& RLS);
  };

  const BigInt& sample(RandomBigIntStream& RLS);
  std::ostream& operator<<(std::ostream& out, const RandomBigIntStream& RLS);

  //---------------------------------------------------------------------------
  // Inline functions.

  inline const BigInt& RandomBigIntStream::operator*() const
  {
    return myValue;
  }


  inline RandomBigIntStream& RandomBigIntStream::operator++()
  {
    ++myCounter;
    myGenValue();
    return *this;
  }


  inline const BigInt& sample(RandomBigIntStream& RLS)
  {
    return *++RLS; // advance then get value
  }

} // end of namespace CoCoA



// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/RandomZZStream.H,v 1.5 2011/11/09 13:50:01 bigatti Exp $
// $Log: RandomZZStream.H,v $
// Revision 1.5  2011/11/09 13:50:01  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.4  2011/08/14 15:52:18  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.3  2011/05/03 09:45:12  abbott
// Changed default seed to 0 (used to be 1).
// Seeding with 0 no longer means "seed from system time".
//
// Revision 1.2  2011/03/14 10:26:22  abbott
// Changed size_t into long.
//
// Revision 1.1  2010/06/29 15:17:02  abbott
// New class RandomZZStream
//
//

#endif
