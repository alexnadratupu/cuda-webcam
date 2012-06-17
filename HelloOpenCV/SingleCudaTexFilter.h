#ifndef SINGLECUDATEXFILTER_H_
#define SINGLECUDATEXFILTER_H_

/** 
	\file SingleCudaTexFilter.h
	SingleCudaTexFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "cudaCommon.h"

#include "SingleCudaFilter.h"

/**
	CUDA ve texture kullanarak GPU �zerinde g�r�nt� filtrelemek i�in kullan�lan s�n�f.
	
	SingleCudaTexFilter s�n�f�n�n g�revi, SingleCudaFilter s�n�f�na ek olarak CUDA �zerinde texture kullanan kernelleri �a��rabilmek i�in texture y�klemesi ve texture y�netimi yapmakt�r.
*/

class SingleCudaTexFilter : public SingleCudaFilter
{

private:
	cudaArray* cu_array;
	cudaChannelFormatDesc channelDesc;
	const char* textureSymbolName;

	const textureReference* constTexRefPtr;
	textureReference* texRefPtr;

	DISALLOW_COPY_AND_ASSIGN(SingleCudaTexFilter);

public:
	
	/**
		kernelLauncher ve texture ad�n� alan SingleCudaTexFilter yarat�c�s�.

		\param kernelLauncher Kerneli �a��rmak i�in kullan�lan metod i�aret�isi.
		\param textureSymbolName Kernelde kullan�lan texture'�n sembol ad�.
		
		ptKernelLauncher tipinde metod i�aret�isi ve texture sembol�n�n kerneldeki ad�n� alan SingleCudaTexFilter yarat�c�s�.
	*/
	explicit SingleCudaTexFilter( ptKernelLauncher kernelLauncher, const char* textureSymbolName )
		: SingleCudaFilter(kernelLauncher), 
		textureSymbolName(textureSymbolName),
		constTexRefPtr(NULL),
		texRefPtr(NULL)
	{
	}

	virtual void InitFilter(int width, int height);
	virtual void FilterImage(char* imageData);
	virtual void ReleaseFilter();
};

#endif SINGLECUDATEXFILTER_H_