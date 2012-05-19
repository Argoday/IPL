
#ifndef META__TypeStruct_H
#define META__TypeStruct_H

#include "ACore.h"

namespace Meta {

template <typename ElementType> class TypeStructEnd {
	public:
		ElementType value;

		static const int length = 1;

		typedef TypeStructEnd<ElementType> ThisType;

		FINLINE TypeStructEnd(){};
		
		FINLINE ThisType &operator -=(const ThisType &other){value-=other.value;return (*this);};
		FINLINE ThisType &operator +=(const ThisType &other){value+=other.value;return (*this);};
		FINLINE ThisType &operator *=(const ThisType &other){value*=other.value;return (*this);};
		FINLINE ThisType &operator /=(const ThisType &other){value/=other.value;return (*this);};

		FINLINE ThisType operator-(const ThisType &other) const {return ThisType(*this)-=other;};
		FINLINE ThisType operator+(const ThisType &other) const {return ThisType(*this)+=other;};
		FINLINE ThisType operator*(const ThisType &other) const {return ThisType(*this)*=other;};
		FINLINE ThisType operator/(const ThisType &other) const {return ThisType(*this)/=other;};

		template <int TypeNumber,typename ReturnType> FINLINE const ElementType &get() const {return value;}
		template <int TypeNumber,typename ReturnType> FINLINE       ElementType &get()       {return value;}
		
		template <int TypeNumber,typename OtherType> FINLINE void set(const OtherType & _otherElement){this->get<TypeNumber,OtherType>()=_otherElement;}
		
};

template <typename ElementType,typename ParentType> class TypeStruct {
	public:
		ElementType value;
		ParentType parent;

		static const int length = ParentType::length + 1;

		typedef TypeStruct<ElementType,ParentType> ThisType;

		FINLINE TypeStruct(){};
		FINLINE TypeStruct(const ThisType &_struct);

		FINLINE ThisType &operator =(const ThisType &_struct);

		FINLINE ThisType &operator -=(const ThisType &other);
		FINLINE ThisType &operator +=(const ThisType &other);
		FINLINE ThisType &operator *=(const ThisType &other);
		FINLINE ThisType &operator /=(const ThisType &other);

		FINLINE ThisType operator-(const ThisType &other) const ;
		FINLINE ThisType operator+(const ThisType &other) const ;
		FINLINE ThisType operator*(const ThisType &other) const ;
		FINLINE ThisType operator/(const ThisType &other) const ;

		template <int TypeNumber,typename ReturnType> FINLINE const ReturnType  & get               () const {return ParentType::get<TypeNumber-1,ReturnType>();}
		template <                                  > FINLINE const ElementType & get<0,ElementType>() const {return value;}

		template <int TypeNumber,typename ReturnType> FINLINE ReturnType  & get               (){return ParentType::get<TypeNumber-1,ReturnType>();}
		template <                                  > FINLINE ElementType & get<0,ElementType>(){return value;}

		template <int TypeNumber,typename OtherType> FINLINE void set(const OtherType & _otherElement){this->get<TypeNumber,OtherType>()=_otherElement;}

};

}

#include "TypeStruct_cpp.h"

#endif
