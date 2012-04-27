
#ifndef META__TypeVector_H
#define META__TypeVector_H

#include "ACore.h"

namespace Meta {

template <typename ElementType,int Length> class TypeVector;

template <typename ElementType> class TypeVector<ElementType,0> {
	
	public:

		typedef typename ElementType ElementType;
		typedef TypeVector<ElementType,0> ThisType;

		FINLINE ThisType(){}
		FINLINE explicit ThisType(const ElementType &scalar){}
		FINLINE ThisType(const ThisType &vector){}

		FINLINE ThisType &operator =(const ThisType    &_vector){return (*this);}
		FINLINE ThisType &operator =(const ElementType &_scalar){return (*this);}

		FINLINE bool operator ==(const ThisType    &_vector) const {return true;}
		FINLINE bool operator ==(const ElementType &_scalar) const {return true;}

		FINLINE void setAs(const ThisType &_vector){}
		FINLINE void setAsMin(const ThisType &vector){}
		FINLINE void setAsMax(const ThisType &vector){}

		FINLINE void setAs(const ElementType &_scalar){}
		FINLINE void setAsMin(const ElementType &scalar){}
		FINLINE void setAsMax(const ElementType &scalar){}

	//Operators
		//With Scalar:
		FINLINE ThisType &operator -=(const ElementType &scalar){return (*this);}
		FINLINE ThisType &operator +=(const ElementType &scalar){return (*this);}
		FINLINE ThisType &operator *=(const ElementType &scalar){return (*this);}
		FINLINE ThisType &operator /=(const ElementType &scalar){return (*this);}
		
		FINLINE ThisType operator-(const ElementType &scalar) const {return (*this);}
		FINLINE ThisType operator+(const ElementType &scalar) const {return (*this);}
		FINLINE ThisType operator*(const ElementType &scalar) const {return (*this);}
		FINLINE ThisType operator/(const ElementType &scalar) const {return (*this);}

	//With Vector
		FINLINE ThisType &operator -=(const ThisType &vector){return (*this);}
		FINLINE ThisType &operator +=(const ThisType &vector){return (*this);}
		FINLINE ThisType &operator *=(const ThisType &vector){return (*this);}
		FINLINE ThisType &operator /=(const ThisType &vector){return (*this);}

		FINLINE ThisType operator-(const ThisType &vector) const {return (*this);}
		FINLINE ThisType operator+(const ThisType &vector) const {return (*this);}
		FINLINE ThisType operator*(const ThisType &vector) const {return (*this);}
		FINLINE ThisType operator/(const ThisType &vector) const {return (*this);}

		friend FINLINE ThisType operator-(const ElementType &scalar, const ThisType &vector);
		friend FINLINE ThisType operator+(const ElementType &scalar, const ThisType &vector);
		friend FINLINE ThisType operator*(const ElementType &scalar, const ThisType &vector);
		friend FINLINE ThisType operator/(const ElementType &scalar, const ThisType &vector);

};


template <typename ElementType,int Length> class TypeVector {

	protected:
		ElementType value; //Aka car
		TypeVector<ElementType,Length-1> parent; //Aka cdr

	public:

		typedef typename ElementType ElementType;
		typedef TypeVector<ElementType,Length> ThisType;
		typedef TypeVector<ElementType,Length-1> ParentType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const ElementType &_scalar);
		FINLINE ThisType(const ThisType &_vector);

		FINLINE ThisType &operator =(const ThisType &_vector);
		FINLINE ThisType &operator =(const ElementType &_scalar);

		FINLINE bool operator ==(const ThisType    &_vector) const ;
		FINLINE bool operator ==(const ElementType &_scalar) const ;

		FINLINE void setAs(const ThisType &_vector);
		FINLINE void setAsMin(const ThisType &vector);
		FINLINE void setAsMax(const ThisType &vector);

		FINLINE void setAs(const ElementType &_scalar);
		FINLINE void setAsMin(const ElementType &scalar);
		FINLINE void setAsMax(const ElementType &scalar);

	//Operators
		//With Scalar:
		FINLINE ThisType &operator -=(const ElementType &scalar);
		FINLINE ThisType &operator +=(const ElementType &scalar);
		FINLINE ThisType &operator *=(const ElementType &scalar);
		FINLINE ThisType &operator /=(const ElementType &scalar);
		
		FINLINE ThisType operator-(const ElementType &scalar) const ;
		FINLINE ThisType operator+(const ElementType &scalar) const ;
		FINLINE ThisType operator*(const ElementType &scalar) const ;
		FINLINE ThisType operator/(const ElementType &scalar) const ;

		//With Vector:
		FINLINE ThisType &operator -=(const ThisType &vector);
		FINLINE ThisType &operator +=(const ThisType &vector);
		FINLINE ThisType &operator *=(const ThisType &vector);
		FINLINE ThisType &operator /=(const ThisType &vector);

		FINLINE ThisType operator-(const ThisType &vector) const ;
		FINLINE ThisType operator+(const ThisType &vector) const ;
		FINLINE ThisType operator*(const ThisType &vector) const ;
		FINLINE ThisType operator/(const ThisType &vector) const ;

		friend FINLINE ThisType operator-(const ElementType &scalar, const ThisType &vector){return TypeVector<ElementType,Length>(scalar)-vector;} //TODO: Figure out how to put this in the _cpp.h file
		friend FINLINE ThisType operator+(const ElementType &scalar, const ThisType &vector){return TypeVector<ElementType,Length>(scalar)+vector;}
		friend FINLINE ThisType operator*(const ElementType &scalar, const ThisType &vector){return TypeVector<ElementType,Length>(scalar)*vector;}
		friend FINLINE ThisType operator/(const ElementType &scalar, const ThisType &vector){return TypeVector<ElementType,Length>(scalar)/vector;}

		template <int TypeNumber> FINLINE const ElementType & get()    const {return parent.get<TypeNumber-1>();}
		template <              > FINLINE const ElementType & get<0>() const {return ThisType::value;}

		template <int TypeNumber> FINLINE       ElementType & get()          {return parent.get<TypeNumber-1>();}
		template <              > FINLINE       ElementType & get<0>()       {return ThisType::value;}

		template <int TypeNumber> FINLINE void set(const ElementType & _otherElement){this->get<TypeNumber>()=_otherElement;}

};


}

#include "TypeVector_cpp.h"

#endif
