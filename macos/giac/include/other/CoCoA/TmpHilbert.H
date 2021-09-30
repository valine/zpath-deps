#ifndef CoCoA_hilbert_H
#define CoCoA_hilbert_H

//   Copyright (c)  2006  Anna Bigatti

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


namespace CoCoA
{

  class RingElem;     // forward declaration -- defined in ring.H
  class PolyRing;     // forward declaration -- defined in PolyRing.H
  class DenseUPolyRing; // forward declaration -- defined in DenseUPolyRing.H
  class ideal;        // forward declaration -- defined in ideal.H

  RingElem HilbertNumQuot_C(const PolyRing& HSRing, ideal I);
  RingElem HilbertNumQuot(ideal I);
  RingElem MGHilbertNumQuot(const SparsePolyRing& HSRing, ideal I);
  void EndPoincare_C(); // just for mempool complaints on global unipoly array

} // end of namespace CoCoA


// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/TmpHilbert.H,v 1.6 2011/04/26 10:13:04 bigatti Exp $
// $Log: TmpHilbert.H,v $
// Revision 1.6  2011/04/26 10:13:04  bigatti
// -- added MGHilbertNumQuot
//
// Revision 1.5  2011/04/08 14:04:46  bigatti
// -- renamed HilbertNumeratorMod into HilbertNumQuot
//
// Revision 1.4  2010/10/29 11:59:12  bigatti
// -- added function for cleaning memory after using C global
//
// Revision 1.3  2007/10/30 17:14:11  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.2  2007/10/10 14:36:34  bigatti
// new: TmpHilbertDir/TmpPoincareCPP.[CH]: poincare code using
// 	C++ univariate polynomials (DenseUPolyRing)
//
// Revision 1.1.1.1  2007/03/09 15:16:11  abbott
// Imported files
//
// Revision 1.1  2007/01/17 17:38:11  bigatti
// -- moved all cocoa-4 code for hilbert into src/TmpHilbertDir
//
// Revision 1.3  2006/12/06 17:11:16  cocoa
// -- removed #include "config.H"
//
// Revision 1.2  2006/11/24 17:43:37  cocoa
// -- reorganized includes of header files
//
// Revision 1.1  2006/10/09 16:48:58  cocoa
// -- first import
//

#endif
