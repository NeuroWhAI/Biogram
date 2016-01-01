#pragma once



























namespace Utility
{
	template <typename T>
	class PointT
	{
	public:
		PointT();

		PointT(T x, T y);
		
		template <typename RT>
		PointT(const PointT<RT>& right);

		template <typename RT>
		PointT<T>& operator= (const PointT<RT>& right);

	public:
		T x, y;
	};
	using Point = PointT<int>;
	using PointF = PointT<float>;


	template <typename T>
	class SizeT
	{
	public:
		SizeT();

		SizeT(T width, T height);

		template <typename RT>
		SizeT(const SizeT<RT>& right);

		template <typename RT>
		SizeT<T>& operator= (const SizeT<RT>& right);

	public:
		T width, height;
	};
	using Size = SizeT<int>;
	using SizeF = SizeT<float>;


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
	};
	using Color = ColorT<int>;
	using ColorF = ColorT<float>;
}


#include "Utility.inl"