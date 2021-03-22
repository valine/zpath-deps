// ==========================================================================
// $Source: /var/lib/cvs/Givaro/src/kernel/gmp++/gmp++_int_add.C,v $
// Copyright(c)'1994-2009 by The Givaro group
// This file is part of Givaro.
// Givaro is governed by the CeCILL-B license under French law
// and abiding by the rules of distribution of free software.
// see the COPYRIGHT file for more details.
// Authors: B. Boyer
// $Id: gmp++_int_random.C,v 1.5 2011-09-16 12:09:37 bboyer Exp $
// ==========================================================================

// #include "gmp++/gmp++.h"
/** @file gmp++/gmp++_int_rand.inl
 * randing stuff.
 */

#ifndef __GIVARO_gmpxx_gmpxx_int_rand_INL
#define __GIVARO_gmpxx_gmpxx_int_rand_INL

#include <givaro/givtimer.h>
#include <assert.h>

namespace Givaro {
	//-----------------------------------------------------
	//----------------------- Random integers -------------
	//-----------------------------------------------------

	/* ********************** */
	/* seeding, initialising  */
	/* ********************** */
#ifdef __GMP_PLUSPLUS__
	gmp_randclass& Integer::randstate()
	{
		static gmp_randclass randstate(gmp_randinit_default);
		return static_cast<gmp_randclass&>(randstate);
	}
#else
#error "not implemented"
#error "please include gmp++/gmp++.h very high in your inlcude list"
#endif

	inline void Integer::seeding(long unsigned int s)
	{
		Integer::randstate().seed(s) ;
	}

	void Integer::seeding(Integer  s)
	{
		Integer::randstate().seed((mpz_class) (mpz_srcptr) &(s.gmp_rep) ) ;
	}

	void Integer::seeding()
	{
		Integer::seeding( (long unsigned) BaseTimer::seed() );
	}


	// BB : good seeding but not so efficient...
	bool Integer::RandBool()
	{
		if (Integer::random(1UL)) return true;
		else return false ;
	}


	/* ****************************** */
	/*  random number smaller than m  */
	/* ****************************** */

#ifdef __GMP_PLUSPLUS__
	//! returns a random integer \p r in the intervall <code>[[0, m-1]]</code>
	template<bool ALWAYSPOSITIVE>
	Integer& Integer::random_lessthan (Integer& r, const Integer & m)
	{
		mpz_set( (mpz_ptr) &(r.gmp_rep) ,
			 ( (mpz_class)Integer::randstate().get_z_range((mpz_class) (mpz_srcptr) &(m.gmp_rep)) ).get_mpz_t() );
		if(!ALWAYSPOSITIVE) if (Integer::RandBool()) Integer::negin(r);
		return r;
	}
#else
	//! returns a random integer \p r in the intervall <code>[[0, m-1]]</code>
	template<bool ALWAYSPOSITIVE>
	Integer& Integer::random_lessthan (Integer& r, const Integer & m)
	{
		mpz_urandomm((mpz_ptr) &(r.gmp_rep),Integer::randstate(),(mpz_srcptr)&(m.gmp_rep));
		if(!ALWAYSPOSITIVE) if (Integer::RandBool()) Integer::negin(r);
		return r;
	}
#endif
	Integer& Integer::random_lessthan (Integer& r, const Integer & m)
	{
		return random_lessthan<true>(r,m);
	}
	Integer& Integer::random_lessthan_2exp (Integer& r, const long unsigned int & m)
	{
		return random_lessthan_2exp<true>(r,m);
	}
	Integer Integer::random_lessthan_2exp (const long unsigned int & m)
	{
		return random_lessthan_2exp<true>(m);
	}
	Integer& Integer::random_lessthan (Integer& r, const long unsigned int & m)
	{
		return random_lessthan<true>(r,m);
	}

	template<class T>
	Integer Integer::random_lessthan (const T & m)
	{
		return random_lessthan<true>(m);
	}

	/* ******************************** */
	/*  random number smaller than 2^m  */
	/* ******************************** */

#ifdef __GMP_PLUSPLUS__
	//! returns a random integer \p r of at most \p m bits
	template<bool ALWAYSPOSITIVE>
	Integer& Integer::random_lessthan_2exp (Integer& r, const long unsigned int & m)
	{
		mpz_set( (mpz_ptr) &(r.gmp_rep) , ((mpz_class)Integer::randstate().get_z_bits(m)).get_mpz_t() );
		if(!ALWAYSPOSITIVE) {
			if (Integer::RandBool()) Integer::negin(r);
		}
		return r;
	}
#else
	//! returns a random integer \p r of at most \p m bits
	template<bool ALWAYSPOSITIVE>
	Integer& Integer::random_lessthan_2exp (Integer& r, const long unsigned int & m)
	{
		mpz_urandomb((mpz_ptr) &(r.gmp_rep),Integer::randstate(),m) ;
		if(!ALWAYSPOSITIVE) if (Integer::RandBool()) Integer::negin(r);
		return r;
	}
#endif

	template<bool ALWAYSPOSITIVE>
	Integer Integer::random_lessthan_2exp (const long unsigned int & m)
	{
		Integer r ;
		random_lessthan_2exp<ALWAYSPOSITIVE>(r,m);
		return r;
	}

	/* synonyms */
	template<bool ALWAYSPOSITIVE>
	Integer& Integer::random_lessthan (Integer& r, const long unsigned int & m)
	{
		return Integer::random_lessthan_2exp<ALWAYSPOSITIVE>(r,m);
	}

	template<bool ALWAYSPOSITIVE,class T>
	Integer Integer::random_lessthan (const T & m)
	{
		Integer res ;
		return Integer::random_lessthan<ALWAYSPOSITIVE>(res,m);
	}

	/* ********************************* */
	/*  random number of same size as s  */
	/* ********************************* */

	//! returns a reference to a random number \p r of the size of \p s, exactly.
	template<bool ALWAYSPOSITIVE>
	Integer& Integer::random_exact (Integer& r, const Integer & s)
	{
		size_t t = s.bitsize() ;
		Integer::random_exact_2exp<ALWAYSPOSITIVE>(r,t);
		return r;
	}
	Integer& Integer::random_exact (Integer& r, const long unsigned int & m)
	{
		return Integer::random_exact<true>(r,m);
	}
	Integer& Integer::random_exact (Integer& r, const Integer & s)
	{
		return Integer::random_exact<true>(r,s);
	}
	template<bool ALWAYSPOSITIVE,class T>
	Integer& Integer::random_exact (Integer& r, const T & m)
	{
		return Integer::random_exact<ALWAYSPOSITIVE>(r,static_cast<long unsigned int>(m));
	}
	template<class T>
	Integer& Integer::random_exact (Integer& r, const T & m)
	{
		return Integer::random_exact(r,static_cast<long unsigned int>(m));
	}

	template<class T>
	Integer Integer::random_exact (const T & s)
	{
		return Integer::random_exact<true>(s) ;
	}



	/* ************************* */
	/*  random number of size m  */
	/* ************************* */

	//! returns a reference to a random number \p r of the size \p m bits, exactly.
	template<bool ALWAYSPOSITIVE>
	Integer& Integer::random_exact_2exp (Integer& r, const long unsigned int & m)
	{
		if (m) random_lessthan_2exp<true>(r,m-1);
		mpz_setbit( (mpz_ptr) &(r.gmp_rep) , m-1);
		if(!ALWAYSPOSITIVE) if (Integer::RandBool()) Integer::negin(r);
		return r;
	}

	Integer& Integer::random_exact_2exp (Integer& r, const long unsigned int & m)
	{
		return Integer::random_exact<true>(r,m);
	}
	// synonym
	template<bool ALWAYSPOSITIVE>
	Integer& Integer::random_exact (Integer& r, const long unsigned int & m)
	{
		return Integer::random_exact_2exp<ALWAYSPOSITIVE>(r,m) ;
	}

	template<bool ALWAYSPOSITIVE,class T>
	Integer Integer::random_exact (const T & s)
	{
		Integer res ;
		return random_exact<ALWAYSPOSITIVE>(res,s);
	}

	/* **************************** */
	/*  random number in [[m,M-1]]  */
	/* **************************** */

	Integer& Integer::random_between (Integer& r, const Integer& m, const Integer&M)
	{
		assert(M > m);
		random_lessthan(r,Integer(M-m));
		r += m ;
		return (r);
	}

	Integer Integer::random_between (const Integer& m, const Integer &M)
	{
		Integer r ;
		return random_between(r,m,M);
	}


	template<class R>
	Integer Integer::random_between (const R & m, const R & M)
	{
		return Integer::random_between(static_cast<long unsigned int>(m),
					       static_cast<long unsigned int>(M));
	}
	template<class R>
	Integer & Integer::random_between (Integer &r, const R & m, const R & M)
	{
		return Integer::random_between(r,static_cast<long unsigned int>(m),
					       static_cast<long unsigned int>(M));
	}


	/* ******************************** */
	/*  random number in [[2^m,2^M-1]]  */
	/* ******************************** */
	// todo : template<bool ALWAYSPOSITIVE, bool V>
	Integer& Integer::random_between_2exp (Integer& r, const long unsigned int& m, const long unsigned int &M)
	{
		assert(M > m);
		r = nonzerorandom((long unsigned int)M-m);
		Integer r1 = random_lessthan_2exp(m);
		r <<= m ;
		r+= r1 ;
		return (r);
	}

	Integer Integer::random_between_2exp (const long unsigned int & m, const long unsigned int &M)
	{
		Integer r ;
		return random_between_2exp(r,m,M);
	}

	// synonym.
	Integer Integer::random_between (const long unsigned int & m, const long unsigned int &M)
	{
		return random_between_2exp(m,M) ;
	}


	Integer& Integer::random_between (Integer& r, const long unsigned int& m, const long unsigned int &M)
	{
		return random_between_2exp(r,m,M);
	}
	/* **************/
	/*  short hand  */
	/* **************/

	//! returns a random integer less than...
	template<bool ALWAYSPOSITIVE,class T>
	Integer& Integer::random (Integer& r, const T & m)
	{
		return Integer::random_lessthan<ALWAYSPOSITIVE>(r,m) ;
	}

	//! returns a random integer less than...
	template<bool ALWAYSPOSITIVE,class T>
	Integer Integer::random(const T & sz)
	{
		return Integer::random_lessthan<ALWAYSPOSITIVE,T>(sz);
	}

	Integer Integer::random()
	{
		return Integer::random(sizeof(mp_limb_t)*8) ;
	}
	template<bool ALWAYSPOSITIVE>
	Integer Integer::random()
	{
		Integer rez = Integer::random(sizeof(mp_limb_t)*8) ;
		if (!ALWAYSPOSITIVE) if (Integer::RandBool()) negin(rez);
		return rez;
	}

	template<class T>
	Integer& Integer::random (Integer& r, const T & m)
	{
		return Integer::random<true,T>(r,m);
	}

	template<class T>
	Integer Integer::random(const T & sz)
	{
		return Integer::random<true>(sz);
	}

	/* *******************/
	/*  Non Zero random  */
	/* *******************/

	template<bool ALWAYSPOSITIVE, class T>
	Integer Integer::nonzerorandom(const T & sz)
	{
		Integer r;
		while(isZero(Integer::random<ALWAYSPOSITIVE,T>(r, sz) )) {} ;
		return r;
	}

	// BB: It's also 1+random(sz-1)...

	template<bool ALWAYSPOSITIVE, class T>
	Integer& Integer::nonzerorandom (Integer& r, const T& size)
	{
		while (isZero(Integer::random<ALWAYSPOSITIVE,T>(r,size))) {} ;
		return r;
	}

	template<class T>
	Integer  Integer::nonzerorandom(const T & sz)
	{
		return  Integer::nonzerorandom<true>(sz);
	}
	template<class T>
	Integer&  Integer::nonzerorandom (Integer& r, const T& size)
	{
		return  Integer::nonzerorandom<true>(r,size);
	}
	Integer  Integer::nonzerorandom()
	{
		Integer rez = Integer::nonzerorandom(sizeof(mp_limb_t)*8) ;
		// if (!ALWAYSPOSITIVE) if (Integer::RandBool()) negin(rez);
		return rez;
	}


}

#endif // __GIVARO_gmpxx_gmpxx_int_rand_INL

// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s:syntax=cpp.doxygen
