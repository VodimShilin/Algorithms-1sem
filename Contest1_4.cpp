#include <iostream>
#include <deque>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;

	std::deque<int> first;
	std::deque<int> second;

	for (int i = 1; i <= n; ++i) {
		char c;
		std::cin >> c;
		if (c == '+') {
			int x;
			std::cin >> x;
			second.push_back(x);
		} else if (c == '*') {
			int x;
			std::cin >> x;
			if (first.size() <= second.size()) {
				first.push_back(x);
			} else {
				second.push_front(x);
			}
		} else {
			std::cout << first.front() << '\n';
			first.pop_front();	
		}

		if (first.size() < second.size()) {
			first.push_back(second.front());
			second.pop_front();
		}
	}

}



