#include <iostream>
#include <fstream>
#include <queue>

std::queue<long long> mergeSort(std::queue<long long> q, int& count) {
    if (q.size() == 1) {
        return q;
    }
    else {
        std::queue<long long> first_queue;
        std::queue<long long> second_queue;
        int length = q.size();
        int counter= 0;
        int first_q_counter = 0;
        int second_q_counter = 0;
        for (int i = 1; i <= length / 2; ++i) {
            first_queue.push(q.front());
            q.pop();
        }
        first_queue = mergeSort(first_queue, count);
        for (int i = length / 2 + 1; i <= length; ++i) {
            second_queue.push(q.front());
            q.pop();
        }
        second_queue = mergeSort(second_queue, count);
        std::queue<long long> sort_queue;
        while ((first_queue.size() != 0) && (second_queue.size() != 0)) {
            ++counter;
            if (first_queue.front() <= second_queue.front()) {
                ++first_q_counter;
                sort_queue.push(first_queue.front());
                first_queue.pop();
                count += counter - first_q_counter;
            }
            else {
                sort_queue.push(second_queue.front());
                second_queue.pop();
            }
        }
        while (first_queue.size() != 0) {
            sort_queue.push(first_queue.front());
            first_queue.pop();
            count += counter - first_q_counter;
        }
        while (second_queue.size() != 0) {
            sort_queue.push(second_queue.front());
            second_queue.pop();
        }
        return sort_queue;
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
    a = mergeSort(a, count);
    std::ofstream outf("inverse.out");
    outf << count;
    outf.close();
}
