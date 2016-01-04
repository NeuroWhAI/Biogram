#pragma once

#include <vector>



























namespace Utility
{
	template <typename T>
	bool removeFrom(std::vector<T>* pList, const T& target);


	template <typename T>
	class SizeT;

	template <typename T>
	class PointT
	{
	public:
		PointT();

		PointT(T x, T y);
		
		template <typename RT>
		PointT(const PointT<RT>& right);

		template <typename RT>
		PointT(const SizeT<RT>& right);

		template <typename RT>
		PointT<T>& operator= (const PointT<RT>& right);

	public:
		T x, y;

	public:
		T getLength() const;
		T getLengthSq() const;

	public:
		PointT<T> operator+ () const;

		PointT<T> operator- () const;

		template <typename RT>
		PointT<T> operator+ (const PointT<RT>& right) const;
		
		template <typename RT>
		PointT<T> operator- (const PointT<RT>& right) const;

		template <typename RT>
		PointT<T> operator* (RT right) const;

		template <typename RT>
		PointT<T> operator/ (RT right) const;
	
		template <typename RT>
		PointT<T>& operator+= (const PointT<RT>& right);

		template <typename RT>
		PointT<T>& operator-= (const PointT<RT>& right);

		template <typename RT>
		PointT<T>& operator*= (RT right);

		template <typename RT>
		PointT<T>& operator/= (RT right);
	};
	using Point = PointT<int>;
	using PointF = PointT<float>;
	using PointD = PointT<double>;


	template <typename T>
	class SizeT
	{
	public:
		SizeT();

		SizeT(T width, T height);

		template <typename RT>
		SizeT(const SizeT<RT>& right);

		template <typename RT>
		SizeT(const PointT<RT>& right);

		template <typename RT>
		SizeT<T>& operator= (const SizeT<RT>& right);

	public:
		T width, height;

	public:
		SizeT<T> operator* (T right) const;
		SizeT<T> operator/ (T right) const;
	};
	using Size = SizeT<int>;
	using SizeF = SizeT<float>;
	using SizeD = SizeT<double>;


	template <typename T>
	class RectT
	{
	public:
		RectT();

		RectT(T left, T top, T right, T bottom);

		template <typename RT>
		RectT(const RectT<RT>& right);

		template <typename RT>
		RectT<T>& operator= (const RectT<RT>& right);

	public:
		T left, top, right, bottom;
	};
	using Rect = RectT<int>;
	using RectF = RectT<float>;
	using RectD = RectT<double>;


	template <typename T>
	class ColorT
	{
	public:
		ColorT();

		ColorT(T r, T g, T b, T a = T(255));

		template <typename RT>
		ColorT(const ColorT<RT>& right);

		template <typename RT>
		ColorT<T>& operator= (const ColorT<RT>& right);

	public:
		T r, g, b, a;

	public:
		static const ColorT<T> WHITE;
		static const ColorT<T> YELLOW;
		static const ColorT<T> BLUE;
		static const ColorT<T> GREEN;
		static const ColorT<T> RED;
		static const ColorT<T> MAGENTA;
		static const ColorT<T> BLACK;
		static const ColorT<T> ORANGE;
		static const ColorT<T> GRAY;
	};
	using Color = ColorT<int>;
	using ColorF = ColorT<float>;
	using ColorD = ColorT<double>;
}


#include "Utility.inl"