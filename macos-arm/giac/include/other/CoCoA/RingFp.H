#ifndef CoCoA_RingFp_H
#define CoCoA_RingFp_H

//   Copyright (c)  2001-2009,2011  John Abbott

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


#include "CoCoA/GlobalManager.H"

namespace CoCoA
{

  class BigInt;       // fwd decl -- defined in BigInt.H
  class MachineInt;   // fwd decl -- defined in MachineInt.H
  class QuotientRing; // fwd decl -- defined in QuotientRing.H
  class ideal;        // fwd decl -- defined in ring.H
  class ring;         // fwd decl -- defined in ring.H

  QuotientRing NewRingFp(const MachineInt& p, GlobalSettings::ResidueSetting choice = DefaultResidueSetting());
  QuotientRing NewRingFp(const BigInt& P);
  QuotientRing NewRingFp(const ideal& I);

  bool IsGoodForRingFp(const MachineInt& p);
  bool IsGoodForRingFp(const BigInt& P);
  bool IsGoodForRingFp(const ideal& I);

  bool IsRingFp(const ring& R); ///< DO NOT USE this function unless you really know what you're doing!

} // end of namespace CoCoA



// RCS header/log
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/RingFp.H,v 1.8 2011/11/09 13:50:01 bigatti Exp $
// $Log: RingFp.H,v $
// Revision 1.8  2011/11/09 13:50:01  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.7  2011/08/14 15:52:17  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.6  2011/05/19 14:38:27  abbott
// Updated small prime finite field impls to allow user to specify
// separately for each whether to use symmetric or non-negative
// residues for export operations (myExport and printing).
//
// Revision 1.5  2011/03/22 20:00:38  abbott
// Added IsGoodForXXX fns to test whether a given arg is suitable as
// characteristic for the given type of small prime finite field.
//
// Revision 1.4  2009/09/24 16:21:13  abbott
// Replaced include directive by forward declarations.
//
// Revision 1.3  2008/12/17 12:11:52  abbott
// Changed type from long to MachineInt in operations which use a machine integer
// in place of a RingElem.  The change is "superficial" but affects many files.
//
// Revision 1.2  2007/10/30 17:14:12  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.1.1.1  2007/03/09 15:16:11  abbott
// Imported files
//
// Revision 1.5  2007/03/02 10:47:53  cocoa
// First stage of RingZ modifications -- tests do not compile currently, Anna will fix this.
//
// Revision 1.4  2006/12/06 17:21:56  cocoa
// -- removed #include "config.H"
//
// Revision 1.3  2006/10/06 10:15:53  cocoa
// In response to Susan's bug: a fiasco when compiling with CoCoA_MEMPOOL_DEBUG
// set wrongly.  Moved several implementation classes out of their header files
// into the implementation files.  Several functions had to be uninlined.
// Also corrected position of #include, etc.
//
// Revision 1.2  2006/08/07 21:23:25  cocoa
// Removed almost all publicly visible references to SmallExponent_t;
// changed to long in all PPMonoid functions and SparsePolyRing functions.
// DivMask remains to sorted out.
//
// Revision 1.1.1.1  2006/05/30 11:39:37  cocoa
// Imported files
//
// Revision 1.7  2006/05/29 16:22:37  cocoa
// Third time lucky???
// Added myIsInteger member function to all rings (NYI for RingFloat).
//
// Revision 1.6  2006/05/12 16:10:58  cocoa
// Added OpenMathFwd.H, and tidied OpenMath.H.
// Many consequential but trivial changes.
//
// Revision 1.5  2006/04/21 15:01:36  cocoa
// Changed default implementation of RingBase::myGcd -- it now gives a SERIOUS
// error.  All fields must now handle a call to gcd explicitly: they can use
// the new myGcdInField function.  It's now cleaner than it was.
//
// Revision 1.4  2006/03/15 18:09:31  cocoa
// Changed names of member functions which print out their object
// into myOutputSelf -- hope this will appease the Intel C++ compiler.
//
// Revision 1.3  2006/03/14 15:01:49  cocoa
// Improved the implementation of ring member fns for computing powers.
// Should keep Intel C++ compiler quieter too.
//
// Revision 1.2  2006/03/12 21:28:34  cocoa
// Major check in after many changes
//
// Revision 1.1.1.1  2005/10/17 10:46:54  cocoa
// Imported files
//
// Revision 1.3  2005/10/14 15:25:07  cocoa
// Major tidying and cleaning to small prime finite fields.
// Several consequential changes.  Improved their documentation.
//
// Added Makefile and script to include/CoCoA/ directory to
// keep library.H up to date.
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
// Revision 1.1.1.1  2005/05/03 15:47:30  cocoa
// Imported files
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
// Revision 1.18  2004/11/18 18:33:41  cocoa
// Now every ring know its own "one" element (as well as "zero").
// Several consequential changes.
//
// Revision 1.17  2004/11/11 13:04:30  cocoa
// -- added \include *.txt for doxygen
//
// Revision 1.16  2004/11/05 15:34:33  cocoa
// Consequential change following from the renaming of
// FieldIdealImpl and the introduction of the new pseudo-ctor.
//
// Revision 1.15  2004/11/04 18:47:43  cocoa
// (1) Ring member functions which previously expected mpz_t args
//     now expect ZZ args.  Numerous minor consequential changes.
// (2) Renamed function which gives access to the mpz_t value inside
//     a ZZ object: previously was raw(...), now is mpzref(...).
//     Plenty of calls had to be altered.
//
// Revision 1.14  2004/07/27 16:03:39  cocoa
// Added IsCommutative test and IamCommutative member function
// to all rings.  Tidied geobuckets a little.
//
// Revision 1.13  2004/07/16 15:45:12  cocoa
// First stage of new RingElem implementation completed.
//
// Revision 1.12  2004/07/14 16:40:42  cocoa
// Separated RingFpLog from its implementation which now resides in
// a new class: SmallFpLogImpl.  This is analogous to the change made
// to RingFp yesterday.
//
// Some tidying and other sundry minor changes.
//
// Revision 1.11  2004/07/13 16:32:26  cocoa
// First stage of major revamp of ring elements.
// Implementation of RingFp has been split into "ring interface"
// and "algorithms plus data structures".
//
// Revision 1.10  2004/05/24 15:52:13  cocoa
// Major update:
//   new error mechanism
//   many fixes
//   RingHoms almost work now
//   RingFloat much improved
//
// Revision 1.9  2004/04/08 15:33:34  cocoa
// Added function IsInteger, and the related RingBase::myIsInteger
// virtual function, plus all necessary implementations.
//
// Revision 1.8  2004/03/20 17:46:10  cocoa
// Check in prior to departure to RWCA
//
// Revision 1.7  2004/02/03 16:16:20  cocoa
// Removed pointless IamGCDDomain functions from several concrete rings.
// Added IamOrderedDomain functions where appropriate.
// Tidied ctors for the small finite fields.
//
// Revision 1.6  2004/01/30 14:07:10  cocoa
// Tidied RingRawValue union: now it contains just two fields,
// and has no need of forward declarations of types used internally
// by the concrete rings -- it uses explicitly a void* instead.
//
// I have tidied the "import" functions used by most concrete rings.
//
// I have moved the choice of representation type for RingFp and RingFpLog
// into a typedef in config.H -- this is to recognise that different
// choices may work best on different platforms.
//
// Revision 1.5  2003/11/14 13:06:05  cocoa
// -- New function "myIsPrintAtom" for printing polynomials and fractions
//
// Revision 1.4  2003/10/17 10:51:06  cocoa
// Major cleaning, and new naming convention.
//
// Revision 1.3  2003/10/09 14:55:19  cocoa
// - minor debugging after merge
//
// Revision 1.2  2003/10/09 12:15:45  cocoa
// New coding convention for rings.
//
// Revision 1.19  2003/06/23 16:53:23  abbott
// Minor cleaning prior to public release.
// Just a name change to following coding conventions.
//
// Revision 1.18  2003/04/24 16:11:24  abbott
// Made exgcd a static member function so it could "see" the private type
// ring_Fp::FpElem (previously it had been public).
//
// Revision 1.17  2003/04/23 10:05:45  abbott
// Predominantly some minor tidying:
//  * typedef for FpElem is now private (it is an implementation detail)
//  * disabled copy ctor and assignment for ring_Fp
//  * ctor for ring_Fp::hom now expects a QuotientRing (instead of ring)
//  * added commented out code to allow use of doubles in ring_Fp::mul
//
// Revision 1.16  2003/04/17 16:50:19  abbott
// Numerous changes:
//  * added mem fns ring_Fp::IsOne, IsMinusOne, init and assign from ZZ
//    (needed by RingBase)
//  * ring_Fp now derived from QuotientRingBase
//  * constructor for ring_Fp is now compatible with NewQuotientRing
//  * added mem fns ring_Fp::CanonRepr and ReduceModI (needed by QuotientRingBase)
//  * added mem fns ring_Fp::NewIdeal and ReduceMod (needed by RingBase to
//    handle ideals)
//  * added mem fns ring_Fp::compose and MakeInducedHom (needed by RingBase
//    and QuotientRingBase to handle homomorphisms).
//  * added ring_Fp::hom class to represent homomorphisms
//  * no need for a class to handle ideals as FieldIdeal does that already.
//
// Revision 1.15  2002/11/14 18:05:05  abbott
// Revised in line with the renaming in ring.H.
//
// Revision 1.14  2002/07/05 15:22:24  abbott
// Added member function IsDivisible.
//
// Revision 1.13  2002/06/28 14:48:28  abbott
// Now the zero element is pointed by an auto_ptr (to be consistent with
// other rings).  The member typedef "elem" is now called "FpElem".
//
// Revision 1.12  2002/06/27 16:09:34  abbott
// Added declaration for the specialized definition of the
// member function "power", previously the default definition
// (sequential powering) was inherited.
//
// Revision 1.11  2002/06/22 17:08:54  abbott
// Changed name of "equal" member function to "IsEqual" (as per new ring.H).
//
// Revision 1.10  2002/05/19 17:39:29  abbott
// Added IsField and zero member functions.
//
// Revision 1.9  2002/05/15 15:00:36  abbott
// Updated the "virtual" interface to agree with the revised ring.H.
// Tidied layout.
// Altered data member name (now accords with coding conventions).
//
// Revision 1.8  2002/02/08 11:13:43  bigatti
// - changed syntax to IsZeroAddMul
//
// Revision 1.7  2002/01/30 15:13:47  abbott
// Constructor now takes an unsigned long (previously unsigned int).
// Added the IsZeroAddMul function required by new ring.H.
//
// Revision 1.6  2001/12/07 18:23:13  abbott
// Changed names in accordance with the new cpding conventions.
//
// Revision 1.5  2001/11/23 20:57:25  abbott
// Added assignment from a long (member of ring_Fp).
//
// Revision 1.4  2001/11/16 18:52:13  bigatti
// added: std::
// for compatibility with gcc-3
//
// Revision 1.3  2001/11/07 20:56:01  abbott
// The change of ring::raw_elem to a union (from a void*) permits "inline"
// small finite field coefficients.  In turn, this obviates the need for
// a MemPool which has been removed.
//
// Revision 1.2  2001/10/29 20:39:41  abbott
// Some minor friend declarations to permit compilation.
// Added a MemPool to manage the storage used by the finite field values.
// Once again the question of whether to put the values in directly
// rather than use pointers arises -- related to the void*/union question
// for ring::raw_elem values.
//
// Revision 1.1  2001/10/05 12:55:32  abbott
// Initial revision
//

#endif
