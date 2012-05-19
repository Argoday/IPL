
#ifndef AUDIO__Config_H
#define AUDIO__Config_H

#include "AAL.h"
#include <Data/DataTypes.h>

namespace Audio {

class AAL_DLL_EXPORT Config {
	public:
		typedef Config ThisType;

		Config(I4  & _channels,I4  & _freq,I4  & _sampleSize):channels(_channels),freq(_freq),sampleSize(_sampleSize){}
		Config(I8u & _channels,I8u & _freq,I8u & _sampleSize):channels(_channels),freq(_freq),sampleSize(_sampleSize){}
		Config(const ThisType & other):channels(other.channels),freq(other.freq),sampleSize(other.sampleSize){}

		const I8u & getChannels()   const {return channels;}
		const I8u & getFrequency()  const {return freq;}
		const I8u & getSampleSize() const {return sampleSize;}

	private:
		I8u channels;
		I8u freq;
		I8u sampleSize;
};

}

#endif 
