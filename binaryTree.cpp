#include <iostream>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

struct Node {
	int data;
	struct Node *left, *right;

	Node(int d) : data(d) {};
};

// 构造二叉树
Node* createTree();
// 递归前序遍历
void preOrder(Node *node);

/* 
非递归前序遍历1
首先输出父节点，然后将父节点入栈，指针指向其左孩子，重复操作。
当左孩子为空时，栈顶出栈，指针指向其右孩子，重复上一操作。
该方法先输出节点数据，再进行节点入栈操作，出入栈过程类似于非递归中序遍历。
*/
void PreOrder1(Node *node);

/*
非递归前序遍历2
该方法比较传统，也比较简单，首先将根节点入栈。
栈不为空时，栈顶出栈，当该节点不为空时，输出数据，依次将右孩子、左孩子入栈。
每次都是在节点出栈时进行输出操作。
*/
void PreOrder2(Node *node);

// 递归中序遍历
void inOrder(Node *node); 

// 非递归中序遍历
void InOrder(Node *node);  

// 递归后序遍历
void postOrder(Node *node);

/*
非递归后续遍历1
双压法，每个节点入栈两次，第一次出栈时，表明该节点孩子没有访问过，将其右孩子、左孩子各入栈两次。
第二次出栈时，表明该节点孩子已经访问过，输出该节点数据。
*/
void PostOrder1(Node *node);

/*
非递归后续遍历2
标记法，以一个指针标记上一个访问过的节点，若当前节点没有孩子或上一访问节点是其左孩子且其没有右孩子
或上一访问节点是其右孩子时，表明该节点孩子已经访问过了(没有孩子也算访问过)，可以访问当前节点。
该方法需要注意，入栈时必须判断节点是否为空。
*/
void PostOrder2(Node *node);

// 层次遍历
void levelOrder(Node *node);

// 二叉树深度
int depth(Node *node);

// 1 2 4 0 0 5 0 0 3 0 6 0 0

int main() {
	Node *root = createTree();
	
	cout << "递归前序遍历: ";
	preOrder(root);
	cout << endl;

	cout << "非递归前序遍历1: ";
	PreOrder1(root);
	cout << endl;

	cout << "非递归前序遍历2: ";
	PreOrder2(root);
	cout << endl;

	cout << "递归中序遍历: ";
	inOrder(root);
	cout << endl;

	cout << "非递归中序遍历: ";
	InOrder(root);
	cout << endl;

	cout << "递归后序遍历: ";
	postOrder(root);
	cout << endl;

	cout << "非递归后序遍历1: ";
	PostOrder1(root);
	cout << endl;

	cout << "非递归后序遍历2: ";
	PostOrder2(root);
	cout << endl;

	cout << "层次遍历: ";
	levelOrder(root);
	cout << endl;

	cout << "二叉树深度: " << depth(root);
	
	cout << endl;

	return 0;
}

Node* createTree() {
	Node *node = nullptr;
	int data = 0;
	cin >> data;
	if (data != 0) {
		node = new Node(data);
		node->left = createTree();
		node->right = createTree();
	}
	return node;
}

void preOrder(Node *node) {
	if (node != nullptr) {
		cout << node->data;
		preOrder(node->left);
		preOrder(node->right);
	}
}

void PreOrder1(Node *node) {
	stack<Node *> st;
	Node *p = node;

	while (p != nullptr) {
		cout << p->data;
		st.push(p);
		p = p->left;
	}

	while (!st.empty()) {
		p = st.top();
		st.pop();

		p = p->right;
		while (p != nullptr) {
			cout << p->data;
			st.push(p);
			p = p->left;
		}
	}
}

void PreOrder2(Node *node) {
	stack<Node *> st;
	st.push(node);

	Node *p;
	while (!st.empty()) {
		p = st.top();
		st.pop();

		if (p != nullptr) {
			cout << p->data;
			st.push(p->right);
			st.push(p->left);
		}
	}
}

void inOrder(Node *node) {
	if (node != nullptr) {
		inOrder(node->left);
		cout << node->data;
		inOrder(node->right);
	}
}

void InOrder(Node * node) {
	stack<Node *> st;
	Node *p = node;

	while (p != nullptr) {
		st.push(p);
		p = p->left;
	}

	while (!st.empty()) {
		p = st.top();
		st.pop();
		cout << p->data;
		p = p->right;
		while (p != nullptr) {
			st.push(p);
			p = p->left;
		}
	}
}

void postOrder(Node *node) {
	if (node != nullptr) {
		postOrder(node->left);
		postOrder(node->right);
		cout << node->data;
	}
}

void PostOrder1(Node *node) {
	stack<Node *> st;
	st.push(node);
	st.push(node);

	Node *p;
	while (!st.empty()) {
		p = st.top();
		st.pop();

		if (p != nullptr) {
			if (!st.empty() && p == st.top()) {
				st.push(p->right);
				st.push(p->right);

				st.push(p->left);
				st.push(p->left);
			}
			else {
				cout << p->data;
			}
		}
	}
}

void PostOrder2(Node *node){
	stack<Node *> st;
	st.push(node);

	Node *p, *pre = nullptr;
	while (!st.empty()) {
		p = st.top();

		if ((p->left == nullptr && p->right == nullptr)
			|| (p->left == pre && p->right == nullptr)
			|| p->right == pre) {
			cout << p->data;
			st.pop();
			pre = p;
		}
		else {
			if (p->right != nullptr) {
				st.push(p->right);
			}
			if (p->left != nullptr) {
				st.push(p->left);
			}
		}
	}
}

void levelOrder(Node *node) {
	queue<Node *> q;
	q.push(node);
	Node *p;

	while (!q.empty()) {
		p = q.front();
		q.pop();

		if (p != nullptr) {
			cout << p->data;
			q.push(p->left);
			q.push(p->right);
		}
	}
}

int depth(Node *node) {
	if (node == nullptr) {
		return 0;
	}
	else {
		return 1 + max(depth(node->left), depth(node->right));
	}
}