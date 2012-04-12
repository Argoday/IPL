
#ifndef META__enable_if_H
#define META__enable_if_H

namespace Meta {


template <
	bool B,
	class T = void
> class enable_if_c {
	public:
		typedef T type;
};

template <
	class T
> class enable_if_c<false, T> {
};

template <
	class Cond,
	class T = void
> class enable_if
	: public enable_if_c<Cond::value, T>
{
};

}

#endif

