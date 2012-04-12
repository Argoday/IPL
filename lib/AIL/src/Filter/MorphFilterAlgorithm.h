
#ifndef FILTER__MorphFilterAlgorithm_H
#define FILTER__MorphFilterAlgorithm_H

namespace Filter {

template <
	typename PixelDataType
> class DilateAlgorithm3x3Cross {
	public:
		static __forceinline void process(PixelDataType *dstPixelPtr,const PixelDataType *srcPixelPtr02,const PixelDataType *srcPixelPtr12,const PixelDataType *srcPixelPtr22,
																	 const PixelDataType *srcPixelPtr01,const PixelDataType *srcPixelPtr11,const PixelDataType *srcPixelPtr21,
																	 const PixelDataType *srcPixelPtr00,const PixelDataType *srcPixelPtr10,const PixelDataType *srcPixelPtr20){
			PixelDataType tempPixel=(*srcPixelPtr12);
			tempPixel.setAsMax(*srcPixelPtr01);
			tempPixel.setAsMax(*srcPixelPtr11);
			tempPixel.setAsMax(*srcPixelPtr21);
			tempPixel.setAsMax(*srcPixelPtr10);
			(*dstPixelPtr) = tempPixel;
		}
};

template <
	typename PixelDataType
> class ErodeAlgorithm3x3Cross {
	public:
		static __forceinline void process(PixelDataType *dstPixelPtr,const PixelDataType *srcPixelPtr02,const PixelDataType *srcPixelPtr12,const PixelDataType *srcPixelPtr22,
																	 const PixelDataType *srcPixelPtr01,const PixelDataType *srcPixelPtr11,const PixelDataType *srcPixelPtr21,
																	 const PixelDataType *srcPixelPtr00,const PixelDataType *srcPixelPtr10,const PixelDataType *srcPixelPtr20){
			PixelDataType tempPixel=(*srcPixelPtr12);
			tempPixel.setAsMin(*srcPixelPtr01);
			tempPixel.setAsMin(*srcPixelPtr11);
			tempPixel.setAsMin(*srcPixelPtr21);
			tempPixel.setAsMin(*srcPixelPtr10);
			(*dstPixelPtr) = tempPixel;
		}
};

}

#endif
