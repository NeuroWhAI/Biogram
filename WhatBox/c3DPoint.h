#pragma once
#include <d3dx9.h>

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 3D점 좌표 템플릿 클래스
// Desc : 원하는 자료형으로 x, y, z의 3값과 인터페이스를 제공
///////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class c3DPoint
{
public:
	c3DPoint();
	c3DPoint( CONST T* );
    c3DPoint( CONST T& );
    c3DPoint( T x, T y, T z );


public:
	T x, y, z;


public:
	// casting
    operator T* ();
    operator CONST T* () const;

	// assignment operators
    c3DPoint& operator += ( CONST c3DPoint& );
    c3DPoint& operator -= ( CONST c3DPoint& );
    c3DPoint& operator *= ( T );
    c3DPoint& operator /= ( T );

    // unary operators
    c3DPoint operator + () const;
    c3DPoint operator - () const;

    // binary operators
    c3DPoint operator + ( CONST c3DPoint& ) const;
    c3DPoint operator - ( CONST c3DPoint& ) const;
    c3DPoint operator * ( T ) const;
    c3DPoint operator / ( T ) const;

    bool operator == ( CONST c3DPoint& ) const;
    bool operator != ( CONST c3DPoint& ) const;
};




//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 함수 정의
//////////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T>
c3DPoint<T>::c3DPoint()
	: x(static_cast<T>(0))
	, y(x)
	, z(x)
{
	
}


template<typename T>
c3DPoint<T>::c3DPoint( CONST T* )
	: x(T->x)
	, y(T->y)
	, z(T->z)
{
	
}


template<typename T>
c3DPoint<T>::c3DPoint( CONST T& )
	: x(T.x)
	, y(T.y)
	, z(T.z)
{
	
}


template<typename T>
c3DPoint<T>::c3DPoint( T _x, T _y, T _z )
	: x(_x)
	, y(_y)
	, z(_z)
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
c3DPoint<T>::operator T* ()
{
	return &x;
}


template<typename T>
c3DPoint<T>::operator CONST T* () const
{
	return &x;
}


template<typename T>
c3DPoint<T>& c3DPoint<T>::operator += ( CONST c3DPoint<T>& right )
{
	x += right.x;
	y += right.y;
	z += right.z;

	return *this;
}


template<typename T>
c3DPoint<T>& c3DPoint<T>::operator -= ( CONST c3DPoint<T>& right )
{
	x -= right.x;
	y -= right.y;
	z -= right.z;

	return *this;
}


template<typename T>
c3DPoint<T>& c3DPoint<T>::operator *= ( T right )
{
	x *= right.x;
	y *= right.y;
	z *= right.z;

	return *this;
}


template<typename T>
c3DPoint<T>& c3DPoint<T>::operator /= ( T right )
{
	x /= right.x;
	y /= right.y;
	z /= right.z;

	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
c3DPoint<T> c3DPoint<T>::operator + () const
{
	return c3DPoint<T>(+x, +y, +z);
}


template<typename T>
c3DPoint<T> c3DPoint<T>::operator - () const
{
	return c3DPoint<T>(-x, -y, -z);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
c3DPoint<T> c3DPoint<T>::operator + ( CONST c3DPoint<T>& right ) const
{
	return c3DPoint<T>(x+right.x, y+right.y, z+right.z);
}


template<typename T>
c3DPoint<T> c3DPoint<T>::operator - ( CONST c3DPoint<T>& right ) const
{
	return c3DPoint<T>(x-right.x, y-right.y, z-right.z);
}


template<typename T>
c3DPoint<T> c3DPoint<T>::operator * ( T right ) const
{
	return c3DPoint<T>(x*right, y*right, z*right);
}


template<typename T>
c3DPoint<T> c3DPoint<T>::operator / ( T right ) const
{
	return c3DPoint<T>(x/right, y/right, z/right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
bool c3DPoint<T>::operator == ( CONST c3DPoint<T>& right ) const
{
	return (x == right.x  &&  y == right.y  &&  z == right.z);
}


template<typename T>
bool c3DPoint<T>::operator != ( CONST c3DPoint<T>& right ) const
{
	return (x != right.x  ||  y != right.y  ||  z != right.z);
}

