
#include "BaseLinearFilter.h"

namespace Filter {

template <typename PixelType> void BaseLinearFilter<PixelType>::resetTotalColor(){
	totalColor.setAs(0.0);
	PixelType *filterDataPtr = &(filterData(0,0));
	for(long y=0; y<filterData.getHeight(); ++y){ //TODO: put this inside of Algorithm1x1
		for(long x=0; x<filterData.getWidth(); ++x){
			totalColor+=filterData(x,y);
			++filterDataPtr;
		}
	}
}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::BaseLinearFilter)
