
#include "BaseLinearFilter.h"

namespace Filter {

template <
	typename PixelType
> void BaseLinearFilter<PixelType>::resetTotalColor(){
	totalColor.setComp(PixelType::RangeType::minPixel);
	auto filterDataPtr = filterData.getDataPtr();
	for(I4 y=0; y<filterData.getHeight(); ++y){ //TODO: put this inside of Algorithm1x1
		for(I4 x=0; x<filterData.getWidth(); ++x){
			totalColor+=filterData(x,y).getAsComp<typename PixelType::ComputationType::NumberType>();
			++filterDataPtr;
		}
	}
}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::BaseLinearFilter)
