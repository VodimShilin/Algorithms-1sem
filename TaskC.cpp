#include <iostream>
#include <vector>
#include <ctime>

long long max(const std::vector<long long>& a) {
    int max_ = 0;
    for (int i = 1; i < a.size(); ++i) {
        if (a[i] > a[max_]) {
            max_ = i;
        }
    }
    return a[max_];
}

long long random() {
    int64_t x = rand();
    x <<= 15;
    x |= rand();
    x <<= 15;
    x |= rand();
    x <<= 3;
    x |= rand() & 0b111;
    return x;
}

void partition(std::vector<long long>& a, std::vector<long long>& less_then_x, std::vector<long long>& equal_to_x, std::vector<long long>& more_then_x, int x) {
    int i = 0;
    while (i < a.size()) {
        int is_pushed = 0;
        if (a[i] < x) {
            less_then_x.push_back(a[i]);
            ++is_pushed;
            std::swap(a[i], a[a.size() - 1]);
            a.pop_back();
        }
        if (is_pushed == 0) ++i;
    }
    i = 0;
    while (i < a.size()) {
        int is_pushed = 0;
        if (a[i] == x) {
            equal_to_x.push_back(a[i]);
            ++is_pushed;
            std::swap(a[i], a[a.size() - 1]);
            a.pop_back();
        }
        if (is_pushed == 0) ++i;
    }
    i = 0;
    while (i < a.size()) {
        int is_pushed = 0;
        if (a[i] > x) {
            more_then_x.push_back(a[i]);
            ++is_pushed;
            std::swap(a[i], a[a.size() - 1]);
            a.pop_back();
        }
        if (is_pushed == 0) ++i;
    }
}

int kth(std::vector<long long> a, int k) {
    while (a.size() > 1) {
        int x = a[a.size() / 2];
        std::vector<long long> less_then_x, equal_to_x, more_then_x;
        partition(a, less_then_x, equal_to_x, more_then_x, x);
        if (less_then_x.size() > k) {
            a = less_then_x;
        }
        else if (less_then_x.size() + equal_to_x.size() > k) {
            a = equal_to_x;
            k -= less_then_x.size();
        }
        else {
            a = more_then_x;
            k -= less_then_x.size() + equal_to_x.size();
        }
    }
    return a[0];
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long n, k;
    std::cin >> n >> k;
    std::vector<long long> a;
    for (int i = 1; i <= n; ++i) {
        long long x;
        std::cin >> x;
        a.push_back(x);
    }
    std::cout << kth(a, k);
    return 0;
}