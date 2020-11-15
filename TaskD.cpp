#include <iostream>
#include <vector>
#include <string>

struct obj {
	long long value;
	int request;
};

void siftUp(std::vector<obj>& a, int& x) {
	while (a[x].value < a[x / 2].value && x > 1) {
		std::swap(a[x], a[x / 2]);
		x /= 2;
	}
}

void siftDown(std::vector<obj>& a, int& x) {
	while (2 * x < a.size()) {
		if (a[x].value > a[2 * x].value && ( 2 * x + 1 == a.size() || a[2 * x].value <= a[2 * x + 1].value)) {
			std::swap(a[x], a[2 * x]);
			x *= 2;
		} else if (2 * x + 1 < a.size() && a[x].value > a[2 * x + 1].value) {
			std::swap(a[x], a[2 * x + 1]);
			x = 2 * x + 1;
		} else {
			break;
		}
	}
}

long long getMin(const std::vector<obj>& a) {
	return a[1].value;
}

void extractMin(std::vector<obj>& a) {
	a[1] = a[a.size() - 1];
	int j = 1;
	siftDown(a, j);
	a.erase(a.begin() + a.size() - 1);
}

void insert(std::vector<obj>& a, const long long& x, const int i) {
	obj y;
	y.value = x;
	y.request = i;
	a.push_back(y);
	int j = a.size() - 1;
	siftUp(a, j);
}

void decreaseKey(std::vector<obj>& a, const int i, const long long x) {
	int index = 0;
	for (int j = 1; j < a.size(); ++j) {
		if (a[j].request == i) {
			index = j;
			break;
		}
	}
	a[index].value -= x;
	siftUp(a, index);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::vector<obj> a;
	int q;
	std::cin >> q;
	obj y;
	y.value = 0;
	a.push_back(y);
	for (int i = 1; i <= q; ++i) {
		std::string s;
		std::cin >> s;
		if (s == "insert") {
			long long x;
			std::cin >> x;
			insert(a, x, i);
		} else if (s == "decreaseKey") {
			int i;
			long long x;
			std::cin >> i >> x;
			decreaseKey(a, i, x);
		} else if (s == "getMin") {
			std::cout << getMin(a) << "\n";
		} else if (s == "extractMin") {
			extractMin(a);
		} 
	}
}

