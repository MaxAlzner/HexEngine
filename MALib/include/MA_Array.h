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
	ARRAY(uint length);
	~ARRAY();

	uint add(const T& item);
	uint add(const ARRAY& other);
	T& get(uint index);
	void insert(const T& item, uint index);
	bool contains(const T& item, uint* outIndex = 0);
	void remove(const T& item);
	void remove(const ARRAY& other);

	void clear();
	void zero();
	void resize(uint length);
	uint length();
	uint capacity();
	T* pointer();
	
	T& operator[](uint index);
	ARRAY& operator+(const T& item);
	ARRAY& operator-(const T& item);
	ARRAY& operator+(const ARRAY& other);
	ARRAY& operator-(const ARRAY& other);
	ARRAY& operator+=(const T& item);
	ARRAY& operator-=(const T& item);
	ARRAY& operator+=(const ARRAY& other);
	ARRAY& operator-=(const ARRAY& other);
	ARRAY& operator++();
	ARRAY& operator--();

private:
	uint items;
	uint size;
	T* data;
};

template <class T> ARRAY<T>::ARRAY()
{
	this->items = 0;
	this->size = 0;
	this->data = 0;
}
template <class T> ARRAY<T>::ARRAY(uint length)
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

template <class T> uint ARRAY<T>::add(const T& item)
{
	if (this->items >= this->size) this->resize(this->size * this->size);
	this->data[this->items] = item;
	uint index = this->items;
	this->items++;
	return index;
}
template <class T> uint ARRAY<T>::add(const ARRAY<T>& other)
{
	uint index = this->items;
	this->resize(other.items);
	for (unsigned i = 0; i < other.items; i++) 
		this->add(((ARRAY<T>&)other).get(i));
	this->items += other.items;
	return index;
}
template <class T> T& ARRAY<T>::get(uint index)
{
	if (index >= this->size) index = this->size - 1;
	return this->data[index];
}
template <class T> void ARRAY<T>::insert(const T& item, uint index)
{
	if (index >= this->size) this->resize(this->size * this->size);
	this->data[index] = item;
	if (index >= this->items) this->items += (index + 1) - this->items;
	else this->items++;
}
template <class T> bool ARRAY<T>::contains(const T& item, uint* outIndex)
{
	if (this->items < 1 || this->size < 1) return false;
	for (unsigned i = 0; i < this->items; i++)
	{
		if (this->data[i] == item)
		{
			if (outIndex != 0) *outIndex = i;
			return true;
		}
	}
	return false;
}
template <class T> void ARRAY<T>::remove(const T& item)
{
	if (this->items < 1 || this->size < 1) return;
	uint index = 0;
	if (!this->contains(item, &index)) return;
	if (index >= this->size) index = this->size - 1;
	for (unsigned i = index + 1; i < this->items; i++) 
		this->data[i - 1] = this->data[i];
	if (this->items > 0) this->items--;
}
template <class T> void ARRAY<T>::remove(const ARRAY<T>& other)
{
	if (other.items < 1 || other.size < 1) return;
	for (unsigned i = 0; i < other.items; i++)
	{
		uint index = 0;
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
	this->items = 0;
}
template <class T> void ARRAY<T>::resize(uint length)
{
	this->size = length;
	if (this->size < 1)
	{
		if (this->data == 0) return;
		this->zero();
		delete [] this->data;
		this->data = 0;
		this->items = 0;
	}
	else
	{
		T* clean = new T[this->size];
		if (this->items > this->size) this->items = this->size;
		for (uint i = 0; i < this->items; i++) 
			clean[i] = this->data[i];

		if (this->data != 0) delete [] this->data;
		this->data = clean;
	}
}
template <class T> uint ARRAY<T>::length()
{
	return this->items;
}
template <class T> uint ARRAY<T>::capacity()
{
	return this->size;
}
template <class T> T* ARRAY<T>::pointer()
{
	return this->data;
}

template <class T> T& ARRAY<T>::operator[](uint index)
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
template <class T> ARRAY<T>& ARRAY<T>::operator+=(const T& item)
{
	this->add(item);
	return *this;
}
template <class T> ARRAY<T>& ARRAY<T>::operator-=(const T& item)
{
	this->remove(item);
	return *this;
}
template <class T> ARRAY<T>& ARRAY<T>::operator+=(const ARRAY<T>& other)
{
	this->add(other);
	return *this;
}
template <class T> ARRAY<T>& ARRAY<T>::operator-=(const ARRAY<T>& other)
{
	this->remove(other);
	return *this;
}
template <class T> ARRAY<T>& ARRAY<T>::operator++()
{
	this->resize(this->size + 1);
	return *this;
}
template <class T> ARRAY<T>& ARRAY<T>::operator--()
{
	this->resize(this->size - 1);
	return *this;
}

_MALIB_END
#endif