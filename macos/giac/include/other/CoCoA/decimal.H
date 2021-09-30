#ifndef CoCoA_decimal_H
#define CoCoA_decimal_H

//   Copyright (c)  2011  John Abbott

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
#include "CoCoA/MachineInt.H"

#include <iosfwd>
//using std::ostream;
#include <string>

namespace CoCoA
{

  class BigRat; // fwd decl -- defined in BigRat.H

  class MantExp
  {
  public:
    MantExp(int s, long e, const BigInt& m): mySign(s), myExponent(e), myMantissa(m) {}
    int mySign;
    long myExponent;
    BigInt myMantissa;

    static const int ourDefaultSigFig; // actual value is in decimal.C
  };

  std::ostream& operator<<(std::ostream& out, const MantExp& ME);

  MantExp MantissaAndExponent(const BigInt& N, const MachineInt& SigFig = MantExp::ourDefaultSigFig);
  MantExp MantissaAndExponent(const BigRat& N, const MachineInt& SigFig = MantExp::ourDefaultSigFig);

  std::string FloatStr(const BigInt& N, const MachineInt& SigFig = MantExp::ourDefaultSigFig);
  std::string FloatStr(const BigRat& q, const MachineInt& SigFig = MantExp::ourDefaultSigFig);

  std::string DecimalStr(const BigInt& N, const MachineInt& SigFig = MantExp::ourDefaultSigFig);
  std::string DecimalStr(const BigRat& q, const MachineInt& SigFig = MantExp::ourDefaultSigFig);

} // end of namespace CoCoA



// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/decimal.H,v 1.8 2012/02/02 15:58:40 abbott Exp $
// $Log: decimal.H,v $
// Revision 1.8  2012/02/02 15:58:40  abbott
// Added include of MachineInt.
//
// Revision 1.7  2012/01/26 16:57:42  abbott
// Moved value of ourDefaultSigFig from H file to C file
// (this allows clean compilation on MSVC, also avoids
// excessive recompilation if we change the value).
//
// Revision 1.6  2011/11/09 13:51:29  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.5  2011/08/24 10:22:45  bigatti
// -- renamed QQ --> BigRat
//
// Revision 1.4  2011/08/14 15:52:17  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.3  2011/08/03 09:05:05  abbott
// Added new fn DecimalStr.
//
// Revision 1.2  2011/08/02 13:28:46  abbott
// Cleaned up impl.  Now MantissaAndExponent has default SigFig too.
// Used naming convention for members of MantExp.
//
// Revision 1.1  2011/03/01 15:21:22  abbott
// Added new functions: MantissaAndExponent, FloatStr (in CoCoALib).
//
//

#endif
