//tree.h
#ifndef TREE_H
#define TREE_H
#define MAX_CHILDREN	10



template<class K>
class node
{
public:
	
	K *key;
	
	node *children[MAX_CHILDREN];
	node *father;
	int index;
	
	int numberOfChildren;
	int level;
	
	node(K &newkey);
	~node(){};
	
	int createChild(K &newkey);
	int deleteChild(int idx);
};

template<class K>
class tree
{
public:
	
	node<K> *root;
	node<K> *current;
	
	int currentChildIndex;
	int levels;
	
	tree(K &newkey);
	~tree();
	
	K* getCurrentChildKey();
	
	//returns 1 on success, 0 on failure
	int forward();
	int backward();
	int nextChild();
	int previousChild();
	int init();
	void deleteTree();


	
private:
	
	int recursiveDelete(node<K> &n);
	
	
};

#include "tree.cpp"	
#endif
