#ifndef _MA_LIST_H_
#define _MA_LIST_H_
_MALIB_BEGIN

template <class T> struct MALIB_API LISTNODE
{
	LISTNODE()
	{
		this->data = 0;
		this->prev = 0;
		this->next = 0;
	}
	T* data;
	LISTNODE* prev;
	LISTNODE* next;
};

template <class T> class MALIB_API LIST
{
public:
	LIST();
	~LIST();

	unsigned int add(const T& item);
	void insert(const T& item, unsigned int index);
	T& get(unsigned int index);
	bool contains(const T& item, unsigned int* outIndex = 0);
	void remove(const T& item);
	
	void stack_push(const T& item);
	void stack_pop();
	void queue_push(const T& item);
	void queue_pop();

	void clear();
	unsigned int length();

	T& operator[](unsigned int index);
	LIST& operator+(const T& item);
	LIST& operator-(const T& item);
	void operator+=(const T& item);
	void operator-=(const T& item);

private:
	unsigned int size;
	LISTNODE<T>* first;
	LISTNODE<T>* last;
	
	LISTNODE<T>* find(unsigned int index);
	LISTNODE<T>* find(T* item, unsigned int* outIndex = 0);
	void append(LISTNODE<T>* prev, LISTNODE<T>* node, LISTNODE<T>* next);
	void destroy(LISTNODE<T>* node);
};

template <class T> LIST<T>::LIST()
{
	this->size = 0;
	this->first = 0;
	this->last = 0;
}
template <class T> LIST<T>::~LIST()
{
	this->clear();
}

template <class T> unsigned int LIST<T>::add(const T& item)
{
	unsigned int index = this->size;
	LISTNODE<T>* node = new LISTNODE<T>;
	node->data = (T*)&item;

	this->append(this->last, node, 0);
	if (this->first == 0) this->first = node;
	this->last = node;

	this->size++;
	return index;
}
template <class T> void LIST<T>::insert(const T& item, unsigned int index)
{
	if (index >= this->size) index = this->size - 1;
	if (index >= this->size - 1 || this->size < 1)
	{
		this->add(item);
		return;
	}
	
	LISTNODE<T>* node = new LISTNODE<T>;
	node->data = (T*)&item;
	if (index < 1)
	{
		this->append(0, node, this->first);
		this->first = node;
	}
	else
	{
		LISTNODE<T>* prev = this->find(index - 1);
		LISTNODE<T>* next = this->find(index);
		this->append(prev, node, next);
	}
	this->size++;
}
template <class T> T& LIST<T>::get(unsigned int index)
{
	if (index >= this->size) index = this->size - 1;
	LISTNODE<T>* node = this->find(index);
	return *node->data;
}
template <class T> bool LIST<T>::contains(const T& item, unsigned int* outIndex)
{
	LISTNODE<T>* node = this->find((T*)&item, outIndex);
	if (node != 0) return true;
	return false;
}
template <class T> void LIST<T>::remove(const T& item)
{
	LISTNODE<T>* node = this->find((T*)&item);
	this->destroy(node);
	this->size--;
}
	
template <class T> void LIST<T>::stack_push(const T& item)
{
	this->add(item);
}
template <class T> void LIST<T>::stack_pop()
{
	if (this->first == 0 && this->last == 0) return;
	LISTNODE<T>* node = this->last;
	this->last = node->prev;
	this->destroy(node);
	this->size--;
}
template <class T> void LIST<T>::queue_push(const T& item)
{
	this->add(item);
}
template <class T> void LIST<T>::queue_pop()
{
	if (this->first == 0 && this->last == 0) return;
	LISTNODE<T>* node = this->first;
	this->first = node->next;
	this->destroy(node);
	this->size--;
}

template <class T> void LIST<T>::clear()
{
	LISTNODE<T>* previous = 0;
	LISTNODE<T>* current = this->first;
	while (true)
	{
		if (current == 0) break;
		previous = current;
		current = current->next;
		delete previous;
	}
	this->first = 0;
	this->last = 0;
	this->size = 0;
}
template <class T> unsigned int LIST<T>::length()
{
	return this->size;
}

template <class T> LISTNODE<T>* LIST<T>::find(unsigned int index)
{
	unsigned int i = 0;
	LISTNODE<T>* current = this->first;
	if (current == 0) 
		return 0;
	bool loop = true;
	if (index == 0) 
		loop = false;
	else if (index >= this->size - 1)
	{
		i = this->size - 1;
		current = this->last;
		loop = false;
	}
	while (loop)
	{
		if (current == 0 || i == index) break;
		current = current->next;
		i++;
	}
	return current;
}
template <class T> LISTNODE<T>* LIST<T>::find(T* item, unsigned int* outIndex)
{
	unsigned int i = 0;
	LISTNODE<T>* current = this->first;
	if (current == 0) 
		return 0;
	bool loop = true;
	if (current->data == item) 
		loop = false;
	else if (this->last != 0 && *this->last->data == *item)
	{
		i = this->size - 1;
		current = this->last;
		loop = false;
	}
	while (loop)
	{
		if (current == 0 || *current->data == *item) break;
		current = current->next;
		i++;
	}
	if (outIndex != 0) *outIndex = i;
	return current;
}
template <class T> void LIST<T>::append(LISTNODE<T>* prev, LISTNODE<T>* node, LISTNODE<T>* next)
{
	node->prev = prev;
	node->next = next;
	if (prev != 0) 
		prev->next = node;
	if (next != 0) 
		next->prev = node;
}
template <class T> void LIST<T>::destroy(LISTNODE<T>* node)
{
	if (node == 0) return;
	LISTNODE<T>* prevNode = node->prev;
	LISTNODE<T>* nextNode = node->next;
	if (prevNode != 0) prevNode->next = 0;
	if (nextNode != 0) nextNode->prev = 0;
	if (this->first == node) this->first = nextNode;
	if (this->last == node) this->last = prevNode;
	delete node;
}

template <class T> T& LIST<T>::operator[](unsigned int index)
{
	return this->get(index);
}
template <class T> LIST<T>& LIST<T>::operator+(const T& item)
{
	this->add(item);
	return this;
}
template <class T> LIST<T>& LIST<T>::operator-(const T& item)
{
	this->remove(item);
	return this;
}
template <class T> void LIST<T>::operator+=(const T& item)
{
	this->add(item);
}
template <class T> void LIST<T>::operator-=(const T& item)
{
	this->remove(item);
}

_MALIB_END
#endif