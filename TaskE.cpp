#include <iostream>
#include <vector>

void siftUp(std::vector<long long>& a, long long i) {
	while (a[i] > a[i / 2] && i > 1) {
		std::swap(a[i], a[i / 2]);
		i /= 2;
	}
}

void siftDown(std::vector<long long>& a, long long i) {
	while (i * 2 < a.size()) {
		if (a[i] < a[2 * i] && (2 * i + 1 == a.size() || a[2 * i] >= a[2 * i + 1])) {
			std::swap(a[i], a[2 * i]);
			i *= 2;
		} else if (2 * i + 1 < a.size() && a[i] < a[2 * i + 1]) {
			std::swap(a[i], a[2 * i + 1]);
			i = 2 * i + 1;
		} else {
			break;
		}
	}
}

void insert(std::vector<long long>& a, long long x, const long long k) {
	if (a.size() <= k) {
		a.push_back(x);
		siftUp(a, a.size() - 1);
	} else {
		if (a[1] > x) {
			a[1] = x;
			siftDown(a, 1);
		}
	}
}

void minSiftUp(std::vector<long long>& a, long long i) {
	if (i > 1 && a[i] < a[i / 2]) {
		std::swap(a[i], a[i / 2]);
		i /= 2;
	}
}

void minSiftDown(std::vector<long long>& a, long long i) {
	while (i * 2 < a.size()) {
		if (a[i] > a[2 * i] && (2 * i + 1 == a.size() || a[2 * i] <= a[2 * i + 1])) {
			std::swap(a[i], a[2 * i]);
			i *= 2;
		}
		else if (2 * i + 1 < a.size() && a[i] > a[2 * i + 1]) {
			std::swap(a[i], a[2 * i + 1]);
			i = 2 * i + 1;
		}
		else {
			break;
		}
	}
}

long long extractMin(std::vector<long long>& a) {
	long long min_ = a[1];
	a[1] = a[a.size() - 1];
	a.erase(a.begin() + a.size() - 1);
	minSiftDown(a, 1);
	return min_;
}

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	long long n, k;
	std::cin >> n >> k;
	std::vector<long long> a;
	a.push_back(0);
	for (long long i = 1; i <= n; ++i) {
		long long x;
		std::cin >> x;
		insert(a, x, k);
	}
	for (long long i = a.size() - 1; i >= 1; --i) {

		minSiftDown(a, i);
	}
	std::cout << "\n";
	while (a.size() > 1) {
		std::cout << extractMin(a) << "\n";
	}
}