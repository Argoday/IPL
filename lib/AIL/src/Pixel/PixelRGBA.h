
#ifndef PIXEL__Pixel_RGBA_H
#define PIXEL__Pixel_RGBA_H

#include <AIL.h>
#include <Meta/TypeVector.h>
#include <Pixel/PixelTypeID.h>
#include <Pixel/PixelDataType3A.h>
#include <Pixel/PixelRange.h>
#include <Data/DataTypes.h>

namespace Pixel {

template <
	typename NumberType,
	typename ComputationDataType,
	typename PixelRangeType,
	int Rposition,
	int Gposition,
	int Bposition,
	int Aposition
> class AIL_DLL_EXPORT PixelRGBAbaseType
	: public PixelDataType3A<NumberType,Rposition,Gposition,Bposition,Aposition>
{
	public:

		typedef typename NumberType     NumberType;
		typedef typename PixelRangeType RangeType;
		typedef PixelDataType3A<NumberType         ,Rposition,Gposition,Bposition,Aposition> DataType;
		typedef PixelDataType3A<ComputationDataType,Rposition,Gposition,Bposition,Aposition> ComputationType;
		typedef PixelDataType3A<NumberType         ,Rposition,Gposition,Bposition,Aposition> ParentType;
		typedef PixelRGBAbaseType<NumberType,ComputationDataType,PixelRangeType,Rposition,Gposition,Bposition,Aposition> ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType   & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType   & _pixel ):ParentType(_pixel ){}

		FINLINE explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b){setR(_r);setG(_g);setB(_b);setA(RangeType::maxValue);}
		FINLINE explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b,const NumberType & _a){setR(_r);setG(_g);setB(_b);setA(_a);}
		
		FINLINE void setR(const NumberType & _r) {this->set<Rposition>(_r);}
		FINLINE void setG(const NumberType & _g) {this->set<Gposition>(_g);}
		FINLINE void setB(const NumberType & _b) {this->set<Bposition>(_b);}
		FINLINE void setA(const NumberType & _a) {this->set<Aposition>(_a);}

		FINLINE void clip(){RangeType::clip(*static_cast<ParentType*>(this));}

		FINLINE const NumberType & getR() const {return this->get<Rposition>();}
		FINLINE const NumberType & getG() const {return this->get<Gposition>();}
		FINLINE const NumberType & getB() const {return this->get<Bposition>();}
		FINLINE const NumberType & getA() const {return this->get<Aposition>();}

};

typedef PixelRGBAbaseType<I1u,I4,PixelRange_XYZAi1u   ,0,1,2,3> PixelRGBAi1utd;
typedef PixelRGBAbaseType<I4 ,I4,PixelRange_XYZAi4_i1u,0,1,2,3> PixelRGBAi4_i1utd;
typedef PixelRGBAbaseType<I4 ,I4,PixelRange_XYZAi4_i2u,0,1,2,3> PixelRGBAi4_i2utd;
typedef PixelRGBAbaseType<F8 ,F8,PixelRange_XYZAf8    ,0,1,2,3> PixelRGBAf8td;

typedef PixelRGBAbaseType<I1u,I4,PixelRange_AXYZi1u   ,1,2,3,0> PixelARGBi1utd;
typedef PixelRGBAbaseType<I4 ,I4,PixelRange_AXYZi4_i1u,1,2,3,0> PixelARGBi4_i1utd;
typedef PixelRGBAbaseType<I4 ,I4,PixelRange_AXYZi4_i2u,1,2,3,0> PixelARGBi4_i2utd;
typedef PixelRGBAbaseType<F8 ,F8,PixelRange_AXYZf8    ,1,2,3,0> PixelARGBf8td;

typedef PixelRGBAbaseType<I1u,I4,PixelRange_ZYXAi1u   ,3,2,1,0> PixelBGRAi1utd;
typedef PixelRGBAbaseType<I4 ,I4,PixelRange_ZYXAi4_i1u,3,2,1,0> PixelBGRAi4_i1utd;
typedef PixelRGBAbaseType<I4 ,I4,PixelRange_ZYXAi4_i2u,3,2,1,0> PixelBGRAi4_i2utd;
typedef PixelRGBAbaseType<F8 ,F8,PixelRange_ZYXAf8    ,3,2,1,0> PixelBGRAf8td;

class AIL_DLL_EXPORT PixelRGBAi1u : public PixelRGBAi1utd {
	public:
		typedef I1u                             NumberType;
		typedef PixelRGBAi1utd::DataType        DataType;
		typedef PixelRGBAi1utd::ComputationType ComputationType;
		typedef PixelRange_XYZAi4               ComputationRange;
		typedef PixelRGBAi1utd                  ParentType;
		typedef PixelRGBAi1u                    ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

		FINLINE explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b,const NumberType & _a){setR(_r);setG(_g);setB(_b);setA(_a);}
};

class AIL_DLL_EXPORT PixelRGBAf8 : public PixelRGBAf8td {
	public:
		typedef F8                             NumberType;
		typedef PixelRGBAf8td::DataType        DataType;
		typedef PixelRGBAf8td::ComputationType ComputationType;
		typedef PixelRange_XYZAf8              ComputationRange;
		typedef PixelRGBAf8td                  ParentType;
		typedef PixelRGBAf8                    ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

		FINLINE explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b,const NumberType & _a){setR(_r);setG(_g);setB(_b);setA(_a);}
};

class AIL_DLL_EXPORT PixelARGBi1u : public PixelARGBi1utd {
	public:
		typedef I1u                             NumberType;
		typedef PixelARGBi1utd::DataType        DataType;
		typedef PixelARGBi1utd::ComputationType ComputationType;
		typedef PixelRange_AXYZi4               ComputationRange;
		typedef PixelARGBi1utd                  ParentType;
		typedef PixelARGBi1u                    ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

		FINLINE explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b,const NumberType & _a){setR(_r);setG(_g);setB(_b);setA(_a);}
};

class AIL_DLL_EXPORT PixelARGBf8 : public PixelARGBf8td {
	public:
		typedef F8                             NumberType;
		typedef PixelARGBf8td::DataType        DataType;
		typedef PixelARGBf8td::ComputationType ComputationType;
		typedef PixelRange_AXYZf8              ComputationRange;
		typedef PixelARGBf8td                  ParentType;
		typedef PixelARGBf8                    ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

		FINLINE explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b,const NumberType & _a){setR(_r);setG(_g);setB(_b);setA(_a);}
};

class AIL_DLL_EXPORT PixelBGRAi1u : public PixelBGRAi1utd {
	public:
		typedef I1u                             NumberType;
		typedef PixelBGRAi1utd::DataType        DataType;
		typedef PixelBGRAi1utd::ComputationType ComputationType;
		typedef PixelRange_ZYXAi4               ComputationRange;
		typedef PixelBGRAi1utd                  ParentType;
		typedef PixelBGRAi1u                    ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

		FINLINE explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b,const NumberType & _a){setR(_r);setG(_g);setB(_b);setA(_a);}
};

class AIL_DLL_EXPORT PixelBGRAf8 : public PixelBGRAf8td {
	public:
		typedef F8                             NumberType;
		typedef PixelBGRAf8td::DataType        DataType;
		typedef PixelBGRAf8td::ComputationType ComputationType;
		typedef PixelRange_ZYXAf8              ComputationRange;
		typedef PixelBGRAf8td                  ParentType;
		typedef PixelBGRAf8                    ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

		FINLINE explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b,const NumberType & _a){setR(_r);setG(_g);setB(_b);setA(_a);}
};

}

#endif
