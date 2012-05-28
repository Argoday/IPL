
#ifndef META__Boolean_CPP_H
#define META__Boolean_CPP_H

#include "Boolean.h"

namespace Meta {

void Boolean::setAs(const ThisType   &  other){value=other.value;}
void Boolean::setAs(const NumberType & _value){value=_value;}

// Operators:
//With NumberType
B1n Boolean::operator ==(const NumberType & _value) const {return (value==_value);}
Boolean & Boolean::operator =(const NumberType & _value){value=_value; return (*this);}

Boolean::Boolean(const NumberType &_value):value(_value){}

Boolean & Boolean::operator -=(const NumberType & number){value = value && !number; return (*this);}
Boolean & Boolean::operator +=(const NumberType & number){value = value ||  number; return (*this);}
Boolean & Boolean::operator *=(const NumberType & number){value = value &&  number; return (*this);}
Boolean & Boolean::operator /=(const NumberType & number){value = value  ^  number; return (*this);}

Boolean Boolean::operator-(const NumberType & value) const {return ThisType(*this)-=value;}
Boolean Boolean::operator+(const NumberType & value) const {return ThisType(*this)+=value;}
Boolean Boolean::operator*(const NumberType & value) const {return ThisType(*this)*=value;}
Boolean Boolean::operator/(const NumberType & value) const {return ThisType(*this)/=value;}

//With ThisType
B1n Boolean::operator ==(const ThisType & other) const {return (value==other.value);}
Boolean::Boolean(const ThisType & other){value=other.value;}

Boolean & Boolean::operator  =(const ThisType & other) {value = other.value; return (*this);}

Boolean & Boolean::operator -=(const ThisType & other) {value = value && !other.value; return (*this);}
Boolean & Boolean::operator +=(const ThisType & other) {value = value ||  other.value; return (*this);}
Boolean & Boolean::operator *=(const ThisType & other) {value = value &&  other.value; return (*this);}
Boolean & Boolean::operator /=(const ThisType & other) {value = value  ^  other.value; return (*this);}

Boolean Boolean::operator-(const ThisType & other) const {return ThisType(*this)-=other;}
Boolean Boolean::operator+(const ThisType & other) const {return ThisType(*this)+=other;}
Boolean Boolean::operator*(const ThisType & other) const {return ThisType(*this)*=other;}
Boolean Boolean::operator/(const ThisType & other) const {return ThisType(*this)/=other;}

Meta::Boolean operator-(const Meta::Boolean::NumberType & value, const Meta::Boolean & other){return Meta::Boolean(value)-other;}
Meta::Boolean operator+(const Meta::Boolean::NumberType & value, const Meta::Boolean & other){return Meta::Boolean(value)+other;}
Meta::Boolean operator*(const Meta::Boolean::NumberType & value, const Meta::Boolean & other){return Meta::Boolean(value)*other;}
Meta::Boolean operator/(const Meta::Boolean::NumberType & value, const Meta::Boolean & other){return Meta::Boolean(value)/other;}

}

#endif
