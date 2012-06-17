#ifndef TEX_INVERT_CU
#define TEX_INVERT_CU

/**
	\file texInvert.cu
	CUDA texture invert kernelinin launcher metodunu ve kernelini tan�mlar.
*/

#include "texInvert.h"

texture<float4, 2, cudaReadModeElementType> texInvert1; /**< Kernelde kullan�lan texture sembol�. */

#define BLOCK_SIZE (32) /**< Blok boyutu ( BLOCK_SIZE x BLOCK_SIZE kare blok ). */

/** GPU zaman�n� �l�mek i�in 1 yap�n�z. */
#define ENABLE_TIMING_CODE 0

/**	
	Texture kullanarak g�r�nt�n�n negatifini alan kernel.

	\param image [0, 1] aral���na normalize edilmi�, BGR kanal s�ral� g�r�nt�n�n GPU belle�indeki adresi.
	\param width G�r�nt�n�n piksel olarak geni�li�i
	\param height G�r�nt�n�n piksel olarak y�ksekli�i

	
	Metod GPU �zerinde �al���r, ��kt�s�n� image parametresinin �zerine yazar.

	*/
__global__
void gpuTexInvert(
	float* image,
	int width,
	int height
	)
{
	int row = blockIdx.y * BLOCK_SIZE + threadIdx.y;
	int col = blockIdx.x * BLOCK_SIZE + threadIdx.x;

	int cIdx = ( row * width + col ) * 3; // 3 ile �arp�m RGB i�in, linearIndex.


	float tu = (float)col / width;
	float tv = (float)row / height;

	//float4 texVal = tex2D( tex, k + .5f, i + .5f );
	float4 texVal = tex2D( texInvert1, tu, tv );

	*( image + cIdx )     = 1 - texVal.x;
	*( image + cIdx + 1 ) = 1 - texVal.y;
	*( image + cIdx + 2 ) = 1 - texVal.z;
}

/**
	\ref ptKernelLauncher tipinde metod.

	\param d_Image [0, 1] aral���na normalize edilmi�, BGR kanal s�ral� g�r�nt�n�n GPU belle�indeki adresi.
	\param width G�r�nt�n�n piksel olarak geni�li�i
	\param height G�r�nt�n�n piksel olarak y�ksekli�i

	\ref gpuTexInvert kernelini Grid ve Block boyutlar�n� ayarlayarak �a��ran metod.
*/
void deviceTexInvertLaunch(
	float *d_Image,
	int width,
	int height
	)
{
	 // launch kernel
	dim3 dimBlock( BLOCK_SIZE, BLOCK_SIZE );
    dim3 dimGrid( width / dimBlock.x, height / dimBlock.y );

#if ENABLE_TIMING_CODE

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

#endif

    gpuTexInvert<<< dimGrid, dimBlock >>>( d_Image, width, height);

#if ENABLE_TIMING_CODE
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);

    // block until the device has completed
    cudaThreadSynchronize();
	
	printf("gpuInvert kernel time: %.3f ms\n", elapsedTime);
#endif

	cudaThreadSynchronize();

    // check if kernel execution generated an error
    // Check for any CUDA errors
    checkCUDAError("kernel invocation");
}


#endif