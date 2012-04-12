
#ifndef META__disable_if_H
#define META__disable_if_H

namespace Meta {


template <
	bool B,
	class T = void
> class disable_if_c {
	public:
		typedef T type;
};

template <
	class T
> class disable_if_c<true, T> {
};

template <
	class Cond,
	class T = void
> class disable_if
	: public disable_if_c<Cond::value, T>
{
};

}

#endif

