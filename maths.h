#ifndef MATHS_H
#define MATHS_H

#include "couple.h"

namespace Maths {
	const long double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
	const long double expo = 2.718281828459045235360287471352662497757247093699959574966967627724076630353;
	const long double eps = 1e-9;
	const long double calculationEps = 1e-9;

	long double realPow(long double value, long double exponent);

	Couple::pair<unsigned int, long long> intPow(long long value, long long exponent, long long mod = 9223372036854775807);

	unsigned int roundToNextPowerOfTwo(unsigned int value);

	bool abs(bool value);

	long double floorFloat(long double value);

	long long gcd(long long a, long long b);

	long double nthRoot(long double value, int indexOfRoot);

	long double ln(long double value);

	long double logarithm(long double base, long double value);

	long double sine(long double value);

	long double cosine(long double value);

	long double tg(long double value);

	long double ctg(long double value);

	long double arcsine(long double value);

	long double arccos(long double value);

	long double arctg(long double value);

	long double arcctg(long double value);
}
#endif // MATHS_H
