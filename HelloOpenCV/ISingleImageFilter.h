#ifndef ISINGLEIMAGEFILTER_H_
#define ISINGLEIMAGEFILTER_H_

/**
	\file ISingleImageFilter.h
	ISingleImageFilter aray�z�n�n tan�m�n� i�erir.
*/

/**
	Resim filtreleme i�lemleri i�in ISingleImageFilter aray�z�.

	Aray�zdeki FilterImage metodunu ger�ekleyen s�n�flar g�r�nt� i�leme yapabilirler. 
	Filtreleme i�lemine ba�lamadan �nce bir kere InitFilter metodu �a�r�l�r, 
	filtreleme tekrar yap�lmayacaksa ReleaseFilter metodu �a�r�l�r.
*/

class ISingleImageFilter
{

public:

	/**
		G�r�nt� ile ilgili alloc ve benzeri i�lemlerin yap�lmas�n� sa�lar. 	

		\param width G�r�nt�n�n piksel geni�li�i.
		\param height G�r�nt�n�n piksel y�ksekli�i.
	*/
	virtual void InitFilter(int width, int height) = 0;

	/** 
		G�r�nt�n�n yerinde(in-place) i�lenmesi i�in �a�r�lan metod. 

		\param imageData G�r�nt�n�n BGR kanal s�ral� bellekteki adresi.
	*/
	virtual void FilterImage(char* imageData) = 0;

	/** G�r�nt� ile ilgili kaynaklar�n b�rak�lmas�n� sa�lar. */
	virtual void ReleaseFilter() = 0;

};

#endif // ISINGLEIMAGEFILTER_H_