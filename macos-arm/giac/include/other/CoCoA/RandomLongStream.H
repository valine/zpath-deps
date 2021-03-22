#ifndef CoCoA_RandomLongStream_H
#define CoCoA_RandomLongStream_H

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

#include <iosfwd>
//using std::ostream;
#include "gmp.h"

namespace CoCoA
{

  class RandomLongStream
  {
  public:
    RandomLongStream(const MachineInt& lwb, const MachineInt& upb, const MachineInt& seed = 0);
    RandomLongStream(const RandomLongStream& copy);
    RandomLongStream& operator=(const RandomLongStream& rhs);
    ~RandomLongStream();
    long operator*() const;
    RandomLongStream& operator++();
    RandomLongStream operator++(int);
    long myIndex() const;
  private:
    void myGenValue(); // fills myValue with a newly generated random value.
  private: // data members
    long myLwb;
    long myUpb;
    unsigned long myRange;
    long myValue;
    long myCounter;
    unsigned long mySeed;
    gmp_randstate_t myState;
    friend std::ostream& operator<<(std::ostream& out, const RandomLongStream& RLS);
  };

  long sample(RandomLongStream& RLS);
  std::ostream& operator<<(std::ostream& out, const RandomLongStream& RLS);

  //---------------------------------------------------------------------------
  // Inline functions.

  inline long RandomLongStream::operator*() const
  {
    return myValue;
  }


  inline RandomLongStream& RandomLongStream::operator++()
  {
    ++myCounter;
    myGenValue();
    return *this;
  }


  inline long sample(RandomLongStream& RLS)
  {
    return *++RLS; // advance then get value
  }

} // end of namespace CoCoA



// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/RandomLongStream.H,v 1.4 2011/11/09 13:47:56 bigatti Exp $
// $Log: RandomLongStream.H,v $
// Revision 1.4  2011/11/09 13:47:56  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.3  2011/05/03 09:46:42  abbott
// Changed default seed to 0 (used to be 1).
// Seeding with 0 no longer means "seed from system time".
//
// Revision 1.2  2011/03/14 10:26:22  abbott
// Changed size_t into long.
//
// Revision 1.1  2010/02/16 10:19:29  abbott
// Added new class RandomLongStream with example and test.
//
//

#endif
