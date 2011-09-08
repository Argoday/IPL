
#ifndef META__TypeVector_H
#define META__TypeVector_H

namespace Meta {

template <typename ElementType,int Length> class TypeVector;

template <typename ElementType> class TypeVector<ElementType,0> {
	
	public:

		typedef typename ElementType ElementType;
		typedef TypeVector<ElementType,0> ThisType;

		__forceinline ThisType(){}
		__forceinline explicit ThisType(const ElementType &scalar){}
		__forceinline ThisType(const ThisType &vector){}

		__forceinline ThisType &operator =(const ThisType    &_vector){return (*this);}
		__forceinline ThisType &operator =(const ElementType &_scalar){return (*this);}

		__forceinline bool operator ==(const ThisType    &_vector) const {return true;}
		__forceinline bool operator ==(const ElementType &_scalar) const {return true;}

		__forceinline void setAs(const ThisType &_vector){}
		__forceinline void setAsMin(const ThisType &vector){}
		__forceinline void setAsMax(const ThisType &vector){}

		__forceinline void setAs(const ElementType &_scalar){}
		__forceinline void setAsMin(const ElementType &scalar){}
		__forceinline void setAsMax(const ElementType &scalar){}

	//Operators
		//With Scalar:
		__forceinline ThisType &operator -=(const ElementType &scalar){return (*this);}
		__forceinline ThisType &operator +=(const ElementType &scalar){return (*this);}
		__forceinline ThisType &operator *=(const ElementType &scalar){return (*this);}
		__forceinline ThisType &operator /=(const ElementType &scalar){return (*this);}
		
		__forceinline ThisType operator-(const ElementType &scalar) const {return (*this);}
		__forceinline ThisType operator+(const ElementType &scalar) const {return (*this);}
		__forceinline ThisType operator*(const ElementType &scalar) const {return (*this);}
		__forceinline ThisType operator/(const ElementType &scalar) const {return (*this);}

	//With Vector
		__forceinline ThisType &operator -=(const ThisType &vector){return (*this);}
		__forceinline ThisType &operator +=(const ThisType &vector){return (*this);}
		__forceinline ThisType &operator *=(const ThisType &vector){return (*this);}
		__forceinline ThisType &operator /=(const ThisType &vector){return (*this);}

		__forceinline ThisType operator-(const ThisType &vector) const {return (*this);}
		__forceinline ThisType operator+(const ThisType &vector) const {return (*this);}
		__forceinline ThisType operator*(const ThisType &vector) const {return (*this);}
		__forceinline ThisType operator/(const ThisType &vector) const {return (*this);}

		friend __forceinline ThisType operator-(const ElementType &scalar, const ThisType &vector);
		friend __forceinline ThisType operator+(const ElementType &scalar, const ThisType &vector);
		friend __forceinline ThisType operator*(const ElementType &scalar, const ThisType &vector);
		friend __forceinline ThisType operator/(const ElementType &scalar, const ThisType &vector);

};


template <typename ElementType,int Length> class TypeVector {

	protected:
		ElementType value; //Aka car
		TypeVector<ElementType,Length-1> parent; //Aka cdr

	public:

		typedef typename ElementType ElementType;
		typedef TypeVector<ElementType,Length> ThisType;
		typedef TypeVector<ElementType,Length-1> ParentType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const ElementType &_scalar);
		__forceinline ThisType(const ThisType &_vector);

		__forceinline ThisType &operator =(const ThisType &_vector);
		__forceinline ThisType &operator =(const ElementType &_scalar);

		__forceinline bool operator ==(const ThisType    &_vector) const ;
		__forceinline bool operator ==(const ElementType &_scalar) const ;

		__forceinline void setAs(const ThisType &_vector);
		__forceinline void setAsMin(const ThisType &vector);
		__forceinline void setAsMax(const ThisType &vector);

		__forceinline void setAs(const ElementType &_scalar);
		__forceinline void setAsMin(const ElementType &scalar);
		__forceinline void setAsMax(const ElementType &scalar);

	//Operators
		//With Scalar:
		__forceinline ThisType &operator -=(const ElementType &scalar);
		__forceinline ThisType &operator +=(const ElementType &scalar);
		__forceinline ThisType &operator *=(const ElementType &scalar);
		__forceinline ThisType &operator /=(const ElementType &scalar);
		
		__forceinline ThisType operator-(const ElementType &scalar) const ;
		__forceinline ThisType operator+(const ElementType &scalar) const ;
		__forceinline ThisType operator*(const ElementType &scalar) const ;
		__forceinline ThisType operator/(const ElementType &scalar) const ;

		//With Vector:
		__forceinline ThisType &operator -=(const ThisType &vector);
		__forceinline ThisType &operator +=(const ThisType &vector);
		__forceinline ThisType &operator *=(const ThisType &vector);
		__forceinline ThisType &operator /=(const ThisType &vector);

		__forceinline ThisType operator-(const ThisType &vector) const ;
		__forceinline ThisType operator+(const ThisType &vector) const ;
		__forceinline ThisType operator*(const ThisType &vector) const ;
		__forceinline ThisType operator/(const ThisType &vector) const ;

		friend __forceinline ThisType operator-(const ElementType &scalar, const ThisType &vector){return TypeVector<ElementType,Length>(scalar)-vector;} //TODO: Figure out how to put this in the _cpp.h file
		friend __forceinline ThisType operator+(const ElementType &scalar, const ThisType &vector){return TypeVector<ElementType,Length>(scalar)+vector;}
		friend __forceinline ThisType operator*(const ElementType &scalar, const ThisType &vector){return TypeVector<ElementType,Length>(scalar)*vector;}
		friend __forceinline ThisType operator/(const ElementType &scalar, const ThisType &vector){return TypeVector<ElementType,Length>(scalar)/vector;}

		template <int TypeNumber> __forceinline const ElementType & get()    const {return parent.get<TypeNumber-1>();}
		template <              > __forceinline const ElementType & get<0>() const {return ThisType::value;}

		template <int TypeNumber> __forceinline       ElementType & get()          {return parent.get<TypeNumber-1>();}
		template <              > __forceinline       ElementType & get<0>()       {return ThisType::value;}

		template <int TypeNumber> __forceinline void set(const ElementType & _otherElement){this->get<TypeNumber>()=_otherElement;}

};


}

#include "TypeVector_cpp.h"

#endif
