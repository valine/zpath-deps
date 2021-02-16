/* $Id: parigen.h 11744 2009-06-03 12:39:15Z bill $

Copyright (C) 2000  The PARI group.

This file is part of the PARI/GP package.

PARI/GP is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation. It is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY WHATSOEVER.

Check the License for details. You should have received a copy of it, along
with the package; see the file 'COPYING'. If not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */

/* This file defines the parameters of the GEN type               */

typedef long *GEN;
typedef unsigned long pari_ulong;
#define ulong pari_ulong

#undef ULONG_MAX
#undef LONG_MAX

#ifdef LONG_IS_64BIT
#  define BITS_IN_LONG 64
#  define TWOPOTBITS_IN_LONG 6
#  define LONG_MAX (9223372036854775807L) /* 2^63-1 */
#  define SMALL_ULONG(p) ((ulong)p <= 3037000493UL)
#else
#  define BITS_IN_LONG 32
#  define TWOPOTBITS_IN_LONG 5
#  define LONG_MAX (2147483647L) /* 2^31-1 */
#  define SMALL_ULONG(p) ((ulong)p <= 46337UL) /* 2p^2 < 2^BITS_IN_LONG */
#endif
#define ULONG_MAX (~0x0UL)

#define DEFAULTPREC    (2 + (long)(8/sizeof(long)))
#define MEDDEFAULTPREC (2 + (long)(16/sizeof(long)))
#define BIGDEFAULTPREC (2 + (long)(24/sizeof(long)))
#define HIGHBIT (1UL << (BITS_IN_LONG-1))
#define BITS_IN_HALFULONG (BITS_IN_LONG>>1)

#define LOWMASK ((1UL<<BITS_IN_HALFULONG) - 1)
#define HIGHMASK (~LOWMASK)

#define HIGHWORD(a) ((a) >> BITS_IN_HALFULONG)
#define LOWWORD(a) ((a) & LOWMASK)

/* Order of bits in codewords:
 *  x[0]       TYPBITS, CLONEBIT, LGBITS
 *  x[1].real  SIGNBITS, EXPOBITS
 *       int   SIGNBITS, LGBITS
 *       pol   SIGNBITS, VARNBITS
 *       ser   SIGNBITS, VARNBITS, VALPBITS
 *       padic VALPBITS, PRECPBITS */
#define TYPnumBITS   7
#define SIGNnumBITS  2

#ifdef LONG_IS_64BIT
#  define VARNnumBITS 16 /* otherwise MAXVARN too large */
#else
#  define VARNnumBITS 14
#endif

/* no user serviceable parts below :-) */
#define   LGnumBITS (BITS_IN_LONG - 1 - TYPnumBITS)
#define VALPnumBITS (BITS_IN_LONG - SIGNnumBITS - VARNnumBITS)
#define EXPOnumBITS (BITS_IN_LONG - SIGNnumBITS)
#define PRECPSHIFT VALPnumBITS
#define  VARNSHIFT VALPnumBITS
#define   TYPSHIFT (BITS_IN_LONG - TYPnumBITS)
#define  SIGNSHIFT (BITS_IN_LONG - SIGNnumBITS)

#define EXPOBITS    ((1UL<<EXPOnumBITS)-1)
#define SIGNBITS    (~((1UL<<SIGNSHIFT) - 1))
#define  TYPBITS    (~((1UL<< TYPSHIFT) - 1))
#define PRECPBITS   (~VALPBITS)
#define LGBITS      ((1UL<<LGnumBITS)-1)
#define VALPBITS    ((1UL<<VALPnumBITS)-1)
#define VARNBITS    (MAXVARN<<VARNSHIFT)
#define MAXVARN     ((1UL<<VARNnumBITS)-1)
#define NO_VARIABLE (2147483647) /* > MAXVARN */

#define HIGHEXPOBIT (1UL<<(EXPOnumBITS-1))
#define HIGHVALPBIT (1UL<<(VALPnumBITS-1))
#define CLONEBIT    (1UL<<LGnumBITS)

#define evaltyp(x)    (((ulong)(x)) << TYPSHIFT)
#define evalvarn(x)   (((ulong)(x)) << VARNSHIFT)
#define evalsigne(x)  ((ulong)(((long)(x)) << SIGNSHIFT))
#define evalprecp(x)   (((long)(x)) << PRECPSHIFT)
#define _evalexpo(x)  (HIGHEXPOBIT + (x))
#define _evalvalp(x)  (HIGHVALPBIT + (x))
#define evallgefint(x)  (x)
#define evallgeflist(x) (x)
#define _evallg(x)    (x)

#define typ(x)        ((long)((((ulong*)(x))[0]) >> TYPSHIFT))
#define settyp(x,s)   (((ulong*)(x))[0]=\
                        (((ulong*)(x))[0]&(~TYPBITS)) | evaltyp(s))

#define isclone(x)    (((ulong*) (x))[0] & CLONEBIT)
#define setisclone(x) (((ulong*) (x))[0] |= CLONEBIT)
#define unsetisclone(x) (((ulong*) (x))[0] &= (~CLONEBIT))

#define lg(x)         ((long)(((ulong*)(x))[0] & LGBITS))
#define setlg(x,s)    (((ulong*)(x))[0]=\
                        (((ulong*)(x))[0]&(~LGBITS)) | evallg(s))

#define signe(x)      ((((long*)(x))[1]) >> SIGNSHIFT)
#define setsigne(x,s) (((ulong*)(x))[1]=\
                        (((ulong*)(x))[1]&(~SIGNBITS)) | (ulong)evalsigne(s))

#define lgefint(x)      ((long)(((ulong*)(x))[1] & LGBITS))
#define setlgefint(x,s) (((ulong*)(x))[1]=\
                          (((ulong*)(x))[1]&(~LGBITS)) | (ulong)evallgefint(s))

#define expo(x)       ((long) ((((ulong*)(x))[1] & EXPOBITS) - HIGHEXPOBIT))
#define setexpo(x,s)  (((ulong*)(x))[1]=\
                       (((ulong*)(x))[1]&(~EXPOBITS)) | (ulong)evalexpo(s))

#define valp(x)       ((long) ((((ulong*)(x))[1] & VALPBITS) - HIGHVALPBIT))
#define setvalp(x,s)  (((ulong*)(x))[1]=\
                       (((ulong*)(x))[1]&(~VALPBITS)) | (ulong)evalvalp(s))

#define precp(x)      ((long) (((ulong*)(x))[1] >> PRECPSHIFT))
#define setprecp(x,s) (((ulong*)(x))[1]=\
                       (((ulong*)(x))[1]&(~PRECPBITS)) | (ulong)evalprecp(s))

#define varn(x)       ((long)((((ulong*)(x))[1]&VARNBITS) >> VARNSHIFT))
#define setvarn(x,s)  (((ulong*)(x))[1]=\
                       (((ulong*)(x))[1]&(~VARNBITS)) | (ulong)evalvarn(s))

#define varncmp(x,y)  ((x)-(y))

/* t_LIST */
#define list_nmax(x) ((GEN)x)[1]
#define list_data(x) ((GEN*)x)[2]

/* DO NOT REORDER THESE
 * actual values can be changed. Adapt lontyp in gen2.c */
enum {
  t_INT    =  1,
  t_REAL   =  2,
  t_INTMOD =  3,
  t_FRAC   =  4,
  t_FFELT  =  5,
  t_COMPLEX=  6,
  t_PADIC  =  7,
  t_QUAD   =  8,
  t_POLMOD =  9,
  t_POL    =  10,
  t_SER    =  11,
  t_RFRAC  =  13,
  t_QFR    =  15,
  t_QFI    =  16,
  t_VEC    =  17,
  t_COL    =  18,
  t_MAT    =  19,
  t_LIST   =  20,
  t_STR    =  21,
  t_VECSMALL= 22,
  t_CLOSURE = 23
};
