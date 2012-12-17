/**
 * @file test_full_reduce.cpp
 *
 * Test of full reduction on matrices
 * 
 * @author Dahua Lin 
 */

#include "test_base.h"
#include <light_mat/matrix/matrix_classes.h>
#include <light_mat/mateval/mat_reduce.h>
#include <cstdlib>

using namespace lmat;
using namespace lmat::test;

inline double randunif()
{
	return (double)std::rand() / double(RAND_MAX);
}

template<class Mat, typename T>
void fill_rand(IRegularMatrix<Mat, T>& mat)
{
	for (index_t j = 0; j < mat.ncolumns(); ++j)
	{
		for (index_t i = 0; i < mat.nrows(); ++i)
		{
			mat(i, j) = randunif();
		}
	}
}

const index_t max_len = 48;

SIMPLE_CASE( full_reduce, sum )
{
	dense_col<double> s(max_len);
	fill_rand(s);

	std::printf("\n");
	for (index_t k = 0; k <= max_len; ++k)
	{
		double r0 = 0;
		for (index_t i = 0; i < k; ++i) r0 += s[i];

		double r = sum(s(range(0, k)));
		ASSERT_APPROX(r, r0, 1.0e-12);
	}
}


BEGIN_TPACK( full_reduce )
	ADD_SIMPLE_CASE( full_reduce, sum )
END_TPACK


BEGIN_MAIN_SUITE
	ADD_TPACK( full_reduce )
END_MAIN_SUITE
