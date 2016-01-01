#include "Utility.h"



























namespace Utility
{
	template <typename T>
	PointT<T>::PointT()
		: x(T())
		, y(T())
	{

	}


	template <typename T>
	PointT<T>::PointT(T x, T y)
		: x(x)
		, y(y)
	{

	}


	template <typename T>
	template <typename RT>
	PointT<T>::PointT(const PointT<RT>& right)
		: x(right.x)
		, y(right.y)
	{

	}


	template <typename T>
	template <typename RT>
	PointT<T>& PointT<T>::operator=(const PointT<RT>& right)
	{
		if (this == &right) return *this;


		this->x = right.x;
		this->y = right.y;
	}

	//###########################################################

	template <typename T>
	SizeT<T>::SizeT()
		: width(T())
		, height(T())
	{

	}


	template <typename T>
	SizeT<T>::SizeT(T width, T height)
		: width(width)
		, height(height)
	{

	}


	template <typename T>
	template <typename RT>
	SizeT<T>::SizeT(const SizeT<RT>& right)
		: width(right.width)
		, height(right.height)
	{

	}


	template <typename T>
	template <typename RT>
	SizeT<T>& SizeT<T>::operator=(const SizeT<RT>& right)
	{
		if (this == &right) return *this;


		this->width = right.width;
		this->height = right.height;
	}

	//###########################################################

	template <typename T>
	RectT<T>::RectT()
		: left(T())
		, top(T())
		, right(T())
		, bottom(T())
	{

	}


	template <typename T>
	RectT<T>::RectT(T left, T top, T right, T bottom)
		: left(left)
		, top(top)
		, right(right)
		, bottom(bottom)
	{

	}


	template <typename T>
	template <typename RT>
	RectT<T>::RectT(const RectT<RT>& right)
		: left(right.left)
		, top(right.top)
		, right(right.right)
		, bottom(right.bottom)
	{

	}


	template <typename T>
	template <typename RT>
	RectT<T>& RectT<T>::operator=(const RectT<RT>& right)
	{
		if (this == &right) return *this;


		this->left = right.left;
		this->top = right.top;
		this->right = right.right;
		this->bottom = right.bottom;
	}

	//###########################################################

	template <typename T>
	ColorT<T>::ColorT()
		: r(T())
		, g(T())
		, b(T())
		, a(T())
	{

	}


	template <typename T>
	ColorT<T>::ColorT(T r, T g, T b, T a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{

	}


	template <typename T>
	template <typename RT>
	ColorT<T>::ColorT(const ColorT<RT>& right)
		: r(right.r)
		, g(right.g)
		, b(right.b)
		, a(right.a)
	{

	}


	template <typename T>
	template <typename RT>
	ColorT<T>& ColorT<T>::operator=(const ColorT<RT>& right)
	{
		if (this == &right) return *this;


		this->r = right.r;
		this->g = right.g;
		this->b = right.b;
		this->a = right.a;
	}
}