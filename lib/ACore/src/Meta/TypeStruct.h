
#ifndef META__TypeStruct_H
#define META__TypeStruct_H

namespace Meta {

template <typename ElementType> class TypeStructEnd {
	public:
		ElementType value;

		static const int length = 1;

		typedef TypeStructEnd<ElementType> ThisType;

		__forceinline ThisType(){};
		
		__forceinline ThisType &operator -=(const ThisType &other){value-=other.value;return (*this);};
		__forceinline ThisType &operator +=(const ThisType &other){value+=other.value;return (*this);};
		__forceinline ThisType &operator *=(const ThisType &other){value*=other.value;return (*this);};
		__forceinline ThisType &operator /=(const ThisType &other){value/=other.value;return (*this);};

		__forceinline ThisType operator-(const ThisType &other) const {return ThisType(*this)-=other;};
		__forceinline ThisType operator+(const ThisType &other) const {return ThisType(*this)+=other;};
		__forceinline ThisType operator*(const ThisType &other) const {return ThisType(*this)*=other;};
		__forceinline ThisType operator/(const ThisType &other) const {return ThisType(*this)/=other;};

		template <int TypeNumber,typename ReturnType> __forceinline const ElementType &get() const {return value;}
		template <int TypeNumber,typename ReturnType> __forceinline       ElementType &get()       {return value;}
		
		template <int TypeNumber,typename OtherType> __forceinline void set(const OtherType & _otherElement){this->get<TypeNumber,OtherType>()=_otherElement;}
		
};

template <typename ElementType,typename ParentType> class TypeStruct {
	public:
		ElementType value;
		ParentType parent;

		static const int length = ParentType::length + 1;

		typedef TypeStruct<ElementType,ParentType> ThisType;

		__forceinline ThisType(){};
		__forceinline ThisType(const ThisType &_struct);

		__forceinline ThisType &operator =(const ThisType &_struct);

		__forceinline ThisType &operator -=(const ThisType &other);
		__forceinline ThisType &operator +=(const ThisType &other);
		__forceinline ThisType &operator *=(const ThisType &other);
		__forceinline ThisType &operator /=(const ThisType &other);

		__forceinline ThisType operator-(const ThisType &other) const ;
		__forceinline ThisType operator+(const ThisType &other) const ;
		__forceinline ThisType operator*(const ThisType &other) const ;
		__forceinline ThisType operator/(const ThisType &other) const ;

		template <int TypeNumber,typename ReturnType> __forceinline const ReturnType  & get               () const {return ParentType::get<TypeNumber-1,ReturnType>();}
		template <                                  > __forceinline const ElementType & get<0,ElementType>() const {return value;}

		template <int TypeNumber,typename ReturnType> __forceinline ReturnType  & get               (){return ParentType::get<TypeNumber-1,ReturnType>();}
		template <                                  > __forceinline ElementType & get<0,ElementType>(){return value;}

		template <int TypeNumber,typename OtherType> __forceinline void set(const OtherType & _otherElement){this->get<TypeNumber,OtherType>()=_otherElement;}

};

}

#include "TypeStruct_cpp.h"

#endif
