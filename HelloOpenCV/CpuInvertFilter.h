#ifndef CPUINVERTFILTER_H_
#define CPUINVERTFILTER_H_

#include "common.h"

#include "SingleImageFilter.h"

/**
	\file CpuInvertFilter.h
	CpuInvertFilter s�n�f�n�n tan�m�n� i�erir.
*/

/**
	Cpu image invert filtre s�n�f�.

	Bu s�n�f SingleImageFilter s�n�f�n� ger�ekleyerek CPU �zerinde resmin negatifini almaya yarar.
*/

class CpuInvertFilter : public SingleImageFilter
{

public:

	CpuInvertFilter()
	{
	}

	/** G�r�nt�n�n RGB kanallar�n�n tersini al�r. */
	virtual void FilterImage(char* imageData)
	{
		// copy imageData to GPU.
		for(int i=0; i<3*width*height; i++)
		{
			*( imageData + i ) = ( unsigned char ) ( 255 - *( imageData + i ) ); // invert every pixel.
		}
	}

private:

	DISALLOW_COPY_AND_ASSIGN(CpuInvertFilter);

};

#endif // CPUINVERTFILTER_H_