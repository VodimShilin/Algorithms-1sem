#include <iostream>
#include <fstream>
#include <vector>
#include <string>

long long maxLength(std::vector<long long>& a) {
	long long count = 0;
	for (int i = 0; i < a.size(); ++i) {
		count = (a[i] > count) ? a[i] : count;
	}
	long long i = 1;
	while (count / 256 != 0) {
		i += 1;
		count /= 256;
	}
	return i;
}

int digit(long long x, int inc) {
	long long ten = 1;
	for (int i = 1; i < inc; ++i) {
		ten *= 256;
	}
	long long y = x / ten;
	y %= 256;
	return y;
}

void numberSort(std::vector<long long>& a) {
	long long max_ = maxLength(a);
	int inc = 0;
	while (inc < max_) {
		++inc;
		int numb[256];
		std::vector<long long> a_sort (a.size());
		for (int i = 0; i <= 255; ++i) {
			numb[i] = 0;
		}
		for (int i = 0; i < a.size(); ++i) {
			int x = digit(a[i], inc);
			++numb[x];
		}
		for (int i = 1; i <= 255; ++i) {
			numb[i] += numb[i - 1];
		}
		for (int i = a.size() - 1; i >= 0; --i) {
			int x = digit(a[i], inc);
			a_sort[numb[x] - 1] = a[i];
			--numb[x];
		}
		a = a_sort;
	}
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	long long n;
	std::cin >> n;
	std::vector<long long> a;
	for (long long i = 1; i <= n; ++i) {
		long long inp_v;
		std::cin >> inp_v;
		a.push_back(inp_v);
	}

	numberSort(a);
	std::cout << "\n";
	for (long long i = 0; i < n; ++i) {
		std::cout << a[i] << "\n";
	}
}
