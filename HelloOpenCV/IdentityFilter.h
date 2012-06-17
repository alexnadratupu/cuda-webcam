#ifndef IDENTITYFILTER_H_
#define IDENTITYFILTER_H_

#include "common.h"
#include "SingleImageFilter.h"

/**
	\file IdentityFilter.h
	IdentityFilter s�n�f�n�n tan�m�n� i�erir.
*/

/**
	Bu s�n�f SingleImageFilter s�n�f�n� bo� ger�ekleyerek g�r�nt�de hi� bir de�i�iklik yapmaz.
*/

class IdentityFilter : public SingleImageFilter
{
public:
	IdentityFilter()
	{
	}

	/** G�r�nt�de de�i�iklik yapmadan ��kar. */
	virtual void FilterImage(char* imageData)
	{
		return; // imaj� de�i�tirmeden d�n.
	}

private:
	DISALLOW_COPY_AND_ASSIGN(IdentityFilter);
};

#endif // IDENTITYFILTER_H_