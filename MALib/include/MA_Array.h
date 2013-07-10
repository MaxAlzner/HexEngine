#ifndef _MA_ARRAY_H_
#define _MA_ARRAY_H_
_MALIB_BEGIN

#ifndef _INC_STRING
#include <string.h>
#endif

template <class T> class MALIB_API ARRAY
{
public:
	ARRAY();
	ARRAY(unsigned int length);
	~ARRAY();

	unsigned int add(const T& item);
	unsigned int add(const ARRAY& other);
	T& get(unsigned int index);
	void insert(const T& item, unsigned int index);
	bool contains(const T& item, unsigned int* outIndex = 0);
	void remove(const T& item);
	void remove(const ARRAY& other);

	void clear();
	void zero();
	void resize(unsigned int length);
	unsigned int length();
	unsigned int capacity();
	T* pointer();

	T& operator[](unsigned int index);
	ARRAY& operator+(const T& item);
	ARRAY& operator-(const T& item);
	ARRAY& operator+(const ARRAY& other);
	ARRAY& operator-(const ARRAY& other);
	void operator+=(const T& item);
	void operator-=(const T& item);
	void operator+=(const ARRAY& other);
	void operator-=(const ARRAY& other);
	void operator++();
	void operator--();

private:
	unsigned int items;
	unsigned int size;
	T* data;
};

template <class T> ARRAY<T>::ARRAY()
{
	this->items = 0;
	this->size = 0;
	this->data = 0;
}
template <class T> ARRAY<T>::ARRAY(unsigned int length)
{
	this->items = 0;
	this->size = length;
	this->data = new T[this->size];
	this->zero();
}
template <class T> ARRAY<T>::~ARRAY()
{
	this->resize(0);
}

template <class T> unsigned int ARRAY<T>::add(const T& item)
{
	if (this->items >= this->size) this->resize(this->items + 1);
	this->data[this->items] = item;
	unsigned int index = this->items;
	this->items++;
	return index;
}
template <class T> unsigned int ARRAY<T>::add(const ARRAY<T>& other)
{
	unsigned int index = this->items;
	this->resize(other.items);
	for (unsigned i = 0; i < other.items; i++) 
		this->add(((ARRAY<T>&)other).get(i));
	this->items += other.items;
	return index;
}
template <class T> T& ARRAY<T>::get(unsigned int index)
{
	if (index >= this->size) index = this->size - 1;
	return this->data[index];
}
template <class T> void ARRAY<T>::insert(const T& item, unsigned int index)
{
	if (index >= this->size) this->resize(index + 1);
	this->data[index] = item;
	if (index >= this->items) this->items += (index + 1) - this->items;
	else this->items++;
}
template <class T> bool ARRAY<T>::contains(const T& item, unsigned int* outIndex)
{
	for (unsigned i = 0; i < this->items; i++)
	{
		if (item == this->data[i])
		{
			if (outIndex != 0) *outIndex = i;
			return true;
		}
	}
	return false;
}
template <class T> void ARRAY<T>::remove(const T& item)
{
	unsigned int index = 0;
	if (!this->contains(item, &index)) return;
	if (index >= this->size) index = this->size - 1;
	for (unsigned i = index + 1; i < this->items; i++) 
		this->data[i - 1] = this->data[i];
	this->items--;
}
template <class T> void ARRAY<T>::remove(const ARRAY<T>& other)
{
	for (unsigned i = 0; i < other.items; i++)
	{
		unsigned int index = 0;
		if (this->contains(other.get(i), &index)) 
			this->remove(index);
	}
}

template <class T> void ARRAY<T>::clear()
{
	this->resize(0);
}
template <class T> void ARRAY<T>::zero()
{
	if (this->size < 1 || this->data == 0) return;
	memset(this->data, 0, sizeof(T) * this->size);
}
template <class T> void ARRAY<T>::resize(unsigned int length)
{
	this->size = length;
	if (this->size == 0)
	{
		if (this->data == 0) return;
		delete [] this->data;
		this->data = 0;
		this->items = 0;
	}
	else
	{
		T* clean = new T[this->size];
		if (this->items > this->size) this->items = this->size;
		for (unsigned i = 0; i < this->items; i++) 
			clean[i] = this->data[i];

		if (this->data != 0) delete [] this->data;
		this->data = clean;
	}
}
template <class T> unsigned int ARRAY<T>::length()
{
	return this->items;
}
template <class T> unsigned int ARRAY<T>::capacity()
{
	return this->size;
}
template <class T> T* ARRAY<T>::pointer()
{
	return this->data;
}

template <class T> T& ARRAY<T>::operator[](unsigned int index)
{
	return this->get(index);
}
template <class T> ARRAY<T>& ARRAY<T>::operator+(const T& item)
{
	this->add(item);
	return *this;
}
template <class T> ARRAY<T>& ARRAY<T>::operator-(const T& item)
{
	this->remove(item);
	return *this;
}
template <class T> ARRAY<T>& ARRAY<T>::operator+(const ARRAY<T>& other)
{
	this->add(other);
	return *this;
}
template <class T> ARRAY<T>& ARRAY<T>::operator-(const ARRAY<T>& other)
{
	this->remove(other);
	return *this;
}
template <class T> void ARRAY<T>::operator+=(const T& item)
{
	this->add(item);
}
template <class T> void ARRAY<T>::operator-=(const T& item)
{
	this->remove(item);
}
template <class T> void ARRAY<T>::operator+=(const ARRAY<T>& other)
{
	this->add(other);
}
template <class T> void ARRAY<T>::operator-=(const ARRAY<T>& other)
{
	this->remove(other);
}
template <class T> void ARRAY<T>::operator++()
{
	this->resize(this->size + 1);
}
template <class T> void ARRAY<T>::operator--()
{
	this->resize(this->size - 1);
}

_MALIB_END
#endif