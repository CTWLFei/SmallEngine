#ifndef __FVECTOR_h__
#define __FVECTOR_h__

#include <vmath.h>

//T stand for template
//F stand for formula

template <typename T, const int N>
class TVecN
{
public:
	typedef class TVecN<T, N> my_type;

	inline TVecN()
	{
		for (n = 0; n < len; n++)
		{
			data[n] = T(0);
		}
	}
	// Construction from scalar
	inline TVecN(T s)
	{
		int n;
		for (n = 0; n < len; n++)
		{
			data[n] = s;
		}
	}

	inline TVecN& operator=(const TVecN& that)
	{
		assign(that);
		return *this;
	}

	inline TVecN operator*(const TVecN& a)
	{
		my_type returnValue;
		for (int i = 0; i < N; i++)
			returnValue.m[i] = m[i] * a[i];
		return returnValue;
	}

	inline TVecN operator*(const T& a)
	{
		my_type returnValue;
		for (int i = 0; i < N; i++)
			returnValue.m[i] = m[i] * a;
		return returnValue;
	}

	inline TVecN operator+(const TVecN& a)
	{
		my_type returnValue;
		for (int i = 0; i < N; i++)
			returnValue.m[i] = m[i] + a[i];
		return returnValue;
	}

	inline TVecN operator-(const TVecN& a)
	{
		my_type returnValue;
		for (int i = 0; i < N; i++)
			returnValue.m[i] = m[i] - a[i];
		return returnValue;
	}

	inline TVecN operator/(const TVecN& a)
	{
		my_type returnValue;
		for (int i = 0; i < N; i++)
			returnValue.m[i] = m[i] / a[i];
		return returnValue;
	}

	inline TVecN operator/(const T& a)
	{
		my_type returnValue;
		for (int i = 0; i < N; i++)
			returnValue.m[i] = m[i] / a;
		return returnValue;
	}

	inline TVecN& operator*=(const TVecN& that)
	{
		assign(*this * that);
		return *this;
	}
	inline TVecN& operator*=(const T& that)
	{
		assign(*this * that);
		return *this;
	}

	inline TVecN& operator+=(const TVecN& that)
	{
		assign(*this + that);
		return *this;
	}

	inline TVecN& operator-=(const TVecN& that)
	{
		assign(*this - that);
		return *this;
	}

	inline TVecN& operator/=(const TVecN& that)
	{
		assign(*this / that);
		return *this;
	}
	inline TVecN& operator/=(const T& that)
	{
		assign(*this / that);
		return *this;
	}

	inline T& operator[](int i){ return m[i]; }
	inline const T& operator[](int i) const { return m[i]; }
	inline int size() { return N; }
	inline operator const T* () const { return &m[0]; }

protected:
	T m[N];

	inline void assign(const TVecN& that)
	{
		for (int i = 0; i < N; i++)
		{
			m[i] = that.m[i];
		}
	}
};

template <typename T>
class TVec2: public TVecN<T, 2>
{
public:
	typedef TVecN<T, 2> base;

	inline TVec2(){}
	inline TVec2(const base& a) : base(a) { }
	inline TVec2(T x, T y)
	{
		m[0] = x;
		m[1] = y;
	}
	
};

template <typename T>
class TVec3 : public TVecN<T, 3>
{
public:
	typedef TVecN<T, 3> base;

	inline TVec3() {}
	inline TVec3(const base& a) : base(a) { }
	inline TVec3(T x, T y, T z)
	{
		m[0] = x;
		m[1] = y;
		m[2] = z;
	}
	inline TVec3(TVec2<T>& v, T z)
	{
		m[0] = v[0];
		m[1] = v[1];
		m[2] = z;
	}
	inline TVec3(T x, TVec2<T>& v)
	{
		m[0] = z;
		m[1] = v[0];
		m[2] = v[1];
	}

};

template <typename T>
class TVec4 : public TVecN<T, 4>
{
public:
	typedef TVecN<T, 4> base;

	inline TVec4() {}
	inline TVec4(const base& a) : base(a) { }
	// TVec4(x, y, z, w);
	inline TVec4(T x, T y, T z, T w)
	{
		m[0] = x;
		m[1] = y;
		m[2] = z;
		m[3] = w;
	}

	// Vec4(v, z, w);
	inline TVec4(const TVec2<T>& v, T z, T w)
	{
		m[0] = v[0];
		m[1] = v[1];
		m[2] = z;
		m[3] = w;
	}

	// Vec4(x, v, w);
	inline TVec4(T x, const TVec2<T>& v, T w)
	{
		m[0] = x;
		m[1] = v[0];
		m[2] = v[1];
		m[3] = w;
	}

	// Vec4(x, y, v);
	inline TVec4(T x, T y, const TVec2<T>& v)
	{
		m[0] = x;
		m[1] = y;
		m[2] = v[0];
		m[3] = v[1];
	}

	// Vec4(v1, v2);
	inline TVec4(const TVec2<T>& u, const TVec2<T>& v)
	{
		m[0] = u[0];
		m[1] = u[1];
		m[2] = v[0];
		m[3] = v[1];
	}

	// Vec4(v, w);
	inline TVec4(const TVec3<T>& v, T w)
	{
		m[0] = v[0];
		m[1] = v[1];
		m[2] = v[2];
		m[3] = w;
	}

	// Vec4(x, v);
	inline TVec4(T x, const TVec3<T>& v)
	{
		m[0] = x;
		m[1] = v[0];
		m[2] = v[1];
		m[3] = v[2];
	}
};


typedef TVec2<float> FVec2;
typedef TVec2<int> FVec2i;
typedef TVec2<unsigned int> FVec2u;
typedef TVec2<double> FVec2d;

typedef TVec3<float> FVec3;
typedef TVec3<int> FVec3i;
typedef TVec3<unsigned int> FVec3u;
typedef TVec3<double> FVec3d;

typedef TVec4<float> FVec4;
typedef TVec4<int> FVec4i;
typedef TVec4<unsigned int> FVec4u;
typedef TVec4<double> FVec4d;

#endif