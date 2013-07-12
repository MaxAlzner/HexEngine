#ifndef _MA_HASHTABLE_H_
#define _MA_HASHTABLE_H_
_MALIB_BEGIN

#define MA_HASHTABLE_DEFAULT_SIZE 32

template <class K, class T> class MALIB_API HASHTABLE
{
public:
	HASHTABLE();
	~HASHTABLE();

	void add(const K& key, const T& item);
	T& get(const K& key);
	K& find(const T& item);
	bool check(const K& key);
	bool contains(const T& item);
	bool associated(const K& key, const T& item);
	void remove(const K& key);
	
	void clear();
	unsigned int length();
	
	T& operator[](const K& key);

private:
	ARRAY<K> keys;
	ARRAY<T> values;
};

template <class K, class T> HASHTABLE<K, T>::HASHTABLE()
{
	this->keys.resize(MA_HASHTABLE_DEFAULT_SIZE);
	this->values.resize(MA_HASHTABLE_DEFAULT_SIZE);
}
template <class K, class T> HASHTABLE<K, T>::~HASHTABLE()
{
	this->clear();
}

template <class K, class T> void HASHTABLE<K, T>::add(const K& key, const T& item)
{
	unsigned int index = 0;
	if (!this->keys.contains(key, &index)) 
		index = this->keys.add(key);

	this->values.insert(item, index);
}
template <class K, class T> T& HASHTABLE<K, T>::get(const K& key)
{
	unsigned int index = 0;
	this->keys.contains(key, &index);

	return this->values[index];
}
template <class K, class T> K& HASHTABLE<K, T>::find(const T& item)
{
	unsigned int index = 0;
	this->values.contains(item, &index);

	return this->keys[index];
}
template <class K, class T> bool HASHTABLE<K, T>::check(const K& key)
{
	return this->keys.contains(key);
}
template <class K, class T> bool HASHTABLE<K, T>::contains(const T& item)
{
	return this->values.contains(item);
}
template <class K, class T> bool HASHTABLE<K, T>::associated(const K& key, const T& item)
{
	unsigned int index = 0;
	if (!this->keys.contains(key, &index)) return false;
	if (this->values[index] != item) return false;

	return true;
}
template <class K, class T> void HASHTABLE<K, T>::remove(const K& key)
{
	unsigned int index = 0;
	if (!this->keys.contains(key, &index)) return;

	//this->keys[index] = 0;
	//this->values[index] = 0;
	T item = this->values[index];
	this->keys.remove(key);
	this->values.remove(item);
}
	
template <class K, class T> void HASHTABLE<K, T>::clear()
{
	this->keys.clear();
	this->values.clear();
	this->keys.resize(HASHTABLE_DEFAULT_SIZE);
	this->values.resize(HASHTABLE_DEFAULT_SIZE);
}
template <class K, class T> unsigned int HASHTABLE<K, T>::length()
{
	return this->keys.length();
}
	
template <class K, class T> T& HASHTABLE<K, T>::operator[](const K& key)
{
	return this->get(key);
}

_MALIB_END
#endif