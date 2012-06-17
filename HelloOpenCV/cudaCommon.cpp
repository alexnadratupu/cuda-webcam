#include "cudaCommon.h"

/**
	\file cudaCommon.cpp
	CUDA kullanan t�m s�n�flarda kullan�lan metodlar� i�erilen dosya.
*/

/**
	CUDA metodlar�n�n d�n�� de�erlerinde hata kontrol� yapar.

	\param msg Hata halinde yazd�r�lacak mesaj.

	D�n�� kodu cudaSuccess de�ilse hata mesaj� yazd�r�l�r ve program sonland�r�l�r.
*/
void checkCUDAError(const char *msg)
{
    cudaError_t err = cudaGetLastError();
    if( cudaSuccess != err) 
    {
        fprintf(stderr, "Cuda error: %s: %s.\n", msg, cudaGetErrorString( err) );
        exit(EXIT_FAILURE);
    }                         
}