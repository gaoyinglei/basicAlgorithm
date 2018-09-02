#include <iostream>

using namespace std;

struct Node {
	int data;
	struct Node *next;
};

Node* create();

/*
传递指针进函数的时候，相当于是传值进入函数，只不过这个值本身是个指针。
因此，在函数内改变指针，不会改变函数外指针。
想要改变，可以传递指针的指针作为参数。
*/
// 递归反转链表
Node* reverse1(Node *head);

// 非递归反转链表
Node* reverse2(Node *head);

void print(Node *head);

int main() {
	Node *head = create();
	print(head);

	head = reverse1(head);
	print(head);

	head = reverse2(head);
	print(head);

	return 0;
}

Node* create() {
	Node *head = nullptr, *p = nullptr;
	int data;

	while (cin >> data) {
		if (data == 0) {
			break;
		}
		if (head == nullptr) {
			head = new Node();
			head->data = data;
			p = head;
		}
		else {
			p->next = new Node();
			p = p->next;
			p->data = data;
		}
	}

	return head;
}

Node* reverse1(Node *head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	Node *p = reverse1(head->next);

	head->next->next = head;
	head->next = nullptr;

	return p;
}

Node* reverse2(Node *head) {
	if (head == nullptr) {
		return head;
	}

	Node *next = head->next;
	Node *cur = head;
	Node *pre = nullptr;

	while (next != nullptr) {
		cur->next = pre;
		pre = cur; 
		cur = next;
		next = next->next;
	}

	cur->next = pre;
	return cur;
}

void print(Node *head) {
	Node *p = head;

	while (p != nullptr) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}