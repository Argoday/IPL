
#ifndef PIXEL__PixelTypeID_H
#define PIXEL__PixelTypeID_H

namespace Pixel {

// Emulate a strong enum
class PixelTypeID {
	public:
		PixelTypeID(const PixelTypeID &other)
			:typeID(other.typeID)
			,name(other.name)
		{
		}

		__forceinline bool operator ==(const PixelTypeID &other) const {return typeID==other.typeID;}

		__forceinline const char * const &getTypeName() const {return name;}

		static const PixelTypeID Yb;

		static const PixelTypeID Yi1u;
		static const PixelTypeID Yi4;
		static const PixelTypeID Yf4;
		static const PixelTypeID Yf8;

		static const PixelTypeID RGBi1u;
		static const PixelTypeID RGBi4;
		static const PixelTypeID RGBf4;
		static const PixelTypeID RGBf8;

		static const PixelTypeID BGRi1u;
		static const PixelTypeID BGRi4;
		static const PixelTypeID BGRf4;
		static const PixelTypeID BGRf8;

		static const PixelTypeID YUVi1u;
		static const PixelTypeID YUVi4;
		static const PixelTypeID YUVf4;
		static const PixelTypeID YUVf8;

		static const PixelTypeID YIQi1u;
		static const PixelTypeID YIQi4;
		static const PixelTypeID YIQf4;
		static const PixelTypeID YIQf8;

		static const PixelTypeID LABi1u;
		static const PixelTypeID LABi4;
		static const PixelTypeID LABf4;
		static const PixelTypeID LABf8;

		static const PixelTypeID HSVi1u;
		static const PixelTypeID HSVi4;
		static const PixelTypeID HSVf4;
		static const PixelTypeID HSVf8;

		static const PixelTypeID RGBAi1u;
		static const PixelTypeID RGBAi4;
		static const PixelTypeID RGBAf4;
		static const PixelTypeID RGBAf8;


	private:
		PixelTypeID(const int &_typeID,const char * const &_name)
			:typeID(_typeID)
			,name(_name)
		{
		}

		const char * const name;
		const int typeID;

};

};

#endif
