#ifndef SINGLEIMAGEFILTERCHAIN_H_
#define SINGLEIMAGEFILTERCHAIN_H_

/** 
	\file SingleImageFilterChain.h
	SingleImageFilterChain s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include <vector>

#include "common.h"

#include "cudaCommon.h"

#include "SingleImageFilter.h"

/**
	Bir veya birden fazla filtrenin tek bir filtre gibi uygulanmas�n� sa�layan s�n�f.

	FilterImage metodu �a�r�ld���nda AppendFilter metodu ile eklenen filtreleri eklenme s�ras�na uygun olarak zincir gibi CPU veya GPU �zerinde �al��t�r�r.
	Eklenebilen filtrelerin tipi ISingleImageFilter tipindedir.
*/
class SingleImageFilterChain : public SingleImageFilter
{
private:
	std::vector<ISingleImageFilter*> vecFilters;

	DISALLOW_COPY_AND_ASSIGN(SingleImageFilterChain);

public:

	/**
		SingleImageFilterChain yarat�c�s�.	
	*/
	SingleImageFilterChain()		
	{		
	}

	/**
		Zincire filtre ekler.

		\param filter Eklenecek filtre.
	*/
	void AppendFilter(ISingleImageFilter* filter)
	{
		assert( filter && "AppendFilter: filter is invalid." );

		vecFilters.push_back( filter );

		if ( isInited )
		{
			filter->InitFilter( width, height );
		}
	}

	/**
		Son eklenen filtreyi zincirden ��kart�r.

		��kart�lan filtrenin ReleaseFilter metodu �a�r�l�r.
	*/
	void RemoveLastFilter()
	{
		ISingleImageFilter* lastFilter = vecFilters.back();
		assert( lastFilter && "RemoveLastFilter: lastFilter is invalid." );

		lastFilter->ReleaseFilter();

		vecFilters.pop_back();
	}

	/**
		T�m filtreleri siler.

		��kart�lan filtrenin ReleaseFilter metodu �a�r�l�r.
	*/
	void RemoveAll()
	{
		vector<ISingleImageFilter*>::const_iterator fi;
		vector<ISingleImageFilter*>::const_iterator fEnd;

		for (fi = vecFilters.begin(), fEnd = vecFilters.end(); fi != fEnd; fi++)
		{			
			(*fi)->ReleaseFilter();
		}

		vecFilters.clear();
	}
	
	virtual void InitFilter(int width, int height)
	{
		SingleImageFilter::InitFilter(width, height);	

		vector<ISingleImageFilter*>::const_iterator fi;
		vector<ISingleImageFilter*>::const_iterator fEnd;

		for (fi = vecFilters.begin(), fEnd = vecFilters.end(); fi != fEnd; fi++)
		{			
			(*fi)->InitFilter( width, height );
		}
	}

	virtual void FilterImage(char* imageData)
	{
		vector<ISingleImageFilter*>::const_iterator fi;
		vector<ISingleImageFilter*>::const_iterator fEnd;

		for (fi = vecFilters.begin(), fEnd = vecFilters.end(); fi != fEnd; fi++)
		{
			(*fi)->FilterImage( imageData );
		}
	}

	virtual void ReleaseFilter()
	{
		SingleImageFilter::ReleaseFilter();

		vector<ISingleImageFilter*>::const_iterator fi;
		vector<ISingleImageFilter*>::const_iterator fEnd;

		for (fi = vecFilters.begin(), fEnd = vecFilters.end(); fi != fEnd; fi++)
		{
			(*fi)->ReleaseFilter();
		}
	}

};

#endif SINGLEIMAGEFILTERCHAIN_H_