#ifndef CoCoA_normaliz_H
#define CoCoA_normaliz_H

#ifdef CoCoA_WITH_NORMALIZ

//   Copyright (c)  2010 Anna M. Bigatti, Christof Soeger

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


#include "libnormaliz/cone.h" // libnormaliz
#include "CoCoA/SmartPtrIRC.H"

#include <vector>
// using std::vector;

namespace CoCoA
{
  class BigInt;          // forward declaration -- defined in BigInt.H 
  class ConstMatrixView; // forward declaration -- defined in matrix.H
  class PPVector;        // forward declaration -- defined in TmpPPVector.H 

namespace Normaliz
{
  class ConeBase; // fwd decl for SmartPtrIRC
  class cone
  {
  public:
    explicit cone(const ConeBase* ptr): mySmartPtr(ptr) {}
    // Default copy ctor works fine.
    // Assignment disabled because SmartPtrIRC has no assignment.
    const ConeBase* operator->() const { return mySmartPtr.operator->(); }  ///< Allow const member fns to be called.
    //    const ConeBase* myRawPtr() const { return mySmartPtr.myRawPtr(); } ///< Used by "downcasting" functions
  private: // data members
    SmartPtrIRC<const ConeBase> mySmartPtr;
  };

  class ConeBase: protected IntrusiveReferenceCount   // abstract class
  {
    friend class SmartPtrIRC<const ConeBase>; // Morally "friend Cone", so it can alter reference count.

  public:
    ConeBase() {}
    virtual ~ConeBase() {}
    //    friend void HilbertBasis(PPVector& v, /*const?*/ ConeBase& c);
    friend std::vector<std::vector<BigInt> > HilbertBasis(const cone& c);
    friend void Ht1Elements(std::vector<std::vector<BigInt> >& v, const cone& c);
    friend void SupportHyperplanes(std::vector<std::vector<BigInt> >& v, const cone& c);
    friend void HVector(std::vector<BigInt>& v, const cone& c);
    //    friend void Triangulation(std::vector<std::vector<BigInt> >& v, const cone& c);

  private:
    virtual void myComputation(libnormaliz::ConeProperty::Enum CP) const =0;
    virtual void myComputation(const libnormaliz::ConeProperties& CPs) const =0;
    virtual void myHilbertBasis(std::vector<std::vector<BigInt> >& v) const =0;
    virtual void myHt1Elements(std::vector<std::vector<BigInt> >& v) const =0;
    virtual void mySupportHyperplanes(std::vector<std::vector<BigInt> >& v) const =0;
    virtual void myHVector(std::vector<BigInt>& v) const =0;
    //    virtual void myTriangulation(std::vector<std::vector<BigInt> >& v) const =0;
  };

  cone NewConeLong(const std::vector<std::vector<BigInt> >& v, libnormaliz::Type::InputType InputType);
  cone NewConeBigInt(const std::vector<std::vector<BigInt> >& v, libnormaliz::Type::InputType InputType);
  cone NewConeLong(ConstMatrixView M, libnormaliz::Type::InputType InputType);
  cone NewConeBigInt(ConstMatrixView M, libnormaliz::Type::InputType InputType);

  std::vector<std::vector<BigInt> > HilbertBasis(const cone& c);
  void Ht1Elements(std::vector<std::vector<BigInt> >& v, const cone& c);
  void SupportHyperplanes(std::vector<std::vector<BigInt> >& v, const cone& c);
  void HVector(std::vector<BigInt>& v, const cone& c);
  //  void TriangulationNormaliz(std::vector<std::vector<BigInt> >& v, const cone& c);

  PPVector NormalToricRing(const PPVector& ppv);
  
} // end of namespace Normaliz
} // end of namespace CoCoA


// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/ExternalLibs-Normaliz.H,v 1.9 2011/11/07 11:09:32 bigatti Exp $
// $Log: ExternalLibs-Normaliz.H,v $
// Revision 1.9  2011/11/07 11:09:32  bigatti
// -- new ctors taking ConstRefRingElem
// -- added PPVector NormalToricRing(const PPVector& ppv)
// -- removed void HilbertBasis(std::vector<std::vector<BigInt> >& v, const cone& c)
//
// Revision 1.8  2011/10/04 13:03:02  bigatti
// -- new logo for gui
//
// Revision 1.7  2011/09/30 12:55:44  bigatti
// -- introduced namespace "Normaliz" and removed Normaliz from function names
// -- input of Normaliz functions in CoCoA-5 is now a matrix instead of
//    vector<vector<BigInt>>
//
// Revision 1.6  2011/08/14 15:52:18  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.5  2011/07/20 15:33:05  bigatti
// -- changed NORMALIZ_DIR to have no "libnormaliz/"
//
// Revision 1.4  2011/07/20 13:49:37  bigatti
// -- added "Normaliz" postfix to Normaliz function calls
//
// Revision 1.3  2011/07/20 12:45:12  bigatti
// -- new normaliz interface (not yet public)
//
// Revision 1.2  2011/02/17 16:50:04  bigatti
// -- getting ready for new official veson on Normaliz: added HVector, removed Triangulation
//
// Revision 1.1  2010/11/05 14:27:18  bigatti
// -- was TmpNormaliz**
//
// Revision 1.5  2010/10/12 11:22:54  bigatti
// -- TmpNormaliz.H simplified:
//    now cone is a smart pointer to ConeBase
//    and the concrete classes are entirely in the .C file
// -- added Ht1Elements, SupportHyperplanes, Triangulation
// -- added some text in ex-Normaliz1 and 2
//
// Revision 1.4  2010/10/08 16:34:08  bigatti
// -- activated ConeMPZ
//
// Revision 1.3  2010/10/08 10:39:32  bigatti
// -- extended interface for normaliz
//

#endif // CoCoA_WITH_NORMALIZ
#endif
