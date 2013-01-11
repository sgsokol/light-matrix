/**
 * @file avx_math.h
 *
 * @brief Math functions on AVX packs
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef LIGHTMAT_AVX_MATH_H_
#define LIGHTMAT_AVX_MATH_H_

#include <light_mat/math/avx_ops.h>
#include "internal/avx_math_emulate.h"

#if defined(LMAT_USE_INTEL_SVML) && defined(LMAT_USE_AMD_LIBM)
#error SVML and LIBM cannot be used simultaneously.
#endif


#ifdef LMAT_USE_INTEL_SVML

// External function prototypes

#define LMAT_SVML_AVX_F( name ) __svml_##name##f8
#define LMAT_SVML_AVX_D( name ) __svml_##name##4

#define LMAT_DECLARE_SVML_AVX_EXTERN1( name ) \
	__m256  LMAT_SVML_AVX_F(name)( __m256 ); \
	__m256d LMAT_SVML_AVX_D(name)( __m256d );

#define LMAT_DECLARE_SVML_AVX_EXTERN2( name ) \
	__m256  LMAT_SVML_AVX_F(name)( __m256,  __m256  ); \
	__m256d LMAT_SVML_AVX_D(name)( __m256d, __m256d );

#define LMAT_AVX_F( name ) LMAT_SVML_AVX_F( name )
#define LMAT_AVX_D( name ) LMAT_SVML_AVX_D( name )

extern "C"
{
	// C++ 03

#define LMAT_HAS_EXTERN_AVX_POW
#define LMAT_HAS_EXTERN_AVX_EXPLOG
#define LMAT_HAS_EXTERN_AVX_TRI
#define LMAT_HAS_EXTERN_AVX_ARCTRI
#define LMAT_HAS_EXTERN_AVX_HYPERB

	LMAT_DECLARE_SVML_AVX_EXTERN2( pow )
	LMAT_DECLARE_SVML_AVX_EXTERN1( exp )
	LMAT_DECLARE_SVML_AVX_EXTERN1( log )
	LMAT_DECLARE_SVML_AVX_EXTERN1( log10 )

	LMAT_DECLARE_SVML_AVX_EXTERN1( sin )
	LMAT_DECLARE_SVML_AVX_EXTERN1( cos )
	LMAT_DECLARE_SVML_AVX_EXTERN1( tan )

	LMAT_DECLARE_SVML_AVX_EXTERN1( asin )
	LMAT_DECLARE_SVML_AVX_EXTERN1( acos )
	LMAT_DECLARE_SVML_AVX_EXTERN1( atan )
	LMAT_DECLARE_SVML_AVX_EXTERN2( atan2 )

	LMAT_DECLARE_SVML_AVX_EXTERN1( sinh )
	LMAT_DECLARE_SVML_AVX_EXTERN1( cosh )
	LMAT_DECLARE_SVML_AVX_EXTERN1( tanh )

	// C++ 11

#define LMAT_HAS_EXTERN_AVX_HYPOT
#define LMAT_HAS_EXTERN_AVX_CBRT
#define LMAT_HAS_EXTERN_AVX_EXPLOG2
#define LMAT_HAS_EXTERN_AVX_EXPLOG_EX
#define LMAT_HAS_EXTERN_AVX_ARCHYPERB
#define LMAT_HAS_EXTERN_AVX_ERF
// #define LMAT_HAS_EXTERN_AVX_GAMMA

	LMAT_DECLARE_SVML_AVX_EXTERN2( hypot )
	LMAT_DECLARE_SVML_AVX_EXTERN1( cbrt )

	LMAT_DECLARE_SVML_AVX_EXTERN1( exp2 )
	LMAT_DECLARE_SVML_AVX_EXTERN1( log2 )
	LMAT_DECLARE_SVML_AVX_EXTERN1( expm1 )
	LMAT_DECLARE_SVML_AVX_EXTERN1( log1p )

	LMAT_DECLARE_SVML_AVX_EXTERN1( asinh )
	LMAT_DECLARE_SVML_AVX_EXTERN1( acosh )
	LMAT_DECLARE_SVML_AVX_EXTERN1( atanh )

	LMAT_DECLARE_SVML_AVX_EXTERN1( erf )
	LMAT_DECLARE_SVML_AVX_EXTERN1( erfc )

	// other functions

	LMAT_DECLARE_SVML_AVX_EXTERN1( exp10 )
	LMAT_DECLARE_SVML_AVX_EXTERN1( cdfnorm )
	LMAT_DECLARE_SVML_AVX_EXTERN1( cdfnorminv )

}

#endif // has intel SVML

#define LMAT_ACTIVATE_AVX_EXTERN_1( Name ) \
	LMAT_ENSURE_INLINE \
	inline avx_f32pk Name( const avx_f32pk& a ) { \
		return LMAT_AVX_F(Name)(a); } \
	LMAT_ENSURE_INLINE \
	inline avx_f64pk Name( const avx_f64pk& a ) { \
		return LMAT_AVX_D(Name)(a); }

#define LMAT_ACTIVATE_AVX_EXTERN_2( Name ) \
	LMAT_ENSURE_INLINE \
	inline avx_f32pk Name( const avx_f32pk& a, const avx_f32pk& b ) { \
		return LMAT_AVX_F(Name)(a, b); } \
	LMAT_ENSURE_INLINE \
	inline avx_f64pk Name( const avx_f64pk& a, const avx_f64pk& b ) { \
		return LMAT_AVX_D(Name)(a, b); }


namespace lmat { namespace meta {

#ifdef LMAT_HAS_EXTERN_AVX_POW
	LMAT_DEFINE_HAS_AVX_SUPPORT( pow_ )
#endif

#ifdef LMAT_HAS_EXTERN_AVX_EXPLOG
	LMAT_DEFINE_HAS_AVX_SUPPORT( exp_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( log_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( log10_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( xlogy_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( xlogx_ )
#endif

#ifdef LMAT_HAS_EXTERN_AVX_TRI
	LMAT_DEFINE_HAS_AVX_SUPPORT( sin_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( cos_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( tan_ )
#endif

#ifdef LMAT_HAS_EXTERN_AVX_ARCTRI
	LMAT_DEFINE_HAS_AVX_SUPPORT( asin_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( acos_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( atan_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( atan2_ )
#endif

#ifdef LMAT_HAS_EXTERN_AVX_HYPERB
	LMAT_DEFINE_HAS_AVX_SUPPORT( sinh_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( cosh_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( tanh_ )
#endif

#ifdef LMAT_HAS_CXX11_MATH

#ifdef LMAT_HAS_EXTERN_AVX_HYPOT
	LMAT_DEFINE_HAS_AVX_SUPPORT( hypot_ )
#endif

#ifdef LMAT_HAS_EXTERN_AVX_CBRT
	LMAT_DEFINE_HAS_AVX_SUPPORT( cbrt_ )
#endif

#ifdef LMAT_HAS_EXTERN_AVX_EXPLOG2
	LMAT_DEFINE_HAS_AVX_SUPPORT( exp2_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( log2_ )
#endif

#ifdef LMAT_HAS_EXTERN_AVX_EXPLOG_EX
	LMAT_DEFINE_HAS_AVX_SUPPORT( expm1_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( log1p_ )
#endif

#ifdef LMAT_HAS_EXTERN_AVX_ARCHYPERB
	LMAT_DEFINE_HAS_AVX_SUPPORT( asinh_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( acosh_ )
	LMAT_DEFINE_HAS_AVX_SUPPORT( atanh_ )
#endif

#endif // has C++ 11 math
} }


namespace lmat { namespace math {

	// C++ 03

#ifdef LMAT_HAS_EXTERN_AVX_POW
	LMAT_ACTIVATE_AVX_EXTERN_2( pow )
#elif (defined(LMAT_ENABLE_SIMD_EMULATE))
	LMAT_ACTIVATE_AVX_MATH_EMULATE_2( pow )
#endif


#ifdef LMAT_HAS_EXTERN_AVX_EXPLOG
	LMAT_ACTIVATE_AVX_EXTERN_1( exp )
	LMAT_ACTIVATE_AVX_EXTERN_1( log )
	LMAT_ACTIVATE_AVX_EXTERN_1( log10 )

	LMAT_ENSURE_INLINE
	inline avx_f32pk xlogy(const avx_f32pk& a, const avx_f32pk& b)
	{
		avx_f32pk z = avx_f32pk::zeros();
		return cond(a > z, log(b), z) * a;
	}

	LMAT_ENSURE_INLINE
	inline avx_f64pk xlogy(const avx_f64pk& a, const avx_f64pk& b)
	{
		avx_f64pk z = avx_f64pk::zeros();
		return cond(a > z, log(b), z) * a;
	}

	LMAT_ENSURE_INLINE
	inline avx_f32pk xlogx(const avx_f32pk& a)
	{
		return xlogy(a, a);
	}

	LMAT_ENSURE_INLINE
	inline avx_f64pk xlogx(const avx_f64pk& a)
	{
		return xlogy(a, a);
	}


#elif (defined(LMAT_ENABLE_SIMD_EMULATE))
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( exp )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( log )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( log10 )
#endif


#ifdef LMAT_HAS_EXTERN_AVX_TRI
	LMAT_ACTIVATE_AVX_EXTERN_1( sin )
	LMAT_ACTIVATE_AVX_EXTERN_1( cos )
	LMAT_ACTIVATE_AVX_EXTERN_1( tan )
#elif (defined(LMAT_ENABLE_SIMD_EMULATE))
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( sin )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( cos )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( tan )
#endif


#ifdef LMAT_HAS_EXTERN_AVX_ARCTRI
	LMAT_ACTIVATE_AVX_EXTERN_1( asin )
	LMAT_ACTIVATE_AVX_EXTERN_1( acos )
	LMAT_ACTIVATE_AVX_EXTERN_1( atan )
	LMAT_ACTIVATE_AVX_EXTERN_2( atan2 )
#elif (defined(LMAT_ENABLE_SIMD_EMULATE))
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( asin )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( acos )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( atan )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_2( atan2 )
#endif


#ifdef LMAT_HAS_EXTERN_AVX_HYPERB
	LMAT_ACTIVATE_AVX_EXTERN_1( sinh )
	LMAT_ACTIVATE_AVX_EXTERN_1( cosh )
	LMAT_ACTIVATE_AVX_EXTERN_1( tanh )
#elif (defined(LMAT_ENABLE_SIMD_EMULATE))
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( sinh )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( cosh )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( tanh )
#endif

	// C++ 11

#ifdef LMAT_HAS_CXX11_MATH

#ifdef LMAT_HAS_EXTERN_AVX_HYPOT
	LMAT_ACTIVATE_AVX_EXTERN_2( hypot )
#elif (defined(LMAT_ENABLE_SIMD_EMULATE))
	LMAT_ACTIVATE_AVX_MATH_EMULATE_2( hypot )
#endif


#ifdef LMAT_HAS_EXTERN_AVX_CBRT
	LMAT_ACTIVATE_AVX_EXTERN_1( cbrt )
#elif (defined(LMAT_ENABLE_SIMD_EMULATE))
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( cbrt )
#endif


#ifdef LMAT_HAS_EXTERN_AVX_EXPLOG2
	LMAT_ACTIVATE_AVX_EXTERN_1( exp2 )
	LMAT_ACTIVATE_AVX_EXTERN_1( log2 )
#elif (defined(LMAT_ENABLE_SIMD_EMULATE))
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( exp2 )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( log2 )
#endif


#ifdef LMAT_HAS_EXTERN_AVX_EXPLOG_EX
	LMAT_ACTIVATE_AVX_EXTERN_1( expm1 )
	LMAT_ACTIVATE_AVX_EXTERN_1( log1p )
#elif (defined(LMAT_ENABLE_SIMD_EMULATE))
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( expm1 )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( log1p )
#endif


#ifdef LMAT_HAS_EXTERN_AVX_ARCHYPERB
	LMAT_ACTIVATE_AVX_EXTERN_1( asinh )
	LMAT_ACTIVATE_AVX_EXTERN_1( acosh )
	LMAT_ACTIVATE_AVX_EXTERN_1( atanh )
#elif (defined(LMAT_ENABLE_SIMD_EMULATE))
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( asinh )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( acosh )
	LMAT_ACTIVATE_AVX_MATH_EMULATE_1( atanh )
#endif


#endif // has C++11 math

} }


#endif /* AVX_MATH_H_ */
