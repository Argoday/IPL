
#ifndef VIDEO__Config_H
#define VIDEO__Config_H

#include "AVL.h"
#include <Data/DataTypes.h>

namespace Video {

class AVL_DLL_EXPORT Config {
	public:
		typedef Config ThisType;

		Config(const I8u & _durationFrames):durationFrames(_durationFrames){}
		Config(const ThisType & other):durationFrames(other.durationFrames){}

		const I8u & getDurationFrames() const {return durationFrames;}

	private:
		I8u durationFrames;
};

}

#endif 
