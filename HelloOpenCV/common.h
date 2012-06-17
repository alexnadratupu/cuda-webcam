#ifndef COMMON_H_
#define COMMON_H_

/** 
	\file common.h 
	Her s�n�fta i�erilen ba�l�k dosyas�.
	
	Her s�n�fta kullan�lan fonksiyonlar� ve makrolar� i�eren ba�l�k dosyas�.
*/

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
/** Kopyalama yarat�c�s� ve atama operat�r�n� private olarak i�aretler. */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#endif // COMMON_H_