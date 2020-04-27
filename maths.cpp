#include "maths.h"
#include "couple.h"
#include <cmath>
#include <stdexcept>

namespace Maths {
		template<typename T> T abs(T t_num)
		{
				if (t_num < 0)
						return -t_num;
				return t_num;
		}

		bool abs(bool t_num) {
				return t_num;
		}

		long double floorFloat(long double t_num)
		{
				return floor(t_num);
		}

		long long gcd(long long a, long long b) {
				while (b != 0) {
						long long tmp = b;
						b = a%b;
						a = tmp;
				}
				return a;
		}

		long double nthRoot(long double t_base, int t_n) {
				if (t_n == 0)
						throw std::logic_error("Can't take root 0 of a number.");
				if (t_n == 1)
						return t_base;
				if (t_n < 0)
						return 1.0/nthRoot(t_base, -t_n);
				if (t_base < 0  && t_n%2==0)
						throw std::logic_error("Can't take even root of negative number.");
				long double baseX = t_base;
				for (int i = 0; i < 5; i++)
						baseX /= t_n;
				long double diff = 10;
				long double kthX;
				while (diff > 1e-9) {
						kthX = ((t_n - 1.0)*baseX + t_base/realPow(baseX, t_n-1))/(1.0*t_n);
						diff = abs(kthX-baseX);
						baseX = kthX;
				}
				return baseX;
		}

		Couple::pair<unsigned int, long long> intPow(long long t_base, long long t_power, long long mod) {
			if (t_power == 0)
				return {0 ,0};
			if (t_base == 0) {
				if (t_power < 0)
					throw std::logic_error("Cannot raise 0 to negative power.");
				return {0, 0};
			}
			if (t_power == 1) {
				return {0, t_base};
			}
			if (t_power < 1) {
				return {1, intPow(t_base, -t_power, mod).second};
			}
			if (t_base < 0 && t_power&1) {
				return {0, -intPow(-t_base, t_power, mod).second};
			}

			long long result = 1;
			while(t_power) {
				if (t_power&1) {
					result *= t_base;
					t_power--;
				}
				if (t_power > 0) {
					t_base *= t_base;
					t_power >>= 1;
				}
			}
			return {0, result};
		}

		long double realPow(long double t_base, long double t_power)
		{
				if (t_base < 0 && abs(t_power-floorFloat(t_power)) > eps)
						throw std::logic_error("Cannot raise negative number to real power.");
				if (abs(t_power - 0.0) < eps)
						return 1;
				if (abs(t_base - 0.0) < eps) {
						if (t_power < 0)
								throw std::logic_error("Cannot raise 0 to negative power.");
						return 0;
				}
				if (abs(t_power - 1.0) < eps)
						return t_base;
				if (t_power < 0)
						return 1.0/realPow(t_base, -t_power);
				if (t_power < 1) {
						int powerToRaise = t_power*1000;
						int rootToTake = 1000;
						int gcdToDiv = gcd(powerToRaise, rootToTake);
						return nthRoot(realPow(t_base, powerToRaise/gcdToDiv), rootToTake/gcdToDiv);
				}
				if (abs(t_power-floorFloat(t_power) > eps))
						return realPow(t_base, floorFloat(t_power))*realPow(t_base, t_power-floorFloat(t_power));
				if (t_base < 0 && abs(fmod(t_power, 2.0)-1.0) < eps)
						return -realPow(-t_base, t_power);
				long double result = 1;
				while (t_power > 0) {
						if (abs(fmod(t_power, 2.0)-0.0) < eps) {
								t_power /= 2.0;
								t_base *= t_base;
						} else {
								t_power -= 1.0;
								result *= t_base;
						}
				}
				return result;
		}

		long double ln(long double x) {
				if (x < 0 || abs(x-0.0) < eps)
						throw std::logic_error("Can't take logarithm of non-positive number.");
				long double taylorSeriesTerm = 1;
				long double taylorSeriesMult = (x-1)/(x+1);
				long double result = 1;
				long double diff = 10;
				long double divisor = 1;
				long double prev = result;
				while(diff > 1e-9) {
						taylorSeriesTerm *= taylorSeriesMult*taylorSeriesMult;
						divisor += 2;
						result += taylorSeriesTerm/divisor;
						diff = abs(result-prev);
						prev = result;
				}
				result *= 2.0*taylorSeriesMult;
				return result;
		}

		long double logarithm(long double a, long double x) {
				if (abs(a-1.0) < eps)
						throw std::logic_error("Can't take logarithm with base equal to 1.");
				if (a < 0 || abs(a-0.0) < eps)
						throw std::logic_error("Can't take logarithm with non-positive base.");
				return ln(x)/ln(a);
		}

		long double sine(long double a) {
				a = fmod(a, 2*pi);
				long double taylorSeriesTerm = a;
				long double result = a;
				long double diff = 10;
				long double prev = result;
				long double iter = 1;
				while(diff > 1e-9) {
						taylorSeriesTerm *= (-1.0*a*a)/(2*iter*(2*iter+1));
						result += taylorSeriesTerm;
						iter += 1.0;
						diff = abs(result-prev);
						prev = result;
				}
				return result;
		}

		long double cosine(long double a) {
				a = fmod(a, 2*pi);
				long double taylorSeriesTerm = 1;
				long double result = 1;
				long double diff = 10;
				long double prev = result;
				long double iter = 1;
				while(diff > 1e-9) {
						taylorSeriesTerm *= (-1.0*a*a)/(2*iter*(2*iter-1));
						result += taylorSeriesTerm;
						diff = abs(result-prev);
						prev = result;
						iter += 1.0;
				}
				return result;
		}

		long double tg(long double a) {
				long double cos = cosine(a);
				if (abs(cos - 0) < eps)
						throw std::logic_error("Can't take tg of PI/2 or 3*PI/2");
				return sine(a)/cosine(a);
		}

		long double ctg(long double a) {
				long double sin = sine(a);
				if (abs(sin - 0) < eps)
						throw std::logic_error("Can't take tg of PI/2 or 3*PI/2");
				return cosine(a)/sine(a);
		}

		long double arcsine(long double a) {
				if (abs(a) > 1)
						throw std::logic_error("Can't get arcsine of number not in the range [-1;+1].");
				long double result = a;
				long double taylorSeriesTerm = 1;
				long double taylorTermAPower = 1;
				long double diff = 10;
				long double prev = result;
				long double iter = 1;
				while (diff > 1e-9) {
						taylorSeriesTerm *= (iter*2*(iter*2-1))/(4*iter*iter);
						taylorTermAPower *= a*a;
						result += (taylorSeriesTerm*taylorTermAPower*a)/(2*iter+1);
						iter += 1.0;
						diff = abs(result-prev);
						prev = result;
				}
				return result;
		}

		long double arccos(long double a) {
				if (abs(a) > 1)
						throw std::logic_error("Can't get arccos of number not in the range [-1;+1].");
				return (pi/2 - arcsine(a));
		}

		long double arctg(long double a) {
				bool reversed = 0;
				if (abs(a) > 1) {
						a = 1.0/a;
						reversed = true;
				}
				long double taylorSeriesTerm = 1;
				long double taylorTermAPower = 1;
				long double result = a;
				long double prev = result;
				long double diff = 10;
				long double iter = 1;
				while (diff > 1e-9) {
						taylorSeriesTerm *= -1;
						taylorTermAPower *= a*a;
						result += (taylorSeriesTerm*taylorTermAPower*a)/(2*iter+1);
						iter += 1.0;
						diff = abs(result-prev);
						prev = result;
				}
				if (reversed)
						return (pi/2.0-result);
				return result;
		}

		long double arcctg(long double a) {
				return (pi/2.0-arctg(a));
		}

}
