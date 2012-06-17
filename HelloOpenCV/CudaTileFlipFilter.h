#ifndef CUDATILEFLIPFILTER_H_
#define CUDATILEFLIPFILTER_H_

/** 
	\file CudaTileFlipFilter.h
	CudaTileFlipFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "SingleCudaFilter.h"

#include "tileFlip.h" // kernel definition.

/**
	CUDA kullanarak GPU �zerinde g�r�nt�y� blok blok d�nd�ren filtre s�n�f�.
*/

class CudaTileFlipFilter : public SingleCudaFilter
{

public:

	/**
		\ref deviceTileFlipLaunch metod i�aret�isi parametresi ile SingleCudaFilter yarat�c�s�n� �a��r�r.
	*/
	CudaTileFlipFilter()
		: SingleCudaFilter(deviceTileFlipLaunch)
	{
	}

private:

	DISALLOW_COPY_AND_ASSIGN(CudaTileFlipFilter);

};

#endif // CUDATILEFLIPFILTER_H_