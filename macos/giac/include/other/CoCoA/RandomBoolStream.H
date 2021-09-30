#ifndef CoCoA_RandomBoolStream_H
#define CoCoA_RandomBoolStream_H

//   Copyright (c)  2006,2007,2010,2011  John Abbott

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
#include <bitset>
//using std::bitset;
#include "gmp.h"

namespace CoCoA
{

  class RandomBoolStream
  {
  public:
    explicit RandomBoolStream(const MachineInt& seed = 0);
    RandomBoolStream(const RandomBoolStream& copy);
    RandomBoolStream& operator=(const RandomBoolStream& rhs);
    ~RandomBoolStream();
    bool operator*() const;
    RandomBoolStream& operator++();
    RandomBoolStream operator++(int);
    long myIndex() const;
  private:
    static const int ourBufferBits = std::numeric_limits<unsigned long>::digits;
    void myFillBuffer(); // fills myBuffer and resets myBitIndex to 0
  private: // data members
    int myBitIndex;
    std::bitset<ourBufferBits> myBuffer;
    long myCounter;
    unsigned long mySeed;
    gmp_randstate_t myState;

    friend std::ostream& operator<<(std::ostream& out, const RandomBoolStream& RBS);
  };

  bool sample(RandomBoolStream& RBS);
  bool prob(double P, RandomBoolStream& RBS); // returns true with probability P
  std::ostream& operator<<(std::ostream& out, const RandomBoolStream& RBS);

  //---------------------------------------------------------------------------
  // Inline functions.

  inline bool RandomBoolStream::operator*() const
  {
    return myBuffer[myBitIndex];
  }


  inline RandomBoolStream& RandomBoolStream::operator++()
  {
    ++myCounter;
    if (++myBitIndex >= ourBufferBits)
      myFillBuffer();
    return *this;
  }


  inline bool sample(RandomBoolStream& RBS)
  {
    return *++RBS; // advance then get value
  }

} // end of namespace CoCoA



// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/RandomBoolStream.H,v 1.2 2011/11/09 13:47:56 bigatti Exp $
// $Log: RandomBoolStream.H,v $
// Revision 1.2  2011/11/09 13:47:56  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.1  2011/05/03 09:37:08  abbott
// Renamed RandomBitStream into RandomBoolStream.
//
// Revision 1.5  2011/03/14 10:26:22  abbott
// Changed size_t into long.
//
// Revision 1.4  2010/02/16 10:20:58  abbott
// Added new fn sample; SampleBool & SampleLong are obsolescent.
//
// Revision 1.3  2010/02/01 22:41:02  abbott
// Removed myMPZ data field which is no longer needed.
// Changed a couple of calls to GMP, after having found
// ones which do directly what I need.
//
// Revision 1.2  2007/10/30 17:14:12  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.1  2007/06/06 15:16:48  abbott
// Added new RandomBoolStream class (now based upon GMP's random generator).
// Consequential changes to Makefiles, etc.  There's even doc and an example!
//
// Revision 1.1.1.1  2007/03/09 15:16:11  abbott
// Imported files
//
// Revision 1.5  2006/12/06 17:18:40  cocoa
// -- removed #include "config.H"
//
// Revision 1.4  2006/11/27 14:19:30  cocoa
// -- added #include <cstddef> //using std::size_t;
//
// Revision 1.3  2006/10/27 19:01:17  cocoa
// Corrected a spelling mistake: Steam has become Stream :-)
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
// Revision 1.2  2006/04/27 13:45:30  cocoa
// Changed name of NewIdentityRingHom to NewIdentityHom.
// Changed name of member functions which print out their own object
// into myOutputSelf (to distinguish from "transitive" myOutput fns).
//
// Revision 1.1  2006/04/14 13:51:40  cocoa
// Added a class for generating random bits (RandomBoolStream in the file random.H).
//

#endif
