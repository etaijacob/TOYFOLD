//tree.cpp
//#include "tree.h"

template <class K>
node<K>::node(K &newkey):
numberOfChildren(0),
level(0),
father(0),
index(0)
{
	 key = &newkey;
}

template <class K>
int node<K>::createChild(K &newkey)
{
	if(numberOfChildren >= MAX_CHILDREN - 1)
		return -1;
			
	children[numberOfChildren++] = new node(newkey);
	
	children[numberOfChildren - 1]->index = numberOfChildren - 1;
	children[numberOfChildren - 1]->father = this;
	children[numberOfChildren - 1]->level = level + 1;

	return numberOfChildren;
}

template <class K>
int node<K>::deleteChild(int idx)
{
	if(idx >= numberOfChildren || children[idx]->numberOfChildren > 0)
		return -1;
	
	delete children[idx];
	if(numberOfChildren >= 2 && idx != numberOfChildren - 1)
	{	
		children[idx] = children[numberOfChildren - 1];
		children[idx]->index = idx;
	}
	
	
	//cout<<"delete child	idx: "<<idx<<endl;
	return --numberOfChildren;	
}


template <class K>
tree<K>::tree(K &newkey):
currentChildIndex(0)
{
	root = new node<K>(newkey);
	root->father = 0;
	
	current = root;
	levels = 1;	
}

template <class K>
void tree<K>::deleteTree()
{
	recursiveDelete(*root);
}	

template <class K>
tree<K>::~tree()
{
	recursiveDelete(*root);
	delete root;
}

template <class K>
int tree<K>::recursiveDelete(node<K> &n)
{
	static int s = 0;

	//cout<<"rec: "<<s<<endl;
	s++;
	
	if(n.numberOfChildren == 0)
		return 1;
	
	while(n.numberOfChildren)
		if(n.deleteChild(0) == -1)
			recursiveDelete(*(n.children[0]));		
	
	return 1;		
}

template <class K>
K* tree<K>::getCurrentChildKey()
{
	return current->children[currentChildIndex]->key;
}
		
//go to next generation
template <class K>
int tree<K>::forward()
{
	if(current->numberOfChildren == 0)
		return 0;
	
	current = current->children[currentChildIndex];
	currentChildIndex = 0;
			 
	return 1;
}

//go to father
template <class K>
int tree<K>::backward()
{
	if(current->father == 0)
		return 0;
	
	currentChildIndex = current->index;
	current = current->father;
	 
	return 1;
}

//cyclic
template <class K>
int tree<K>::nextChild()
{	
	if(current->numberOfChildren == 0)
		return -1;

	currentChildIndex = (currentChildIndex + 1)%current->numberOfChildren;
	return 1;
}

//cyclic
template <class K>
int tree<K>::previousChild()
{
	if(current->numberOfChildren == 0)
		return -1;
	
	if(currentChildIndex == 0)
	{
		currentChildIndex = current->numberOfChildren - 1;
		return 1;
	}

	--currentChildIndex;
	return 1;
}

template <class K>
int tree<K>::init()
{
	currentChildIndex = 0;
	current = root;
	
	return 1;
}

#if 0
int main(int argc, char **argv)
{
	
	return 1;
}
#endif


