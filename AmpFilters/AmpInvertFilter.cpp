#include "AmpInvertFilter.h"
#include "amp.h"

using namespace concurrency;

/**
	Cpu image invert filtre s�n�f�.

	Bu s�n�f SingleImageFilter s�n�f�n� ger�ekleyerek CPU �zerinde resmin negatifini almaya yarar.
*/

/** G�r�nt�n�n RGB kanallar�n�n tersini al�r. */
void AmpInvertFilter::FilterImage(char* imageData)
{
	unsigned int* iImageData = (unsigned int*)malloc(3*width*height * sizeof(int));

	// AMP'de char kullanilamiyor, veriyi int'e donustur.
	for(int i=0; i<3*width*height; i++)
	{
		*( iImageData + i ) = ( unsigned int ) *( imageData + i );
	}

	const int size = 3*width*height;
	
	// Veri �zerinde do�rudan �al��abiliriz. (in-place).
	array_view<unsigned int, 1> img(size, iImageData);	
		
	/*
	for(int i=0; i<3*width*height; i++)
	{
		*( imageData + i ) = ( unsigned char ) ( 255 - *( imageData + i ) ); // her pikselin her kanal�n�n negatifini al.
	}*/

	parallel_for_each(         
        img.extent,         
        [=](index<1> idx) restrict(amp)
		{
			// Her kanal�n negatifi al�n�r.
			img[idx] = 255 - img[idx];
		}
    );

	img.synchronize();

	// AMP'de char kullanilamiyor, veriyi char'e donustur.
	for(int i=0; i<3*width*height; i++)
	{
		*( imageData + i ) = ( char ) *( iImageData + i );
	}
}
