
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

		static const PixelTypeID GRAYb;
		static const PixelTypeID GRAYi;
		static const PixelTypeID GRAYd;

		static const PixelTypeID RGBuc;
		static const PixelTypeID RGBi;
		static const PixelTypeID RGBf;
		static const PixelTypeID RGBd;

		static const PixelTypeID RGBAuc;
		static const PixelTypeID RGBAi;
		static const PixelTypeID RGBAf;
		static const PixelTypeID RGBAd;

		static const PixelTypeID YUVd;

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
