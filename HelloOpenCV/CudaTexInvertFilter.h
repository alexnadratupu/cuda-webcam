#ifndef CUDATEXINVERTFILTER_H_
#define CUDATEXINVERTFILTER_H_

/** 
	\file CudaTexInvertFilter.h
	CudaTexInvertFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "SingleCudaTexFilter.h"

#include "texInvert.h"

/**
	CUDA ve texture kullanarak GPU �zerinde g�r�nt�n�n negatifini alan filtre s�n�f�.
*/

class CudaTexInvertFilter : public SingleCudaTexFilter
{

public:

	/**
		\ref deviceTexInvertLaunch metod i�aret�isi ve "texInvert1" sembol ad� parametresi ile SingleCudaTexFilter yarat�c�s�n� �a��r�r.
	*/
	CudaTexInvertFilter()
		: SingleCudaTexFilter(deviceTexInvertLaunch, "texInvert1")
	{
	}

private:

	DISALLOW_COPY_AND_ASSIGN(CudaTexInvertFilter);

};

#endif // CUDATEXINVERTFILTER_H_