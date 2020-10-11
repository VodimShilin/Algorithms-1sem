#include <iostream>
#include <string>

struct Stack {
	struct Node {
		int value;
		Node* next;
	};

	Node* root = nullptr;
	int stsize = 0;

	void push(int data) {
		Node* temp;
		temp = new Node;
		temp->value = data;
		temp->next = root;
		root = temp;
		++stsize;
	}

	bool isEmpty() {
		return root == nullptr;
	}

	int top() {		
		return root->value;
	}

	void pop() {
		Node* temp;
		temp = root;
		root = root->next;
		delete(temp);
		--stsize;
	}
};

int main() {
	Stack st;
	bool flag = false;
	while (flag == false) {
		std::string s;
		std::cin >> s;
		if (s == "push") {
			int a;
			std::cin >> a;
			st.push(a);
			std::cout << "ok\n";
		}
		else if (s == "pop") {
			if (st.isEmpty() == false) {
				std::cout << st.top() << "\n";
				st.pop();
			}
			else {
				std::cout << "error\n";
			}
		}
		else if (s == "back") {
			if (st.isEmpty() == false) {
				std::cout << st.top() << "\n";
			}
			else {
				std::cout << "error\n";
			}
			
		}
		else if (s == "size") {
			std::cout << st.stsize << "\n";
		}
		else if (s == "clear") {
			while (st.isEmpty() == false) {
				st.pop();
			}
			std::cout << "ok\n";
		}
		else if (s == "exit") {
			flag = true;
			std::cout << "bye";
		}	
	}
	return 0;
}

