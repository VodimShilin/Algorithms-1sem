#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    unsigned long long n;
    long long m, k;
    std::cin >> n >> m >> k;

    std::map<unsigned long long, std::set<long long>> a;
    std::vector<std::set<unsigned long long>> b(m + 1);

    for (long long i = 1; i <= k; ++i) {
        std::string to_do;
        std::cin >> to_do;
        if (to_do == "ADD") {
            long long s;
            unsigned long long e;
            std::cin >> e >> s;
            a[e].insert(s);
            b[s].insert(e);
        } else if (to_do == "LISTSET") {
            long long s;
            std::cin >> s;
            long long inc = 0;
            bool flag = false;
            if (b[s].empty()) std::cout << -1;
            else for (unsigned long long x : b[s]) {
                std::cout << x << " ";
            }
            std::cout << "\n";
        } else if (to_do == "DELETE") {
            long long s;
            unsigned long long e;
            std::cin >> e >> s;
            a[e].erase(s);
            b[s].erase(e);
        } else if (to_do == "CLEAR") {
            long long s;
            std::cin >> s;
            while (!b[s].empty())
            {
                auto it = b[s].begin();
                a[*it].erase(s);
                b[s].erase(*it);

            }
        } else if (to_do == "LISTSETSOF") {
            unsigned long long e;
            std::cin >> e;
            bool flag = false;
            if (a.find(e) != a.end()) {
                if (!a[e].empty()) {
                    flag = true;
                    for (long long x : a[e]) {
                        std::cout << x << " ";
                    }
                }
                else a.erase(e);
            }
            if (flag == false) std::cout << "-1";
            std::cout << "\n";
        }
    }
}
