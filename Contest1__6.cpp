#include <iostream>
#include <fstream>
#include <queue>

std::queue<long long> merge_sort(std::queue<long long> q, int& count) {
    if (q.size() == 1) {
        return q;
    } else {
        std::queue<long long> q1;
        std::queue<long long> q2;
        int l = q.size();
        int c = 0;
        int c1 = 0;
        int c2 = 0;
        for (int i = 1; i <= l / 2; ++i) {
            q1.push(q.front());
            q.pop();
        }
        q1 = merge_sort(q1, count);
        for (int i = l / 2 + 1; i <= l; ++i) {
            q2.push(q.front());
            q.pop();
        }
        q2 = merge_sort(q2, count);
        std::queue<long long> q_;
        while ((q1.size() != 0) && (q2.size() != 0)) {
            ++c;
            if (q1.front() <= q2.front()) {
                ++c1;
                q_.push(q1.front());
                q1.pop();
                count += c - c1;
            } else {
                q_.push(q2.front());
                q2.pop();
            }
        }
        while (q1.size() != 0) {
            q_.push(q1.front());
            q1.pop();
            count += c - c1;
        }
        while (q2.size() != 0) {
            q_.push(q2.front());
            q2.pop();
        }
        return q_;
    }
}


int main()
{
    std::ifstream inf("inverse.in");
    std::queue<long long> a;
    int n;
    inf >> n;
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        long long x;
        inf >> x;
        a.push(x);
    }
    a = merge_sort(a, count);
    /*for (int i = 1; i <= n; ++i) {
        std::cout << a.front() << "\n";
        a.pop();
    }*/
    std::ofstream outf("inverse.out");
    outf << count;
    outf.close();
}
