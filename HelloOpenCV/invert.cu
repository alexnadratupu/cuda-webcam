#include "invert.h"

/**
	\file invert.cu
	CUDA invert kernelinin launcher metodunu ve kernelini tan�mlar.
*/

/** Kernel 1 griddeki blok boyutu ( BLOCK_SIZE x BLOCK_SIZE kare bloklar ). */
#define BLOCK_SIZE (32)

/** GPU zaman�n� �l�mek i�in 1 yap�n�z. */
#define ENABLE_TIMING_CODE 0

/**	
	G�r�nt�n�n tersini alan kernel.

	\param image [0, 1] aral���na normalize edilmi�, BGR kanal s�ral� g�r�nt�n�n GPU belle�indeki adresi.
	\param width G�r�nt�n�n piksel olarak geni�li�i
	\param height G�r�nt�n�n piksel olarak y�ksekli�i

	
	Metod GPU �zerinde �al���r, ��kt�s�n� image parametresinin �zerine yazar.

	*/
__global__
void gpuInvert(
	float* image,
	int width,
	int height
	)
{
	int row = blockIdx.y * BLOCK_SIZE + threadIdx.y;
	int col = blockIdx.x * BLOCK_SIZE + threadIdx.x;

	int cIdx = ( row * width + col ) * 3; // 3 ile �arp�m RGB i�in, linearIndex.

	// normalize edilmi� pikselleri 1'den ��kartt���m�zda g�r�nt�n�n negatifini alm�� oluruz.
	*( image + cIdx     ) = 1 - *( image + cIdx     ); // Blue kanal�
	*( image + cIdx + 1 ) = 1 - *( image + cIdx + 1 ); // Green kanal�
	*( image + cIdx + 2 ) = 1 - *( image + cIdx + 2 ); // Red kanal�
}

/**
	\ref ptKernelLauncher tipinde metod.

	\param d_Image [0, 1] aral���na normalize edilmi�, BGR kanal s�ral� g�r�nt�n�n GPU belle�indeki adresi.
	\param width G�r�nt�n�n piksel olarak geni�li�i
	\param height G�r�nt�n�n piksel olarak y�ksekli�i

	\ref gpuInvert kernelini Grid ve Block boyutlar�n� ayarlayarak �a��ran metod.
*/
void deviceInvertLaunch(
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

    gpuInvert<<< dimGrid, dimBlock >>>( d_Image, width, height);

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
