//fenvick tree
#include <iostream>
#include <vector>

struct Fenvick_tree {
private:
	struct Node {
		long long s = 0;
		long long value = 0;
		long long index = 0;
		long long f = 0;
		long long g = 0;
		Node(long long a, long long index) : value(a), index(index), f(index & (index + 1)), g(index | (index + 1)) {}
		Node() = default;
	};
	std::vector<Node> tree;
public:
	Fenvick_tree(int n) : tree(n) {}
	
	long long sum(long long l, long long r) {
		int sign = 1;
		long long summ = 0;
		for (size_t i = l; i <= r; ++i) {
			summ += tree[i].value * sign;
			sign *= -1;
		}
		return summ;
	}

	void insert(long long a, long long i) {
		tree[i] = Node(a, i);
		tree[i].s = sum(tree[i].f, i);
	}

	void change(long long index, long long j) {
		int sign = 1;
		if (index % 2 == 1) sign = -1;
		long long value = tree[index].value;
		tree[index].value = j;
		for (size_t i = index; i < tree.size(); i = tree[i].g) {
			tree[i].s -= value * sign;
			tree[i].s += tree[index].value * sign;
		}
	}
	
	long long getsum(long long r) {
		long long summ = 0;
		for (long long i = r; i >= 0; i = tree[i].f - 1) {
			summ += tree[i].s;
		}
		return summ;
	}
	
	long long getSum(long long l, long long r) {
		long long summ = 0;
		if (l <= 0) summ = getsum(r);
		else summ = getsum(r) - getsum(l - 1);
		return l % 2 == 0 ? summ : -summ;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	long long n;
	std::cin >> n;
	Fenvick_tree tree = n;
	for (size_t i = 0; i < n; ++i) {
		long long x;
		std::cin >> x;
		tree.insert(x, i);
	}
	long long m;
	std::cin >> m;
	for (size_t i = 0; i < m; ++i) {
		long long w, index, j;
		std::cin >> w >> index >> j;
		if (w == 0) {
			tree.change(index - 1, j);
		} else {
			std::cout << tree.getSum(index - 1, j - 1) << '\n';
		}
	}
}
