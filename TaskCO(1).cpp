#include <iostream>
#include <vector>
#include <ctime>

void partition(std::vector<long long>& a, long long begin, long long end, long long x) {
    long long i = begin;
    long long left_i = begin;
    long long right_i = end - 1;
    long long x_i = left_i;
    long long is_x = left_i;
    while (right_i > left_i) {
        while (left_i < right_i && a[left_i] < x) {
            ++left_i;
        }
        while (right_i > left_i && a[right_i] > x) {
            --right_i;
        }
        x_i = left_i;
        if (a[left_i] == x) {
            while (x_i <= right_i && a[x_i] >= x) {
                ++x_i;
            }
        }
        is_x = left_i + 1;
        if (x_i > right_i) {
            while (is_x <= right_i && a[is_x] > x) {
                ++is_x;
            }
        }
        if (a[left_i] != x ) {
            std::swap(a[left_i], a[right_i]);
            if (a[left_i] != x) ++left_i;
            --right_i;
        } else if (a[left_i] == x && x_i <= right_i) {
            std::swap(a[left_i], a[x_i]);
            ++left_i;
        } else if (a[left_i] == x && is_x <= right_i) {
            ++left_i;
            std::swap(a[left_i], a[is_x]);
        } else break;
    }

}


void search(const std::vector<long long>& a, long long k, long long& begin, long long& end, const long long x) {
    long long less_x = -1;
    long long is_x = -1;
    for (long long i = begin; i < end; ++i) {
        if (less_x == -1 && a[i] == x) {
            less_x = i;
        } else if (is_x == -1 && a[i] > x) {
            is_x = i;
        }
    }
    if (less_x > k) {
        end = less_x;
    } else if (is_x > k || (less_x != -1 && is_x == -1)) {
        begin = less_x;
        end = less_x;
    } else {
        begin = is_x;
    }
}

int kth(std::vector<long long>& a, long long k) {
    long long begin = 0;
    long long end = a.size();
    while (end - begin > 1) {
        long long x =a[(begin + end) / 2];
        partition(a, begin, end, x);
        search(a, k, begin, end, x);
    }
    return a[begin];
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