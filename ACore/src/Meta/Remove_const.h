
#ifndef META__Remove_const_H
#define META__Remove_const_H

namespace Meta {

template<class _Ty>	class Remove_const {
	typedef _Ty type;
};

template<class _Ty>	class Remove_const<const _Ty> {
	typedef _Ty type;
};

template<class _Ty>	class Remove_const<const _Ty[]> {
	typedef _Ty type[];
};

template<class _Ty, unsigned int _Nx> class Remove_const<const _Ty[_Nx]> {
	typedef _Ty type[_Nx];
};

}

#endif
