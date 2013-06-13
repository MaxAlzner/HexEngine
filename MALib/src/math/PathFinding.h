#ifndef __PATHFINDING_H_
#define __PATHFINDING_H_

struct NodeLink;

template <class T> class PathNode
{
public:
	PathNode();
	PathNode(const char* name, T& data);
	~PathNode();

	void connect(PathNode* node, float weight = 1.0f);
	void disconnect(PathNode* node);
	void disable(PathNode* node);
	void enable(PathNode* node);
	bool connected(PathNode* node, bool alsoEnabled = false, NodeLink** outLink = NULL);

	bool path(PathNode* dest, std::vector<PathNode*>* outPath, float depth = -1.0f);

	void set(T& data);

	std::string name;
	std::vector<NodeLink*> links;
	T data;

private:
	bool isAdjacent(PathNode* node, std::vector<PathNode*>* ignore = NULL);
	PathNode* getAdjacent(unsigned int i);
};

struct NodeLink
{
	void* in;
	void* out;
	float weight;
	bool enabled;
};

template <class T> PathNode<T>::PathNode()
{
	this->name = "";
}
template <class T> PathNode<T>::PathNode(const char* name, T& data)
{
	this->name = name;
	this->set(data);
}
template <class T> PathNode<T>::~PathNode()
{
	this->adjacent.clear();
}

template <class T> void PathNode<T>::connect(PathNode* node, float weight)
{
	if (!this->connected(node) && !node->connected(this))
	{
		NodeLink* link = new NodeLink;
		link->in = node;
		link->out = this;
		link->weight = weight;
		link->enabled = true;
		this->links.push_back(link);
		node->links.push_back(link);
	}
}
template <class T> void PathNode<T>::disconnect(PathNode* node)
{
	for (unsigned i = 0; i < this->links.size(); i++)
	{
		NodeLink* link = this->links[i];
		if (this->connected(node, false, &link))
		{
			if (link != NULL)
			{
				//this->links.erase(this->links.begin() + i);
			}
		}
	}
}
template <class T> void PathNode<T>::disable(PathNode* node)
{
	NodeLink* link = NULL;
	if (this->connected(node, false, &link))
	{
		if (link != NULL) link->enabled = false;
	}
}
template <class T> void PathNode<T>::enable(PathNode* node)
{
	NodeLink* link = NULL;
	if (this->connected(node, false, &link))
	{
		if (link != NULL) link->enabled = true;
	}
}
template <class T> bool PathNode<T>::connected(PathNode* node, bool alsoEnabled, NodeLink** outLink)
{
	for (unsigned i = 0; i < this->links.size(); i++)
	{
		NodeLink* link = this->links[i];
		if (link->in == node || link->out == node)
		{
			if (alsoEnabled && !link->enabled) return false;
			if (outLink != NULL) *outLink = link;
			return true;
		}
	}
	return false;
}

template <class T> bool PathNode<T>::isAdjacent(PathNode* node, std::vector<PathNode*>* ignore)
{
	if (node == NULL || ignore == NULL) return false;
	
	for (unsigned i = 0; i < this->links.size(); i++)
	{
		PathNode* adjacent = this->getAdjacent(i);
		bool check = adjacent == node;
		if (!check) continue;

		bool isIgnored = false;
		if (ignore != NULL)
		{
			for (unsigned k = 0; k < ignore->size(); k++)
			{
				if (adjacent == (*ignore)[k]) isIgnored = true;
			}
		}

		if (check && !isIgnored) return true;
	}

	return false;
}
template <class T> bool PathNode<T>::path(PathNode* dest, std::vector<PathNode*>* outPath, float depth)
{
	if (dest == NULL || outPath == NULL) return false;
	
	outPath->push_back(this);
	if (this == dest)
		return true;

	if (this->connected(dest, true))
	{
		outPath->push_back(dest);
		return true;
	}

	if (this->links.size() <= 1) return false;

#if 0
	PathNode* next = NULL;
	float last = -1.0f;
	for (unsigned i = 0; i < this->links.size(); i++)
	{
		NodeLink* link = this->links[i];

		float result = depth - link->weight;
		if (result < 0.0f && depth > 0.0f) continue;
		
		PathNode* node = this->getAdjacent(i);
		bool alreadyBeen = false;
		for (unsigned k = 0; k < outPath->size(); k++)
		{
			if ((*outPath)[k] == node) alreadyBeen = true;
		}
		if (alreadyBeen) continue;

		if (last > result)
		{
			last = result;
			next = node;
		}
	}

	if (next != NULL)
	{
		outPath->push_back(next);
		return next->path(dest, outPath, last);
	}
#elif 1
	PathNode* checking = this;
	while (true)
	{
		for (unsigned i = 0; i < checking->links.size(); i++)
		{
			PathNode* node = checking->getAdjacent(i);
			if (node == dest)
			{
				outPath->push_back(node);
				return true;
			}
			else if (node->connected(dest, true))
			{
				outPath->push_back(node);
				outPath->push_back(dest);
				return true;
			}
			for (unsigned k = 0; k < node->links.size(); k++)
			{
				PathNode* child = node->getAdjacent(k);
				if (child->connected(dest, true))
				{
					outPath->push_back(node);
					outPath->push_back(child);
					outPath->push_back(dest);
					return true;
				}
			}
		}
		return false;
	}
#else
	bool ring = false;
	for (unsigned i = 0; i < this->links.size(); i++)
	{
		PathNode* node = this->getAdjacent(i);
		ring = ring || node->path(dest, outPath, depth);
	}
	return ring;
#endif

	return false;
}

template <class T> void PathNode<T>::set(T& data)
{
	this->data = data;
}

template <class T> PathNode<T>* PathNode<T>::getAdjacent(unsigned int i)
{
	if (i >= this->links.size()) return NULL;

	NodeLink* link = this->links[i];

	if (this == link->in) return (PathNode<T>*)link->out;
	return (PathNode<T>*)link->in;
}

#endif