#pragma once

class ISingleImageFilter
{
public:

	// �maj ile ilgili alloc ve benzeri i�lemleri yapar.
	virtual void InitFilter(int width, int height) = 0;

	// �maj� yerinde i�leyen fonksiyon (in-place).
	virtual void FilterImage(char* image) = 0;

	virtual void ReleaseFilter() = 0;
};

class SingleImageFilter : public ISingleImageFilter
{
protected:
	bool isInited;
	bool isReleased;
	int height;
	int width;

public:

	virtual ~SingleImageFilter()
	{
	}

	SingleImageFilter(void)
		: isInited(false), isReleased(false), height(0), width(0)
	{
		
	}

	virtual void InitFilter(int width, int height)
	{
		this->width = width;
		this->height = height;
		this->isInited = true;
	}

	virtual void ReleaseFilter()
	{
		this->isReleased = true;
	}
};
