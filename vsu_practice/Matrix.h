//#pragma once
//
//#include <cfloat>
//
//template <typename T>
//class Vector
//{
//public:
//	
//	Vector<T>();
//	Vector<T>(int size);
//	~Vector();
//	
//	T& operator[](int index);
//
//	void init(int size);
//
//private:
//
//	T* _elems;
//};
//
//template <typename T>
//class Matrix
//{
//public:
//
//	Matrix<T>();
//	Matrix<T>(int size);
//	~Matrix();
//
//	Vector<T>& operator[](int index);
//
//	void init(int size);
//
//private:
//
//	Vector<T>** _rows;
//};
//
//
//
//template<typename T>
//inline Vector<T>::Vector()
//	: _elems(nullptr)
//{}
//
//template<typename T>
//inline Vector<T>::Vector(int size)
//{
//	init(size);
//}
//
//
//template<typename T>
//inline void Vector<T>::init(int size)
//{
//	_elems = new T[size];
//	for (int i = 0; i < size; i++)
//	{
//		_elems[i] = FLT_MAX;
//	}
//}
//
//
//template<typename T>
//inline Vector<T>::~Vector()
//{
//	delete[] _elems;
//}
//
//template<typename T>
//inline T& Vector<T>::operator[](int index)
//{
//	return _elems[index];
//}
//
//
//
//
//
//template<typename T>
//inline Matrix<T>::Matrix()
//	: _rows(nullptr)
//{}
//
//template<typename T>
//inline Matrix<T>::Matrix(int size)
//{
//	_rows = new Vector<T>*[size];
//	for (int i = 0; i < size; i++)
//	{
//		_rows[i] = new Vector<T>(size);
//	}
//}
//
//template<typename T>
//inline void Matrix<T>::init(int size)
//{
//	_rows = new Vector<T>*[size];
//	for (int i = 0; i < size; i++)
//	{
//		_rows[i] = new Vector<T>(size);
//	}
//}
//
//template<typename T>
//inline Matrix<T>::~Matrix()
//{
//	delete[] _rows;
//}
//
//template<typename T>
//inline Vector<T>& Matrix<T>::operator[](int index)
//{
//	return *_rows[index];
//}