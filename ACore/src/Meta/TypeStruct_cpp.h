
#ifndef META__TypeStruct_CPP_H
#define META__TypeStruct_CPP_H

namespace Meta {

#define TEMPLATE_DEF template <typename ElementType,typename ParentType>
#define TYPE_DEF TypeStruct<ElementType,ParentType>

TEMPLATE_DEF TYPE_DEF::TypeStruct(const ThisType &_struct)
	:ParentType(_struct)
	,value(_struct.value)
{
}

TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator  =(const ThisType &_struct) {
	value=_struct.value;
	return static_cast<ThisType &>(this->ParentType::operator =(_struct));
}

TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator -=(const ThisType &other) {value-=other.value;return static_cast<ThisType &>(this->ParentType::operator -=(other));}
TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator +=(const ThisType &other) {value+=other.value;return static_cast<ThisType &>(this->ParentType::operator +=(other));}
TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator *=(const ThisType &other) {value*=other.value;return static_cast<ThisType &>(this->ParentType::operator *=(other));}
TEMPLATE_DEF TYPE_DEF &TYPE_DEF::operator /=(const ThisType &other) {value/=other.value;return static_cast<ThisType &>(this->ParentType::operator /=(other));}

TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator-(const ThisType &other) const {return ThisType(*this)-=other;}
TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator+(const ThisType &other) const {return ThisType(*this)+=other;}
TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator*(const ThisType &other) const {return ThisType(*this)*=other;}
TEMPLATE_DEF TYPE_DEF TYPE_DEF::operator/(const ThisType &other) const {return ThisType(*this)/=other;}

#undef TEMPLATE_DEF
#undef TYPE_DEF

}

#endif
