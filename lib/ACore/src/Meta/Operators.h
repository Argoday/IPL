
#ifndef META__OPERATORS_H
#define META__OPERATORS_H

#include "ACore.h"

namespace Meta {

#define TEMPLATE_DEF template <typename T,typename U>
#define SI_DEF static FINLINE

//TODO: Think about changing 'process' as the standardized name to instead use operator()
TEMPLATE_DEF class Add {
	public:
		SI_DEF auto process(const T         &object1,const U         &object2) -> decltype(object1          +  object2 ){return (object1          +  object2 );}
		SI_DEF auto process(const T         &object1,const U * const &object2) -> decltype(object1          +(*object2)){return (object1          +(*object2));}
		SI_DEF auto process(const T * const &object1,const U         &object2) -> decltype(object1->operator+( object2)){return (object1->operator+( object2));}
		SI_DEF auto process(const T * const &object1,const U * const &object2) -> decltype(object1->operator+(*object2)){return (object1->operator+(*object2));}
};
TEMPLATE_DEF class Sub {
	public:
		SI_DEF auto process(const T         &object1,const U         &object2) -> decltype(object1          -  object2 ){return (object1          -  object2 );}
		SI_DEF auto process(const T         &object1,const U * const &object2) -> decltype(object1          -(*object2)){return (object1          -(*object2));}
		SI_DEF auto process(const T * const &object1,const U         &object2) -> decltype(object1->operator-( object2)){return (object1->operator-( object2));}
		SI_DEF auto process(const T * const &object1,const U * const &object2) -> decltype(object1->operator-(*object2)){return (object1->operator-(*object2));}
};
TEMPLATE_DEF class Mul {
	public:
		SI_DEF auto process(const T         &object1,const U         &object2) -> decltype(object1          *  object2 ){return (object1          *  object2 );}
		SI_DEF auto process(const T         &object1,const U * const &object2) -> decltype(object1          *(*object2)){return (object1          *(*object2));}
		SI_DEF auto process(const T * const &object1,const U         &object2) -> decltype(object1->operator*( object2)){return (object1->operator*( object2));}
		SI_DEF auto process(const T * const &object1,const U * const &object2) -> decltype(object1->operator*(*object2)){return (object1->operator*(*object2));}
};
TEMPLATE_DEF class Div {
	public:
		SI_DEF auto process(const T         &object1,const U         &object2) -> decltype(object1          /  object2 ){return (object1          /  object2 );}
		SI_DEF auto process(const T         &object1,const U * const &object2) -> decltype(object1          /(*object2)){return (object1          /(*object2));}
		SI_DEF auto process(const T * const &object1,const U         &object2) -> decltype(object1->operator/( object2)){return (object1->operator/( object2));}
		SI_DEF auto process(const T * const &object1,const U * const &object2) -> decltype(object1->operator/(*object2)){return (object1->operator/(*object2));}
};

TEMPLATE_DEF class AddEq {
	public:
		SI_DEF void process(T         &object1,const U         &object2){object1          +=  object2 ;}
		SI_DEF void process(T         &object1,const U * const &object2){object1          +=(*object2);}
		SI_DEF void process(T * const &object1,const U         &object2){object1->operator+=( object2);}
		SI_DEF void process(T * const &object1,const U * const &object2){object1->operator+=(*object2);}
};
TEMPLATE_DEF class SubEq {
	public:
		SI_DEF void process(T         &object1,const U         &object2){object1          -=  object2 ;}
		SI_DEF void process(T         &object1,const U * const &object2){object1          -=(*object2);}
		SI_DEF void process(T * const &object1,const U         &object2){object1->operator-=( object2);}
		SI_DEF void process(T * const &object1,const U * const &object2){object1->operator-=(*object2);}
};
TEMPLATE_DEF class MulEq {
	public:
		SI_DEF void process(T         &object1,const U         &object2){object1          *=  object2 ;}
		SI_DEF void process(T         &object1,const U * const &object2){object1          *=(*object2);}
		SI_DEF void process(T * const &object1,const U         &object2){object1->operator*=( object2);}
		SI_DEF void process(T * const &object1,const U * const &object2){object1->operator*=(*object2);}
};
TEMPLATE_DEF class DivEq {
	public:
		SI_DEF void process(T         &object1,const U         &object2){object1          /=  object2 ;}
		SI_DEF void process(T         &object1,const U * const &object2){object1          /=(*object2);}
		SI_DEF void process(T * const &object1,const U         &object2){object1->operator/=( object2);}
		SI_DEF void process(T * const &object1,const U * const &object2){object1->operator/=(*object2);}
};

#undef TEMPLATE_DEF
#undef SI_DEF

}

#endif
