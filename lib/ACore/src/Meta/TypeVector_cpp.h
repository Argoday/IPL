
#ifndef META__TypeVector_CPP_H
#define META__TypeVector_CPP_H

namespace Meta {

#define TEMPLATE_DEF template <typename ElementType,int Length>
#define TYPE_DEF TypeVector<ElementType,Length>

TEMPLATE_DEF void TYPE_DEF::setAs(const ThisType    &_vector){value=_vector.value;parent.setAs(_vector.parent);}
TEMPLATE_DEF void TYPE_DEF::setAs(const ElementType &_scalar){value=_scalar      ;parent.setAs(_scalar);}

TEMPLATE_DEF void TYPE_DEF::setAsMin(const ThisType &vector){
	if(vector.value<value){value=vector.value;}
	parent.setAsMin(vector.parent);
}
TEMPLATE_DEF void TYPE_DEF::setAsMax(const ThisType &vector){
	if(vector.value>value){value=vector.value;}
	parent.setAsMax(vector.parent);
}
TEMPLATE_DEF void TYPE_DEF::setAsMin(const ElementType &scalar){
	if(scalar<value){value=scalar;}
	parent.setAsMin(scalar.parent);
}
TEMPLATE_DEF void TYPE_DEF::setAsMax(const ElementType &scalar){
	if(scalar>value){value=scalar;}
	parent.setAsMax(scalar.parent);
}

// Operators:
//With Scalar
TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator  =(const ElementType &_scalar){value=_scalar;parent=_scalar;return (*this);}
TEMPLATE_DEF TYPE_DEF::TypeVector(const ElementType &_scalar):value(_scalar),parent(_scalar){}

TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator -=(const ElementType &scalar){value-=scalar;parent-=scalar;return (*this);}
TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator +=(const ElementType &scalar){value+=scalar;parent+=scalar;return (*this);}
TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator *=(const ElementType &scalar){value*=scalar;parent*=scalar;return (*this);}
TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator /=(const ElementType &scalar){value/=scalar;parent/=scalar;return (*this);}

TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator-(const ElementType &scalar) const {return ThisType(*this)-=scalar;}
TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator+(const ElementType &scalar) const {return ThisType(*this)+=scalar;}
TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator*(const ElementType &scalar) const {return ThisType(*this)*=scalar;}
TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator/(const ElementType &scalar) const {return ThisType(*this)/=scalar;}

//With Vector
TEMPLATE_DEF TYPE_DEF::TypeVector(const ThisType &_vector)
	:value(_vector.value)
	,parent(_vector.parent)
{
}

TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator  =(const ThisType &_vector) {
	value=_vector.value;
	parent=_vector.parent;
	return (*this);
}

TEMPLATE_DEF bool TYPE_DEF::operator ==(const ThisType &_vector) const {
	if(value!=_vector.value){
		return false;
	}
	return (parent==_vector.parent);
}

TEMPLATE_DEF bool TYPE_DEF::operator ==(const ElementType &_scalar) const {
	if(value!=_scalar){
		return false;
	}
	return parent==_scalar;
}

TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator -=(const ThisType &vector) {value-=vector.value;parent-=vector.parent;return (*this);}
TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator +=(const ThisType &vector) {value+=vector.value;parent+=vector.parent;return (*this);}
TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator *=(const ThisType &vector) {value*=vector.value;parent*=vector.parent;return (*this);}
TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator /=(const ThisType &vector) {value/=vector.value;parent/=vector.parent;return (*this);}

TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator-(const ThisType &vector) const {return ThisType(*this)-=vector;}
TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator+(const ThisType &vector) const {return ThisType(*this)+=vector;}
TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator*(const ThisType &vector) const {return ThisType(*this)*=vector;}
TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator/(const ThisType &vector) const {return ThisType(*this)/=vector;}

#undef TEMPLATE_DEF
#undef TYPE_DEF

}

#endif
