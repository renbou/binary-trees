#ifndef COUPLE_H
#define COUPLE_H

namespace Couple {
	template<typename T1, typename T2>
	class pair {
	public:
		T1 first;
		T2 second;

		pair()
				: first(T1()),
				  second(T2()) {}

		pair(T1 t_first, T2 t_second)
				: first(t_first),
				  second(t_second) {}

	};

	template<typename T1, typename T2, typename T3>
	class triple {
	public:
		T1 first;
		T2 second;
		T3 third;

		triple()
				: first(T1()),
				  second(T2()),
				  third(T3()) {}

		triple(T1 t_first, T2 t_second, T3 t_third)
				: first(t_first),
				  second(t_second),
				  third(t_third) {}
	};
}

#endif //COUPLE_H
