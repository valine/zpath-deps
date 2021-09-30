#ifndef CoCoA_ring_H
#define CoCoA_ring_H

//   Copyright (c)  2005-2011  John Abbott

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
#include "CoCoA/SmartPtrIRC.H"
#include "CoCoA/assert.H"

#include <iosfwd>
// using std::ostream;
#include <vector>
// using std::vector;


namespace CoCoA
{

  class OpenMathOutput; // fwd decl -- defined in OpenMath.H
  class OpenMathInput;  // fwd decl -- defined in OpenMath.H
  class symbol;         // fwd decl -- defined in symbol.H
  class ideal;          // fwd decl -- defined in ideal.H
  class RingHom;        // fwd decl -- defined in RingHom.H
  class BigInt;         // fwd decl -- defined in BigInt.H
  class BigRat;         // fwd decl -- defined in BigRat.H

  class RingBase; // fwd decl for SmartPtrIRC
  /*-----------------------------------------------------------------*/
  /** \include ring.txt  */
  /*-----------------------------------------------------------------*/
  class ring
  {
  public:
    explicit ring(const RingBase* RingPtr): mySmartPtr(RingPtr) {}
    // Default copy ctor works fine.
    // Assignment disabled because SmartPtrIRC has no assignment.
    const RingBase* operator->() const { return mySmartPtr.operator->(); }  ///< Allow const member fns to be called.
    const RingBase* myRawPtr() const { return mySmartPtr.myRawPtr(); } ///< Used by "downcasting" functions IsRingFp, AsRingFp, etc.
  private: // data members
    SmartPtrIRC<const RingBase> mySmartPtr;
  };


  class RingElemConstRawPtr
  {
  public:
    explicit RingElemConstRawPtr(void const* ptr): myPtr(ptr) {}
    // default copy ctor, assignment, and dtor are fine
    void const* myRawPtr() const { return myPtr; }
  private: // data members
    void const* myPtr;
  };

  class RingElemRawPtr: public RingElemConstRawPtr
  {
    // data members are inherited from RingElemConstRawPtr
  public:
    explicit RingElemRawPtr(void* ptr): RingElemConstRawPtr(ptr) {}
    // default copy ctor, assignment, and dtor are fine
    void* myRawPtr() const { return const_cast<void*>(RingElemConstRawPtr::myRawPtr()); }
  };


  class ConstRefRingElem
  {
  private: // data members
    const ring myR;
  protected:
    RingElemRawPtr myValuePtr;  // VALUE NOT OWNED BY ME -- deliberately not RingElemConstRawPtr (see doc)

  public:
    ConstRefRingElem(const ring& R, RingElemConstRawPtr rawx);
    // default copy ctor works OK
    // default dtor works OK  -- deliberately NOT virtual (see documentation)
  private: // disable assignment
    ConstRefRingElem& operator=(const ConstRefRingElem& rhs); // NEVER DEFINED -- assignment disabled
  protected:
    const ring& myOwner() const { return myR; }
    const RingElemConstRawPtr& myRawPtr() const { return myValuePtr; } // NB implicit conversion to RingElemConstRawPtr
    // friend accessor functions (with non-member-fn syntax)
    friend const RingElemConstRawPtr& raw(const ConstRefRingElem& x);
    friend const ring& owner(const ConstRefRingElem& x);
  };

  class RefRingElem: public ConstRefRingElem
  {
    // data members inherited from ConstRefRingElem
  protected:
    const RingElemRawPtr& myRawPtr() const { return myValuePtr; }
    // friend accessor functions (with non-member-fn syntax)
    friend const RingElemRawPtr& raw(const RefRingElem& x);

  public:
    RefRingElem(const ring& R, RingElemRawPtr rawx): ConstRefRingElem(R, rawx) {}
    // default copy ctor works OK
    // default dtor works OK -- deliberately NOT virtual (see documentation)
    RefRingElem& operator=(const RefRingElem& rhs);
    RefRingElem& operator=(const ConstRefRingElem& rhs);
    RefRingElem& operator=(const MachineInt& n);
    RefRingElem& operator=(const BigInt& N);
    RefRingElem& operator=(const BigRat& Q);
  };


  class RingElem: public RefRingElem
  {
    // Data members inherited from RefRingElem, as are accessors.
    // Sole difference is that the value pointed to by myValuePtr
    // is OWNED by the RingElem object.

  public:
    explicit RingElem(const ring& R);
    RingElem(const ring& R, const MachineInt& n);
    RingElem(const ring& R, const BigInt& N);
    RingElem(const ring& R, const BigRat& Q);
    RingElem(const ring& R, const RingElemRawPtr rawx);
    RingElem(const ring& R, const symbol& s);
    RingElem(const RingElem& copy); // have to define this, default version is unsuitable, cannot be explicit as it is needed in function return
    RingElem(const ConstRefRingElem& copy); // becomes rather a hassle if made explicit
    ~RingElem();  ///< -- deliberately NOT virtual (see documentation)
    RingElem& operator=(const RingElem& rhs);
    RingElem& operator=(const ConstRefRingElem& rhs); // also caters for rhs being RefRingElem
    RingElem& operator=(const MachineInt& n);
    RingElem& operator=(const BigInt& N);
    RingElem& operator=(const BigRat& Q);
  };


  // This is a bit like an auto_ptr to a RingElem; it can surrender ownership.
  class AutoRingElem
  {
  private: // data members
    const ring myR;
    RingElemRawPtr myValuePtr;  // either NULL or VALUE IS OWNED BY ME
  public:
    AutoRingElem(const ring& R, RingElemRawPtr rawx);
    ~AutoRingElem();//inline, see below
    friend RingElemRawPtr raw(AutoRingElem& x);
    friend RingElemRawPtr release(AutoRingElem& x);
  private: // disable assignment and copy ctor
    AutoRingElem(const AutoRingElem&);            // NEVER DEFINED -- disable copy ctor
    AutoRingElem& operator=(const AutoRingElem&); // NEVER DEFINED -- disable assigment
  };


  class RingBase: protected IntrusiveReferenceCount   // abstract class
  {
    friend class SmartPtrIRC<const RingBase>; // Morally "friend ring", so it can alter reference count.

  protected: // data member
    friend long ID(const ring& R);
    static long NewRingID();
    const long myID; // Every concrete ring has a fixed distinct (numerical) ID.

  protected:
    RingBase();             // See inline functions below.
    virtual ~RingBase();    // Destructor of a base class must be virtual.
  private: // Disable assignment and copy ctor.
    RingBase(const RingBase&);            // NEVER DEFINED -- copy ctor disabled
    RingBase& operator=(const RingBase&); // NEVER DEFINED -- assignment disabled
  public:
    typedef RingElemConstRawPtr ConstRawPtr;  // for brevity
    typedef RingElemRawPtr RawPtr;            // for brevity

    // Functions which every ring must implement.
    virtual void myCharacteristic(BigInt& p) const = 0;
    virtual bool IamCommutative() const = 0;
    virtual bool IamIntegralDomain() const = 0;
    virtual bool IamGCDDomain() const;                                ///< Defaults to true.
    virtual bool IamOrderedDomain() const;                            ///< Defaults to false.
    virtual bool IamField() const = 0;
    virtual bool IamExact() const = 0;
    virtual ConstRefRingElem myZero() const = 0;
    virtual ConstRefRingElem myOne() const = 0;
    virtual RingElemRawPtr myNew() const = 0;
    virtual RingElemRawPtr myNew(const MachineInt& n) const = 0;
    virtual RingElemRawPtr myNew(const BigInt& N) const = 0;
    virtual RingElemRawPtr myNew(const BigRat& Q) const;                   ///< by default map num & den then divide
    virtual RingElemRawPtr myNew(const symbol& s) const;
    virtual RingElemRawPtr myNew(ConstRawPtr rawx) const = 0;
    virtual void myRecvTwinFloat(RawPtr rawlhs, ConstRawPtr rawx) const = 0; ///< default throws error
    virtual void myDelete(RawPtr rawx) const = 0;                      ///< destroys x (incl all resources)
    virtual void mySwap(RawPtr rawx, RawPtr rawy) const = 0;           ///< swap(x, y)
    virtual void myAssign(RawPtr rawlhs, ConstRawPtr rawx) const = 0;  ///< lhs = x
    virtual void myAssign(RawPtr rawlhs, const MachineInt& n) const = 0;  ///< lhs = n
    virtual void myAssign(RawPtr rawlhs, const BigInt& N) const = 0;       ///< lhs = N
    virtual void myAssign(RawPtr rawlhs, const BigRat& Q) const;           ///< lhs = Q, by default map num & den then divide
    virtual void myAssignZero(RawPtr rawlhs) const = 0;                ///< lhs = 0
    virtual void myNegate(RawPtr rawlhs, ConstRawPtr rawx) const = 0;  ///< lhs = -x
    virtual void myAdd(RawPtr rawlhs, ConstRawPtr rawx, ConstRawPtr rawy) const = 0; ///< lhs = x+y
    virtual void mySub(RawPtr rawlhs, ConstRawPtr rawx, ConstRawPtr rawy) const = 0; ///< lhs = x-y
    virtual void myMul(RawPtr rawlhs, ConstRawPtr rawx, ConstRawPtr rawy) const = 0; ///< lhs = x*y
    virtual void myDiv(RawPtr rawlhs, ConstRawPtr rawx, ConstRawPtr rawy) const = 0; ///< lhs = x/y
    virtual bool myIsDivisible(RawPtr rawlhs, ConstRawPtr rawx, ConstRawPtr rawy) const = 0;///< lhs = x/y, if divisible
    virtual bool myIsInvertible(ConstRawPtr rawx) const;                             ///< true iff x is invertible
    virtual bool myIsIrred(ConstRawPtr rawx) const;                                  ///< true iff x is irreducible (if defined)
    virtual void myGcd(RawPtr rawlhs, ConstRawPtr rawx, ConstRawPtr rawy) const;     ///< lhs = gcd(x,y) if GCDDomain;
    virtual void myLcm(RawPtr rawlhs, ConstRawPtr rawx, ConstRawPtr rawy) const;     ///< lhs = lcm(x,y) if GCDDomain;
    virtual void myGcdQuot(RawPtr rawlhs, RawPtr rawxquot, RawPtr rawyquot, ConstRawPtr rawx, ConstRawPtr rawy) const; ///< lhs = gcd(x,y)  xquot = x/gcd, yquot = y/gcd  if GCDDomain;
    virtual void myExgcd(RawPtr rawlhs, RawPtr rawxcofac, RawPtr rawycofac, ConstRawPtr rawx, ConstRawPtr rawy) const; ///< lhs = gcd(x,y) = xcofac*x + ycofac*y  if GCDDomain;
    virtual void myNormalizeFrac(RawPtr num, RawPtr den) const;
    virtual void myNormalizeFracNoGcd(RawPtr num, RawPtr den) const;

    void myPower(RawPtr rawlhs, ConstRawPtr rawx, long n) const;                     ///< lhs = x^n, n>=0
    void myPower(RawPtr rawlhs, ConstRawPtr rawx, const BigInt& N) const;            ///< lhs = x^N, N>=0
    void mySquare(RawPtr rawlhs, ConstRawPtr rawx) const;                            ///< lhs = x^2, default impl
    virtual void mySymbols(std::vector<symbol>& SymList) const;                      ///< append symbols in ring to SymList
    virtual RingElem mySymbolValue(const symbol& sym) const = 0;                      ///< returns the RingElem corresponding to sym
    virtual void myOutput(std::ostream& out, ConstRawPtr rawx) const = 0;            ///< out << x
    virtual bool myIsPrintAtom(ConstRawPtr rawx) const;                              ///< x^n may be printed without parentheses
    virtual bool myIsPrintedWithMinus(ConstRawPtr /*rawx*/) const { return false; }  ///< first character of x printed is a minus sign. Default false
    virtual void myOutputSelf(std::ostream& out) const = 0;                          ///< out << R
    virtual void myOutputSelf(OpenMathOutput& OMOut) const = 0;                      ///< OMOut << R
    virtual void myOutput(OpenMathOutput& OMOut, ConstRawPtr rawx) const = 0;        ///< OMOut << x
    virtual bool myIsZero(ConstRawPtr rawx) const = 0;                               ///< x == 0
    virtual bool myIsOne(ConstRawPtr rawx) const = 0;                                ///< x == 1
    virtual bool myIsMinusOne(ConstRawPtr rawx) const;                               ///< x == -1
    virtual bool myIsInteger(BigInt& N, ConstRawPtr rawx) const = 0;                 ///< true iff x is integer
    virtual bool myIsRational(BigRat& Q, ConstRawPtr rawx) const = 0;                    ///< true iff x is rational
    virtual bool myIsDouble(double& d, ConstRawPtr rawx) const;                      ///< false iff x overflows
    virtual bool myIsZeroAddMul(RawPtr rawlhs, ConstRawPtr rawy, ConstRawPtr rawz) const;   ///< lhs += y*z, result says whether lhs == 0.
    virtual bool myIsZeroAddMul(RawPtr rawlhs, RawPtr rawtmp, ConstRawPtr rawy, ConstRawPtr rawz) const;   ///< lhs += y*z, result says whether lhs == 0.
    virtual bool myIsEqual(ConstRawPtr rawx, ConstRawPtr rawy) const = 0;            ///< x == y
    // The next three functions make sense only for arithmetically ordered rings.
    virtual int myCmp(ConstRawPtr rawx, ConstRawPtr rawy) const;                     ///< result is <0, =0, >0 according as x<y, x=y, x>y
    virtual int mySign(ConstRawPtr rawx) const;                                      ///< -1,0,+1 according as x <0,=0,>0
    virtual bool myFloor(BigInt& N, ConstRawPtr rawx) const;                         ///< true iff x is integer; put floor(x) in N.

    virtual ideal myIdealCtor(const std::vector<RingElem>& gens) const = 0;

    virtual RingHom myCompose(const RingHom& phi, const RingHom& theta) const = 0;   ///< phi(theta(...))

  protected: // These are almost an implementation detail
    virtual void myPowerSmallExp(RawPtr rawlhs, ConstRawPtr rawx, long n) const = 0; ///< lhs = x^n (non-trivial, i.e. n>=2)
    virtual void myPowerBigExp(RawPtr rawlhs, ConstRawPtr rawx, const BigInt& N) const;///< lhs = x^N (non-triv, N large); default gives error
    void mySequentialPower(RawPtr rawlhs, ConstRawPtr rawx, long n) const;           ///< lhs = x^n (assumes n >= 0)
    void myBinaryPower(RawPtr rawlhs, ConstRawPtr rawx, long n) const;               ///< lhs = x^n (assumes n > 0)
    void myBinaryPower(RawPtr rawlhs, ConstRawPtr rawx, const BigInt& N) const;      ///< lhs = x^N (assumes N > 0)
    void myGcdInField(RawPtr rawlhs, ConstRawPtr rawx, ConstRawPtr rawy) const;      ///< lhs = gcd(x, y) in a field, result is 0 or 1
  private:   // This is an implementation detail
    void myBinaryPowerLoop(RawPtr rawlhs, ConstRawPtr rawx, long n) const;
  };


  BigInt characteristic(const ring& R);
  std::vector<symbol> symbols(const ring& R);

  void swap(RefRingElem f, RefRingElem g);

  // Some syntactic sugar for arithmetic on RingElems
  bool operator==(ConstRefRingElem, ConstRefRingElem);
  bool operator!=(ConstRefRingElem, ConstRefRingElem);
  RingElem operator-(ConstRefRingElem);
  RingElem operator+(ConstRefRingElem, ConstRefRingElem);
  RingElem operator-(ConstRefRingElem, ConstRefRingElem);
  RingElem operator*(ConstRefRingElem, ConstRefRingElem);
  RingElem operator/(ConstRefRingElem, ConstRefRingElem);
  RingElem gcd(ConstRefRingElem, ConstRefRingElem);
  RingElem lcm(ConstRefRingElem, ConstRefRingElem);
  void GcdQuot(RefRingElem gcd, RefRingElem xquot, RefRingElem yquot, ConstRefRingElem x, ConstRefRingElem y);
  RefRingElem operator+=(RefRingElem, ConstRefRingElem);
  RefRingElem operator-=(RefRingElem, ConstRefRingElem);
  RefRingElem operator*=(RefRingElem, ConstRefRingElem);
  RefRingElem operator/=(RefRingElem, ConstRefRingElem);
  std::ostream& operator<<(std::ostream&, ConstRefRingElem);
//??? see io.H  std::ostream& operator<<(std::ostream&, const std::vector<RingElem>&);
  OpenMathOutput& operator<<(OpenMathOutput& OMOut, ConstRefRingElem);
  bool IsZero(ConstRefRingElem);
  bool IsOne(ConstRefRingElem);
  bool IsMinusOne(ConstRefRingElem);
  bool IsInteger(BigInt& N, ConstRefRingElem x);
  bool IsRational(BigRat& Q, ConstRefRingElem x);
  bool IsDouble(double& d, ConstRefRingElem x);
  bool IsInvertible(ConstRefRingElem);
  bool IsIrred(ConstRefRingElem);
  bool IsDivisible(ConstRefRingElem, ConstRefRingElem);
  RingElem power(ConstRefRingElem x, const MachineInt& n); ///< NB exponent may be negative
  RingElem power(ConstRefRingElem x, const BigInt& N);         ///< NB exponent may be negative
  ConstRefRingElem zero(const ring& R);
  ConstRefRingElem one(const ring& R);
  std::ostream& operator<<(std::ostream& out, const ring& R);
  OpenMathOutput& operator<<(OpenMathOutput& OMOut, const ring& R);

  // Syntactic sugar for operations on RingElems in an ordered domain.
  int sign(ConstRefRingElem x);
  RingElem abs(ConstRefRingElem x);
  BigInt floor(ConstRefRingElem x);
  BigInt ceil(ConstRefRingElem x);
  BigInt NearestInteger(ConstRefRingElem x);
  int CmpDouble(ConstRefRingElem x, double z);
  int cmp(ConstRefRingElem x, ConstRefRingElem y);
  bool operator<(ConstRefRingElem x, ConstRefRingElem y);
  bool operator<=(ConstRefRingElem x, ConstRefRingElem y);
  bool operator>(ConstRefRingElem x, ConstRefRingElem y);
  bool operator>=(ConstRefRingElem x, ConstRefRingElem y);

  // More syntactic sugar: arithmetic between RingElems and MachineInts
  bool operator==(ConstRefRingElem, const MachineInt&);
  bool operator!=(ConstRefRingElem, const MachineInt&);
  RingElem operator+(ConstRefRingElem, const MachineInt&);
  RingElem operator-(ConstRefRingElem, const MachineInt&);
  RingElem operator*(ConstRefRingElem, const MachineInt&);
  RingElem operator/(ConstRefRingElem, const MachineInt&);
  RingElem gcd(ConstRefRingElem, const MachineInt&);
  bool operator==(const MachineInt&, ConstRefRingElem);
  bool operator!=(const MachineInt&, ConstRefRingElem);
  RingElem operator+(const MachineInt&, ConstRefRingElem);
  RingElem operator-(const MachineInt&, ConstRefRingElem);
  RingElem operator*(const MachineInt&, ConstRefRingElem);
  RingElem operator/(const MachineInt&, ConstRefRingElem);
  RingElem gcd(const MachineInt&, ConstRefRingElem);
  RefRingElem operator+=(RefRingElem, const MachineInt&);
  RefRingElem operator-=(RefRingElem, const MachineInt&);
  RefRingElem operator*=(RefRingElem, const MachineInt&);
  RefRingElem operator/=(RefRingElem, const MachineInt&);
  bool IsDivisible(const MachineInt&, ConstRefRingElem);
  bool IsDivisible(ConstRefRingElem, const MachineInt&);

  // Ordered domain operations between RingElems and MachineInts
  int cmp(ConstRefRingElem x, const MachineInt& n);
  int cmp(const MachineInt& n, ConstRefRingElem y);
  bool operator<(ConstRefRingElem x, const MachineInt& y);
  bool operator<=(ConstRefRingElem x, const MachineInt& y);
  bool operator>(ConstRefRingElem x, const MachineInt& y);
  bool operator>=(ConstRefRingElem x, const MachineInt& y);
  bool operator<(const MachineInt& x, ConstRefRingElem y);
  bool operator<=(const MachineInt& x, ConstRefRingElem y);
  bool operator>(const MachineInt& x, ConstRefRingElem y);
  bool operator>=(const MachineInt& x, ConstRefRingElem y);

  // More syntactic sugar: arithmetic between RingElems and BigInts
  bool operator==(ConstRefRingElem, const BigInt&);
  bool operator!=(ConstRefRingElem, const BigInt&);
  RingElem operator+(ConstRefRingElem, const BigInt&);
  RingElem operator-(ConstRefRingElem, const BigInt&);
  RingElem operator*(ConstRefRingElem, const BigInt&);
  RingElem operator/(ConstRefRingElem, const BigInt&);
  RingElem gcd(ConstRefRingElem, const BigInt&);
  bool operator==(const BigInt&, ConstRefRingElem);
  bool operator!=(const BigInt&, ConstRefRingElem);
  RingElem operator+(const BigInt&, ConstRefRingElem);
  RingElem operator-(const BigInt&, ConstRefRingElem);
  RingElem operator*(const BigInt&, ConstRefRingElem);
  RingElem operator/(const BigInt&, ConstRefRingElem);
  RingElem gcd(const BigInt&, ConstRefRingElem);
  RefRingElem operator+=(RefRingElem, const BigInt&);
  RefRingElem operator-=(RefRingElem, const BigInt&);
  RefRingElem operator*=(RefRingElem, const BigInt&);
  RefRingElem operator/=(RefRingElem, const BigInt&);
  bool IsDivisible(const BigInt& N, ConstRefRingElem);
  bool IsDivisible(ConstRefRingElem, const BigInt& N);

  // Ordered domain operations on RingElems and BigInts
  int cmp(ConstRefRingElem x, const BigInt& N);
  int cmp(const BigInt& N, ConstRefRingElem y);
  bool operator<(ConstRefRingElem x, const BigInt& y);
  bool operator<=(ConstRefRingElem x, const BigInt& y);
  bool operator>(ConstRefRingElem x, const BigInt& y);
  bool operator>=(ConstRefRingElem x, const BigInt& y);
  bool operator<(const BigInt& x, ConstRefRingElem y);
  bool operator<=(const BigInt& x, ConstRefRingElem y);
  bool operator>(const BigInt& x, ConstRefRingElem y);
  bool operator>=(const BigInt& x, ConstRefRingElem y);

  // More syntactic sugar: arithmetic between RingElems and BigRats
  bool operator==(ConstRefRingElem, const BigRat&);
  bool operator!=(ConstRefRingElem, const BigRat&);
  RingElem operator+(ConstRefRingElem, const BigRat&);
  RingElem operator-(ConstRefRingElem, const BigRat&);
  RingElem operator*(ConstRefRingElem, const BigRat&);
  RingElem operator/(ConstRefRingElem, const BigRat&);
  RingElem gcd(ConstRefRingElem, const BigRat&);
  bool operator==(const BigRat&, ConstRefRingElem);
  bool operator!=(const BigRat&, ConstRefRingElem);
  RingElem operator+(const BigRat&, ConstRefRingElem);
  RingElem operator-(const BigRat&, ConstRefRingElem);
  RingElem operator*(const BigRat&, ConstRefRingElem);
  RingElem operator/(const BigRat&, ConstRefRingElem);
  RingElem gcd(const BigRat&, ConstRefRingElem);
  RefRingElem operator+=(RefRingElem, const BigRat&);
  RefRingElem operator-=(RefRingElem, const BigRat&);
  RefRingElem operator*=(RefRingElem, const BigRat&);
  RefRingElem operator/=(RefRingElem, const BigRat&);
  bool IsDivisible(const BigRat& N, ConstRefRingElem);
  bool IsDivisible(ConstRefRingElem, const BigRat& N);

  // Ordered domain operations on RingElems and BigRats
  int cmp(ConstRefRingElem x, const BigRat& N);
  int cmp(const BigRat& N, ConstRefRingElem y);
  bool operator<(ConstRefRingElem x, const BigRat& y);
  bool operator<=(ConstRefRingElem x, const BigRat& y);
  bool operator>(ConstRefRingElem x, const BigRat& y);
  bool operator>=(ConstRefRingElem x, const BigRat& y);
  bool operator<(const BigRat& x, ConstRefRingElem y);
  bool operator<=(const BigRat& x, ConstRefRingElem y);
  bool operator>(const BigRat& x, ConstRefRingElem y);
  bool operator>=(const BigRat& x, ConstRefRingElem y);


  //---------------------------------------------------------------------------
  // inline functions on rings -- the order of appearance might be important!


  inline bool operator==(const ring& R1, const ring& R2)
  {
    return R1.myRawPtr() == R2.myRawPtr();
//    return R1.mySmartPtr == R2.mySmartPtr;  // equivalent formulation
  }

  inline bool operator!=(const ring& R1, const ring& R2)
  {
    return !(R1 == R2);
  }


  //----------------------------------------------------------------------
  // Inline functions.  The "owner" and "raw" accessor functions must come first.


  inline AutoRingElem::AutoRingElem(const ring& R, RingElemRawPtr rawx):
      myR(R),
      myValuePtr(rawx)
  {}


  inline AutoRingElem::~AutoRingElem()
  {
    if (myValuePtr.myRawPtr())
      myR->myDelete(myValuePtr);
  }

  inline RingElemRawPtr raw(AutoRingElem& x)
  {
    CoCoA_ASSERT(x.myValuePtr.myRawPtr() != 0);
    return x.myValuePtr;
  }

  inline RingElemRawPtr release(AutoRingElem& x)
  {
    CoCoA_ASSERT(x.myValuePtr.myRawPtr() != 0);
    RingElemRawPtr rawans = x.myValuePtr;
    x.myValuePtr = RingElemRawPtr(0);
    return rawans;
  }


  inline ConstRefRingElem::ConstRefRingElem(const ring& R, RingElemConstRawPtr rawx):
      myR(R),
      myValuePtr(const_cast<void*>(rawx.myRawPtr()))
  {}


//??? BEWARE reference to temporary???? e.g. const ring& R = owner(a+b);
  inline const ring& owner(const ConstRefRingElem& x)
  {
    return x.myOwner();
  }


  inline const RingElemConstRawPtr& raw(const ConstRefRingElem& x)
  {
    return x.myRawPtr();
  }

  inline const RingElemRawPtr& raw(const RefRingElem& x)
  {
    return x.myRawPtr();
  }



  inline long ID(const ring& R)
  {
    return R->myID;
  }


  inline RingBase::RingBase():
    IntrusiveReferenceCount(),
    myID(NewRingID())
  {}


  inline RingBase::~RingBase()
  {}


  inline RingElem::RingElem(const ring& R):
      RefRingElem(R, R->myNew())
  {}


  inline RingElem::RingElem(const ring& R, RingElemRawPtr rawx):
      RefRingElem(R, rawx)
  {}


  inline RingElem::RingElem(const RingElem& copy):
      RefRingElem(owner(copy), owner(copy)->myNew(raw(copy)))
  {}


  inline RingElem::RingElem(const ConstRefRingElem& copy):
      RefRingElem(owner(copy), owner(copy)->myNew(raw(copy)))
  {}



  inline ConstRefRingElem zero(const ring& R)
  {
    return R->myZero();
  }


  inline ConstRefRingElem one(const ring& R)
  {
    return R->myOne();
  }


  inline bool IsGCDDomain(const ring& R)
  {
    return R->IamGCDDomain();
  }


  inline bool IsCommutative(const ring& R)
  {
    return R->IamCommutative();
  }


  inline bool IsIntegralDomain(const ring& R)
  {
    return R->IamIntegralDomain();
  }


  inline bool IsField(const ring& R)
  {
    return R->IamField();
  }


  inline bool IsExact(const ring& R)
  {
    return R->IamExact();
  }


  inline bool IsOrderedDomain(const ring& R)
  {
    return R->IamOrderedDomain();
  }

  //??? bool contains(const RingBase& big_ring, const RingBase& little_ring);


  // Define the not-equals functions here:

  inline bool operator!=(ConstRefRingElem x, ConstRefRingElem y)
  {
    return !(x == y);
  }

  inline bool operator!=(ConstRefRingElem r, const MachineInt& n)
  {
    return !(r == n);
  }

  inline bool operator!=(const MachineInt& n, ConstRefRingElem r)
  {
    return !(r == n);
  }

  inline bool operator!=(ConstRefRingElem r, const BigInt& N)
  {
    return !(r == N);
  }

  inline bool operator!=(const BigInt& N, ConstRefRingElem r)
  {
    return !(r == N);
  }

} // end of namespace CoCoA


// RCS header/log in the next few lines
// $Header: /Volumes/Home_1/cocoa/cvs-repository/CoCoALib-0.99/include/CoCoA/ring.H,v 1.28 2011/11/09 13:51:29 bigatti Exp $
// $Log: ring.H,v $
// Revision 1.28  2011/11/09 13:51:29  bigatti
// -- renamed MachineInteger --> MachineInt
//
// Revision 1.27  2011/08/24 10:22:45  bigatti
// -- renamed QQ --> BigRat
//
// Revision 1.26  2011/08/14 15:52:17  abbott
// Changed ZZ into BigInt (phase 1: just the library sources).
//
// Revision 1.25  2011/08/13 08:10:13  abbott
// Added missing dtor for AutoRingElem!
//
// Revision 1.24  2011/06/23 16:04:47  abbott
// Added IamExact mem fn for rings.
// Added myRecvTwinFloat mem fn for rings.
// Added first imple of RingHom from RingTwinFloat to other rings.
//
// Revision 1.23  2011/05/19 14:45:27  abbott
// Removed commented out decls of old form of IsRational.
// Added IsDouble/myIsDouble.
//
// Revision 1.22  2011/03/30 09:12:33  bigatti
// -- added myNew(const symbol& s)
//
// Revision 1.21  2011/03/10 16:39:34  abbott
// Replaced (very many) size_t by long in function interfaces (for rings,
// PPMonoids and modules).  Also replaced most size_t inside fn defns.
//
// Revision 1.20  2011/01/28 11:42:41  bigatti
// -- added default value for IsPrintedWithMinus
//
// Revision 1.19  2011/01/19 16:13:57  bigatti
// -- added lcm/myLcm
//
// Revision 1.18  2010/12/20 15:19:29  bigatti
// -- modified IsZeroAddMul with temporary variable (slug found with cyclotomic)
//
// Revision 1.17  2010/10/01 15:20:33  bigatti
// -- added mySymbolValue
// -- added RingElem(R, sym)
//
// Revision 1.16  2010/09/06 09:06:25  abbott
// Undid Giovanni's changes, which are no longer necessary.
//
// Revision 1.15  2010/09/04 10:29:57  lagorio
// *** empty log message ***
//
// Revision 1.14  2009/12/03 17:37:22  abbott
// Moved fns characteristic & swap into .C file, so that .H does not
// need to include ZZ.H and error.H.
//
// Revision 1.13  2009/10/29 18:30:09  abbott
// Changed the ring ID value to be a long (previously was size_t).
// Some minor cleaning to include directives.
//
// Revision 1.12  2009/09/24 16:23:38  abbott
// Put include directives in alphabetical order.
//
// Revision 1.11  2009/07/02 16:32:11  abbott
// Consequential changes stemming from new class BigRat, and modified interface to the member
// function RingBase::myIsRational.  Also some new conversion functions.
//
// Revision 1.10  2008/12/17 12:11:52  abbott
// Changed type from long to MachineInt in operations which use a machine integer
// in place of a RingElem.  The change is "superficial" but affects many files.
//
// Revision 1.9  2008/11/18 10:24:48  abbott
// Added floor, ceil, NearestInteger and CmpDouble functions.
// Also added myFloor member fn.  Plus some very minor code tidying.
//
// Revision 1.8  2008/06/30 17:21:57  abbott
// Added some missing const keywords -- not really necessary but express better the programmer's intention.
//
// Revision 1.7  2008/04/22 14:44:26  abbott
// Removed top level function square.
// Internal powering routine myBinaryPower now uses mySquare.
//
// Revision 1.6  2008/04/15 14:57:03  bigatti
// -- added mySquare, square
//
// Revision 1.5  2008/03/12 16:38:47  bigatti
// -- added: IsIrred
//
// Revision 1.4  2007/10/30 17:14:11  abbott
// Changed licence from GPL-2 only to GPL-3 or later.
// New version for such an important change.
//
// Revision 1.3  2007/05/22 22:45:14  abbott
// Changed fn name IsUnit to IsInvertible.
//
// Revision 1.2  2007/05/18 10:46:06  bigatti
// -- added comment: #include "CoCoA/ZZ.H"  // for inline ZZ characteristic(ring)
//
// Revision 1.1.1.1  2007/03/09 15:16:11  abbott
// Imported files
//
// Revision 1.17  2007/01/15 16:16:14  cocoa
// -- added prefix "raw" to RawPtr arguments names
// -- changed rhs into rawx, n, or N
//
// Revision 1.16  2007/01/13 14:14:34  cocoa
// Overhaul of RingHom code: it nows uses SmartPtrIRC, and printing is more logical.
// Have not yet updated the documentation.
//
// Revision 1.15  2007/01/08 16:39:22  cocoa
// -- changed comment about operator<<
//
// Revision 1.14  2006/12/06 17:18:40  cocoa
// -- removed #include "config.H"
//
// Revision 1.13  2006/11/27 13:06:23  cocoa
// Anna and Michael made me check without writing a proper message.
//
// Revision 1.12  2006/11/23 17:45:46  cocoa
// -- updated #include and forward declarations
//
// Revision 1.11  2006/11/22 17:49:33  cocoa
// -- doxygen style comments
//
// Revision 1.10  2006/11/21 17:08:02  cocoa
// added explicit call to IntrusiveReferenceCount ctor in RingBase ctor
//
// Revision 1.9  2006/11/20 15:55:02  cocoa
// ring is now a class again.  Improved definitions of operator-> in derived classes.
//
// Revision 1.8  2006/11/03 15:37:47  cocoa
// -- cleaned up code after testing on usage of SmartPtrIRC
//
// Revision 1.7  2006/11/03 14:01:46  cocoa
// -- changed: reference counting in ring, PPMonoids and OrdvArith now
//    uses SmartPtrIRC
//
// Revision 1.6  2006/11/02 13:25:44  cocoa
// Simplification of header files: the OpenMath classes have been renamed.
// Many minor consequential changes.
//
// Revision 1.5  2006/10/27 19:09:45  cocoa
// Replaced some member functions of CoCoA::symbol by friend functions.
// Removed some include dependency on symbol.H
//
// Revision 1.4  2006/10/16 23:18:59  cocoa
// Corrected use of std::swap and various special swap functions.
// Improved myApply memfn for homs of RingDistrMPolyInlPP.
//
// Revision 1.3  2006/10/06 14:04:15  cocoa
// Corrected position of #ifndef in header files.
// Separated CoCoA_ASSERT into assert.H from config.H;
// many minor consequential changes (have to #include assert.H).
// A little tidying of #include directives (esp. in Max's code).
//
// Revision 1.2  2006/08/07 21:23:25  cocoa
// Removed almost all publicly visible references to SmallExponent_t;
// changed to long in all PPMonoid functions and SparsePolyRing functions.
// DivMask remains to sorted out.
//
// Revision 1.1.1.1  2006/05/30 11:39:37  cocoa
// Imported files
//
// Revision 1.10  2006/05/29 16:22:37  cocoa
// Third time lucky???
// Added myIsInteger member function to all rings (NYI for RingFloat).
//
// Revision 1.9  2006/05/12 16:10:58  cocoa
// Added OpenMathFwd.H, and tidied OpenMath.H.
// Many consequential but trivial changes.
//
// Revision 1.8  2006/04/27 13:43:35  cocoa
// Added abs function (only for arithmetically ordered rings).
//
// Revision 1.7  2006/04/21 15:01:36  cocoa
// Changed default implementation of RingBase::myGcd -- it now gives a SERIOUS
// error.  All fields must now handle a call to gcd explicitly: they can use
// the new myGcdInField function.  It's now cleaner than it was.
//
// Revision 1.6  2006/03/27 12:21:25  cocoa
// Minor silly changes to reduce number of complaints from some compiler or other.
//
// Revision 1.5  2006/03/15 18:09:31  cocoa
// Changed names of member functions which print out their object
// into myOutputSelf -- hope this will appease the Intel C++ compiler.
//
// Revision 1.4  2006/03/14 15:01:49  cocoa
// Improved the implementation of ring member fns for computing powers.
// Should keep Intel C++ compiler quieter too.
//
// Revision 1.3  2006/03/12 21:28:34  cocoa
// Major check in after many changes
//
// Revision 1.2  2006/02/14 16:22:20  cocoa
// -- defined "operator<<" for vector<RingElem>&  in ring.H/C
//
// Revision 1.1.1.1  2005/10/17 10:46:54  cocoa
// Imported files
//
// Revision 1.4  2005/09/22 18:04:17  cocoa
// It compiles; the tests run OK.  The examples compile.
// No documentation -- the mindless eurocrats have rendered
// me mindless too.
//
// Revision 1.3  2005/07/08 15:09:29  cocoa
// Added new symbol class (to represent names of indets).
// Integrated the new class into concrete polynomial rings
// and PPMonoid -- many consequential changes.
// Change ctors for the "inline" sparse poly rings: they no
// longer expect a PPMonoid, but build their own instead
// (has to be a PPMonoidOv).
//
// Revision 1.2  2005/06/22 14:47:56  cocoa
// PPMonoids and PPMonoidElems updated to mirror the structure
// used for rings and RingElems.  Many consequential changes.
//
// Revision 1.1.1.1  2005/05/03 15:47:30  cocoa
// Imported files
//
// Revision 1.5  2005/04/20 15:40:48  cocoa
// Major change: modified the standard way errors are to be signalled
// (now via a macro which records filename and line number).  Updated
// documentation in error.txt accordingly.
//
// Improved the documentation in matrix.txt (still more work to be done).
//
// Revision 1.4  2005/04/19 14:06:04  cocoa
// Added GPL and GFDL licence stuff.
//
// Revision 1.3  2005/02/11 16:45:24  cocoa
// Removed the useless and misleading functions myInit and myKill
// from the SmallFp*Impl classes; various consequential changes.
//
// Revision 1.2  2005/02/11 14:15:20  cocoa
// New style ring elements and references to ring elements;
// I hope I have finally got it right!
//
// Revision 1.1.1.1  2005/01/27 15:12:13  cocoa
// Imported files
//
// Revision 1.23  2004/11/25 16:14:21  cocoa
// (1) Fixed definition of specialization of std::swap template function
//     so that it compiles with gcc 3.4.3
// (2) Implemented monomial function for polynomial rings.
// (3) Added one(PPM) and PPM->myOne() functions.
//
// Revision 1.22  2004/11/18 18:33:40  cocoa
// Now every ring know its own "one" element (as well as "zero").
// Several consequential changes.
//
// Revision 1.21  2004/11/11 14:05:02  cocoa
// -- minor changes for doxygen
//
// Revision 1.20  2004/11/09 15:57:01  cocoa
// -- minor changes for doxygen
//
// Revision 1.19  2004/11/04 18:47:42  cocoa
// (1) Ring member functions which previously expected mpz_t args
//     now expect ZZ args.  Numerous minor consequential changes.
// (2) Renamed function which gives access to the mpz_t value inside
//     a ZZ object: previously was raw(...), now is mpzref(...).
//     Plenty of calls had to be altered.
//
// Revision 1.18  2004/07/27 16:03:38  cocoa
// Added IsCommutative test and IamCommutative member function
// to all rings.  Tidied geobuckets a little.
//
// Revision 1.17  2004/07/20 15:04:05  cocoa
// The next step in the new "ring element" conversion process:
// handling the case of creating a "const RefRingElem" object
// (since C++ refuses to do this properly itself).
//
// Revision 1.16  2004/07/16 15:45:12  cocoa
// First stage of new RingElem implementation completed.
//
// Revision 1.15  2004/07/13 16:32:26  cocoa
// First stage of major revamp of ring elements.
// Implementation of RingFp has been split into "ring interface"
// and "algorithms plus data structures".
//
// Revision 1.14  2004/06/29 17:10:22  cocoa
// Partially tidied use of "protected" and "private" in various
// base classes.  Checking in at the end of the day -- it works,
// and I wouldn't want it to be lost next time point's disk
// misbehaves.
//
// Revision 1.13  2004/05/27 16:14:02  cocoa
// Minor revision for new coding conventions.
//
// Revision 1.12  2004/05/24 15:52:13  cocoa
// Major update:
//   new error mechanism
//   many fixes
//   RingHoms almost work now
//   RingFloat much improved
//
// Revision 1.11  2004/04/08 15:33:34  cocoa
// Added function IsInteger, and the related RingBase::myIsInteger
// virtual function, plus all necessary implementations.
//
// Revision 1.10  2004/03/20 17:46:10  cocoa
// Check in prior to departure to RWCA
//
// Revision 1.9  2004/02/03 16:16:20  cocoa
// Removed pointless IamGCDDomain functions from several concrete rings.
// Added IamOrderedDomain functions where appropriate.
// Tidied ctors for the small finite fields.
//
// Revision 1.8  2004/01/30 14:08:16  cocoa
// Tidied RingRawValue union -- forgot to check this in with all the other
// files.
//
// Revision 1.7  2004/01/28 16:03:27  cocoa
// Sundry minor changes.
//
// Revision 1.6  2003/11/21 14:32:17  cocoa
// -- added fields for DistrMPoly
//
// Revision 1.5  2003/11/14 13:06:04  cocoa
// -- New function "myIsPrintAtom" for printing polynomials and fractions
//
// Revision 1.4  2003/10/17 10:51:06  cocoa
// Major cleaning, and new naming convention.
//
// Revision 1.3  2003/10/09 14:55:19  cocoa
// - minor debugging after merge
//
// Revision 1.2  2003/10/09 12:12:26  cocoa
// New coding convention for rings.
//
// Revision 1.1.1.1  2003/09/24 12:55:43  cocoa
// Imported files
//
// Revision 1.24  2003/06/23 16:35:06  abbott
// Updates prior to public release:
//   changed characteristic to yield a big integer
//   added IsIntegralDomain function
//
// Revision 1.23  2003/05/30 11:57:47  abbott
// Minor revisions to some comments (for compatibility with "doxygen".
//
// Revision 1.22  2003/04/16 14:14:26  abbott
// Main changes:
//   added functions for ideals and homomorphisms
//     RingBase::NewIdeal  -- to create new ideals
//     RingBase::ReduceMod -- to reduce a value modulo an ideal
//
//   added a function to compute the composition of two ring homomorphisms
//     RingBase::compose
//
//   added IsDivisible top level function
//   added RingBase::ZeroRefCount  (a slightly "dirty" function).
//
// Revision 1.21  2003/01/21 15:33:01  abbott
// Major restructuring (and some renaming):
//   RingBase is now the base class for all rings, and
//   it includes an intrusive reference count;
//   ring is a reference counted pointer class (to RingBase);
//   RingElem, ConstRefRingElem are now at top level;
//   RingRawValue is also at top level (unhappy about this).
// Commented out the "zero" function.
//
// Revision 1.20  2002/12/13 15:14:05  abbott
// Added functions IsOne and IsMinusOne (both at global level and
// as member functions of an AbstractRing).  Commented out the
// member function for testing equality between a RingElem and a
// machine integer.  Added member functions for initializing or
// assigning from a big integer (of type ZZ).  Added syntactic
// sugar operators for arithmetic between RingElems and ZZs.
//
// Revision 1.19  2002/12/11 11:49:09  abbott
// Checking in for safety -- this code does at least compile and work.
// Exponents in power functions must now be non-negative (unsigned int).
// Added functions between RingElems and ZZs (big integers).
// Added two member functions for initialising/assigning from big integers.
//
// Made op == and != inline because Anna wanted them so; probably revoke
// this after IsOne has been invented.
//
// Revision 1.18  2002/11/14 16:24:04  abbott
// Extensive changes.  ring renamed to AbstractRing.
// New typedef RingElem for AbstractRing::elem.
// New typedef ConstRawValue to be used as arg type in ring member functions.
// Old alias subclass has been removed -- its semantics were unclear.
// New ConstRefElem subclass replaces old alias -- clearer semantics than alias.
// New typedef ConstRefRingElem to be used as arg type for read only RingElems :-(
// New specialization of std::swap template fn for RingElems.
//
// Revision 1.17  2002/07/05 15:15:04  abbott
// Added IsDivisible pure virtual member function.
// Added SequentialPower member function, and made power pure virtual.
//
// Revision 1.16  2002/06/27 16:05:53  abbott
// Added two missing equality/not-equality operators.
// Added BinaryPower member function (and BinaryPowerLoop).
//
// Revision 1.15  2002/06/21 14:36:35  abbott
// Changed name of "equal" member function to "IsEqual".
// Added field to ring::elem to support FractionField.
// Added "syntactic sugar" to allow arithmetic between ring::elems
// and machine integers.
//
// Revision 1.14  2002/05/30 16:19:21  abbott
// Removed an apparently bogus init member function: its second arg was a ring::elem
// rather than a RawValue.
//
// Revision 1.13  2002/05/30 13:33:12  abbott
// Added IsField and IsGCDDomain functions (also as member functions).
// Added zero function (and member function).
// Added equals and not-equals operators.
//
// Revision 1.12  2002/05/15 14:50:29  abbott
// Extensive revisions.
//   Added new member functions for ring: characteristic, negate, power.
//   Reordered various blocks of code.
//   Class elem is now class ring::elem.
//   Enlarged ring::elem objects so that they can be aliases.
//   Changed "const RawValue&" arguments into simple "RawValue" arguments.
//
// Revision 1.11  2002/03/28 15:56:25  abbott
// Added field to ring::RawValue for ring_DMP.
//
// Revision 1.10  2002/02/15 11:53:59  bigatti
// - added IsGCDDomain, gcd, "=", "==", "!="
//
// Revision 1.9  2002/02/08 11:09:54  bigatti
// - changed syntax to IsZeroAddMul
//
// Revision 1.8  2002/01/30 14:55:33  abbott
// Apparently the destructor should not have been pure virtual, so I fixed that.
// Added ring member function IsZeroAddMul -- Anna says it improves performance
// noticeably.
// Changed "raw" from being a member function of elem, to being a normal
// function (following a brief discussion with Anna and Max).  Also it no
// longer requires the ring as argument -- any such checks must be explicit!
// The "raw" functions are inline.
//
// Revision 1.7  2001/12/07 18:19:43  abbott
// Changed names in accordance with new coding conventions;
// in particular ring::raw_elem became ring::RawValue.
// Added a few assertions.
//
// Revision 1.6  2001/11/23 20:50:31  abbott
// Added assignment to an elem from a machine integer (long).
// Had to make DMP a friend of class elem -- UNHAPPY!
//
// Revision 1.5  2001/11/16 18:44:15  bigatti
// added: std::
// for compatibility with gcc-3
//
// Revision 1.4  2001/11/07 20:51:22  abbott
// Changed ring::raw_elem to a union (from a void*) analogously to the change
// to PPmonoid::raw_elem.  Note that care will be needed to keep the field
// types synchronized with the types required by each concrete ring!
//
// Added an accessor function which allows access to the value field of
// an elem (but the caller must supply the ring, as a safety check).
// Not sure about how dirty this is.  Used in DMP.C (DMP::mul and DMP::div).
//
// Revision 1.3  2001/11/05 18:03:13  abbott
// Added a "copy constructor" which allows a raw_elem to be initialized
// from an elem (after checking that the rings are the same).
// Question: should this constuctor automatically apply homomorphisms?
//
// Revision 1.2  2001/10/31 20:40:45  abbott
// Some minor changes: biggest was declaration of +=, -=, *=, /=
// for elems.
//
// Revision 1.1  2001/10/05 12:44:13  abbott
// Initial revision
//

#endif
