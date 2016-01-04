#include "Utility.h"

#include <cmath>



























namespace Utility
{
	template <typename T>
	bool removeFrom(std::vector<T>* pList, const T& target)
	{
		int index = 0;
		for (const auto& item : *pList)
		{
			if (item == target)
			{
				pList->erase(pList->begin() + index);

				return true;
			}

			++index;
		}


		return false;
	}

	//###########################################################

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
		: x(static_cast<T>(right.x))
		, y(static_cast<T>(right.y))
	{

	}


	template <typename T>
	template <typename RT>
	PointT<T>::PointT(const SizeT<RT>& right)
		: x(static_cast<T>(right.width))
		, y(static_cast<T>(right.height))
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

	//-----------------------------------------------------------

	template <typename T>
	T PointT<T>::getLength() const
	{
		return std::sqrt(x*x + y*y);
	}


	template <typename T>
	T PointT<T>::getLengthSq() const
	{
		return (x*x + y*y);
	}

	//-----------------------------------------------------------

	template <typename T>
	PointT<T> PointT<T>::operator+ () const
	{
		return *this;
	}


	template <typename T>
	PointT<T> PointT<T>::operator- () const
	{
		return PointT<T>(-x, -y);
	}


	template <typename T>
	template <typename RT>
	PointT<T> PointT<T>::operator+ (const PointT<RT>& right) const
	{
		return PointT<T>(x + right.x, y + right.y);
	}

	template <typename T>
	template <typename RT>
	PointT<T> PointT<T>::operator- (const PointT<RT>& right) const
	{
		return PointT<T>(x - right.x, y - right.y);
	}

	template <typename T>
	template <typename RT>
	PointT<T> PointT<T>::operator* (RT right) const
	{
		return PointT<T>(x * right, y * right);
	}

	template <typename T>
	template <typename RT>
	PointT<T> PointT<T>::operator/ (RT right) const
	{
		return PointT<T>(x / right, y / right);
	}

	template <typename T>
	template <typename RT>
	PointT<T>& PointT<T>::operator+= (const PointT<RT>& right)
	{
		x += right.x;
		y += right.y;

		return *this;
	}

	template <typename T>
	template <typename RT>
	PointT<T>& PointT<T>::operator-= (const PointT<RT>& right)
	{
		x -= right.x;
		y -= right.y;

		return *this;
	}

	template <typename T>
	template <typename RT>
	PointT<T>& PointT<T>::operator*= (RT right)
	{
		x *= right;
		y *= right;

		return *this;
	}

	template <typename T>
	template <typename RT>
	PointT<T>& PointT<T>::operator/= (RT right)
	{
		x /= right;
		y /= right;

		return *this;
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
	SizeT<T>::SizeT(const PointT<RT>& right)
		: width(right.x)
		, height(right.y)
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

	//-----------------------------------------------------------

	template <typename T>
	SizeT<T> SizeT<T>::operator* (T right) const
	{
		return{ width*right, height*right };
	}


	template <typename T>
	SizeT<T> SizeT<T>::operator/ (T right) const
	{
		return{ width/right, height/right };
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


	template <typename T>
	const ColorT<T> ColorT<T>::WHITE(255, 255, 255);
	template <typename T>
	const ColorT<T> ColorT<T>::YELLOW(255, 255, 0);
	template <typename T>
	const ColorT<T> ColorT<T>::GREEN(0, 255, 0);
	template <typename T>
	const ColorT<T> ColorT<T>::BLUE(0, 0, 255);
	template <typename T>
	const ColorT<T> ColorT<T>::RED(255, 0, 0);
	template <typename T>
	const ColorT<T> ColorT<T>::MAGENTA(255, 0, 255);
	template <typename T>
	const ColorT<T> ColorT<T>::BLACK(0, 0, 0);
	template <typename T>
	const ColorT<T> ColorT<T>::ORANGE(255, 127, 0);
	template <typename T>
	const ColorT<T> ColorT<T>::GRAY(166, 166, 166);
}