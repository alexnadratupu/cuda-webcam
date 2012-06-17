#ifndef CUDAINVERTFILTER_H_
#define CUDAINVERTFILTER_H_

/** 
	\file CudaInvertFilter.h
	CudaInvertFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "SingleCudaFilter.h"

#include "invert.h" // kernel definition

/**
	CUDA kullanarak GPU �zerinde g�r�nt�n�n negatifini alan filtre s�n�f�.
*/

class CudaInvertFilter : public SingleCudaFilter
{

public:

	/**
		\ref deviceInvertLaunch metod i�aret�isi parametresi ile SingleCudaFilter yarat�c�s�n� �a��r�r.
	*/
	CudaInvertFilter()
		: SingleCudaFilter(deviceInvertLaunch)
	{
	}

private:

	DISALLOW_COPY_AND_ASSIGN(CudaInvertFilter);

};

#endif // CUDAINVERTFILTER_H_