#ifndef __FMATRIX_h__
#define __FMATRIX_h__

#include <vmath.h>

template <typename T>
class FMatrix
{
public:
	FMatrix() {}
	FMatrix<T> operator*(const FMatrix<T>& a) 
	{

	}
private:
	T m[4][4];
};

#endif