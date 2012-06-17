#ifndef CUDASEPUAFILTER_H_
#define CUDASEPUAFILTER_H_

/** 
	\file CudaSepiaFilter.h
	CudaSepiaFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "SingleCudaFilter.h"

#include "sepia.h" // kernel definition.

/**
	CUDA kullanarak GPU �zerinde g�r�nt�n�n sepia tonlamas�n� d�nd�ren filtre s�n�f�.
*/

class CudaSepiaFilter : public SingleCudaFilter
{

public:

	/**
		\ref deviceSepiaLaunch metod i�aret�isi parametresi ile SingleCudaFilter yarat�c�s�n� �a��r�r.
	*/
	CudaSepiaFilter()
		: SingleCudaFilter(deviceSepiaLaunch)
	{
	}

private:

	DISALLOW_COPY_AND_ASSIGN(CudaSepiaFilter);

};

#endif // CUDASEPUAFILTER_H_