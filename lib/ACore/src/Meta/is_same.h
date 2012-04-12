
#ifndef META__is_same_H
#define META__is_same_H

namespace Meta {

template<
	class T,
	class U
> class is_same {
	public:
		enum { value = 0 };
};
template<
	class T
> class is_same<T,T> {
	public:
		enum { value = 1 };
};

}

#endif
