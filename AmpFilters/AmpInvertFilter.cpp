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
	auto data = reinterpret_cast<unsigned int*>(imageData);

	const int size = 3*width*height;
	array_view<const unsigned int, 1> img(size, data);
	array_view<unsigned int, 1> result(size, data);
	result.discard_data();

	/*
	for(int i=0; i<3*width*height; i++)
	{
		*( imageData + i ) = ( unsigned char ) ( 255 - *( imageData + i ) ); // her pikselin her kanal�n�n negatifini al.
	}*/

	parallel_for_each( 
        // Define the compute domain, which is the set of threads that are created.
        img.extent, 
        // Define the code to run on each thread on the accelerator.
        [=](index<1> idx) restrict(amp)
		{
			result[idx] = 255 - img[idx];
		}
    );
}
