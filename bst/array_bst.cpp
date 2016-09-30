#include <iostream>
using namespace std;

#define SIZE 5
#define ROOT 1

//to get left child, use 2n
//to get right child, use 2n+1


//Preorder Traversal
//	print the node
// 	Recurse left subtree
//	Recurse right subtree

//Inorder
//	Recurse left subtree
//	Print the node
//	Recurse right subtree

//Postorder Traversal
//	Recurse left subtree
// 	Recurse right subtree
//	print the node

class binTree
{
public:
	binTree();
	void inorder(int);
	void postorder(int);
	void preorder(int);
private:
	int tree[SIZE];
};

binTree::binTree()
{
	for(int i = 1; i < SIZE; i++)
		tree[i] = i;
}

void binTree::inorder(int index)
{
	if(index < SIZE)
	{
		inorder(2*index);
		cout << tree[index] << " " << endl;
		inorder(2*index+1);
	}

}

void binTree::postorder(int index)
{
	if(index < SIZE)
	{
		postorder(2*index);
		postorder(2*index+1);
		cout << tree[index] << " " << endl;
	}
}

void binTree::preorder(int index)
{
	if(index < SIZE)
	{
		cout << tree[index] << " " << endl;
		preorder(2*index);
		preorder(2*index+1);
	}
}


int main ()
{
	binTree tree;
//	tree.preorder(ROOT);
//	tree.inorder(ROOT);
	tree.postorder(ROOT);
}




