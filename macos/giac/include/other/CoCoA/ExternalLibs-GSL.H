#ifndef CoCoA_gsl_H
#define CoCoA_gsl_H

#ifdef CoCoA_WITH_GSL

//   Copyright (c)  2011  Bruno Simoes

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

#include <vector>
#include <gsl/gsl_math.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_permute_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_errno.h>

#include "CoCoA/library.H"

namespace CoCoA
{

  matrix NewMatrix(const ring& R, gsl_matrix* m);
  matrix NewMatrix(const ring& R, gsl_matrix* m, bool transpose);
  
  matrix NewMatrix(const ring& R, gsl_vector* m);
  gsl_matrix* NewMatrixGSL(ConstMatrixView M);
  gsl_matrix* NewMatrixGSL(matrix& M);
  void UpdateMatrix(matrix& A, gsl_matrix* m);
  
  std::vector<RingElem> NewVector(const ring& R, gsl_vector* m);
  gsl_vector* NewVectorGSL(std::vector<RingElem>& v);

  // Print tools
  void PrintVector(gsl_vector *m);
  void PrintMatrix(gsl_matrix *m);
  
  // SVD
  std::vector<matrix> SVD(ConstMatrixView A);
  std::vector<RingElem> SingularValues(ConstMatrixView A);
  std::vector<RingElem> SolveSVD(ConstMatrixView A, std::vector<RingElem>& b);
  
  // LU
  matrix LU(ConstMatrixView A);
  std::vector<RingElem> SolverLU(ConstMatrixView A, std::vector<RingElem>& b);
  
  // Cholesky Decomposition
  matrix CholeskyDecomposition(ConstMatrixView A);

  // QR
  std::vector<matrix> QR(ConstMatrixView A);
  std::vector<matrix> QRPT(ConstMatrixView A);
  std::vector<RingElem> SolverQR(ConstMatrixView A, std::vector<RingElem>& b);

  void QRDecomposition(ConstMatrixView A, matrix& qr, std::vector<RingElem>& tau);
    
  // B-Decomp
  void BidiagDecomposition(ConstMatrixView A, matrix& D, std::vector<RingElem>& tau_U, std::vector<RingElem>& tau_V);
  void BidiagDecompUnpack(ConstMatrixView A, matrix& U, matrix& V, std::vector<RingElem>& diagonal, std::vector<RingElem>& superdiagonal);
  
}
#endif

// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/ExternalLibs-GSL.H,v 1.4 2011/04/27 09:41:04 bigatti Exp $
// $Log: ExternalLibs-GSL.H,v $
// Revision 1.4  2011/04/27 09:41:04  bigatti
// -- minor reshape
//

#endif
