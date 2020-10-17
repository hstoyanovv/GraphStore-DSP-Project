#ifndef MyVector_H
#define MyVector_H
#include<iostream>

template<typename T>
class MyVector
{
private:
	T * data;
	size_t size;
	size_t capacity;

	void copyFrom(const MyVector<T> & rhs);
	void clear();
	void resize();

public:
	MyVector();
	MyVector(const MyVector<T> & rhs);
	MyVector<T> & operator=(const MyVector<T> & rhs);
	~MyVector();

	void push_back(const T & value);
	void erase(const size_t idx);

	const size_t getsize() const;
	T & operator[](size_t idx);
	bool contains(const T & value);
	const bool empty() const;

};

#endif

template<typename T>
inline void MyVector<T>::copyFrom(const MyVector<T> & rhs)
{
	data = new T[rhs.size];
	for (size_t i = 0; i < rhs.size; i++)
	{
		data[i] = rhs.data[i];
	}

	size = capacity = rhs.size;
}

template<typename T>
inline void MyVector<T>::clear()
{
	delete[] data;
}

template<typename T>
inline void MyVector<T>::resize()
{
	if (capacity == 0)
		capacity = 2;
	else
		capacity *= 2;

	T* data1 = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data1[i] = data[i];
	}

	delete[] data;
	data = data1;
}

template<typename T>
inline MyVector<T>::MyVector()
{
	data = nullptr;
	size = 0;
	capacity = 0;
}

template<typename T>
inline MyVector<T>::MyVector(const MyVector<T> & rhs) :data(nullptr), size(0), capacity(0)
{
	copyFrom(rhs);
}

template<typename T>
inline MyVector<T> & MyVector<T>::operator=(const MyVector<T> & rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}

	return *this;
}

template<typename T>
inline MyVector<T>::~MyVector()
{
	clear();
}

template<typename T>
inline void MyVector<T>::push_back(const T & value)
{
	if (size >= capacity)
		resize();

	data[size++] = value;
}

template<typename T>
inline void MyVector<T>::erase(const size_t idx)
{
	for (size_t i = idx; i < size - 1; i++)
	{
		std::swap(data[i], data[i + 1]);
	}

	size--;
}

template<typename T>
inline const size_t MyVector<T>::getsize() const
{
	return size;
}

template<typename T>
inline T & MyVector<T>::operator[](size_t idx)
{
	return data[idx];
}

template<typename T>
inline bool MyVector<T>::contains(const T & value)
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == value)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
inline const bool MyVector<T>::empty() const
{
	return size == 0;
}
