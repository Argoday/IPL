
#ifndef META__remove_const_H
#define META__remove_const_H

namespace Meta {

template<class T				> class remove_const			 {typedef T type;   };
template<class T				> class remove_const<const T>	 {typedef T type;   };
template<class T				> class remove_const<const T[]>  {typedef T type[]; };
template<class T, unsigned int N> class remove_const<const T[N]> {typedef T type[N];};

}

#endif
