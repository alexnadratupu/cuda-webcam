#include "FilterFactory.h"

#include "common.h"

#include "AmpInvertFilter.h"

/** 
	\file FilterFactory.cpp
	AmpFilters projesindeki filtreler i�in factory metodlar�n� i�eren dosya.
*/

FILTERAPI ISingleImageFilter* FILTERENTRY GetAmpInvertFilter()
{
	return new AmpInvertFilter();
}