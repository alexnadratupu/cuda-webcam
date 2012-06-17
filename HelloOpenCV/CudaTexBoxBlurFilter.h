#ifndef CUDATEXBOXBLURFILTER_H_
#define CUDATEXBOXBLURFILTER_H_

/** 
	\file CudaTexBoxBlurFilter.h
	CudaTexBoxBlurFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "SingleCudaTexFilter.h"

#include "texBoxBlur.h" // kernel definition

/**
	CUDA ve texture kullanarak GPU �zerinde g�r�nt�y� buland�ran filtre s�n�f�.
*/

class CudaTexBoxBlurFilter : public SingleCudaTexFilter
{

public:

	/**
		\ref deviceTexBoxBlurLaunch metod i�aret�isi ve "texBlur1" sembol ad� parametresi ile SingleCudaTexFilter yarat�c�s�n� �a��r�r.
	*/
	CudaTexBoxBlurFilter()
		: SingleCudaTexFilter(deviceTexBoxBlurLaunch, "texBlur1")
	{
	}

private:

	DISALLOW_COPY_AND_ASSIGN(CudaTexBoxBlurFilter);

};

#endif // CUDATEXBOXBLURFILTER_H_