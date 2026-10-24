#include <climits>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

template <typename T>
using vec = std::vector<T>;

using namespace std;
using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;
using i32 = int;

using triplet = tuple<u32,u32,u32>;
using duplet = tuple<u64,u64>;

constexpr u64 inf = 1LL << 62;


/* Max ~ 4 billon vertex | max path length ~ 10^15 */
u64 dijkstra(vec<vec<duplet>> &g, u32 start, u32 finish)
{
    u32 n = g.size();
    priority_queue<duplet, vec<duplet>, greater<>> pq;
    vec<u64> dist(n, inf);
    pq.push({0,start});
    
    while (pq.size()) {
        auto [d, v] = pq.top(); pq.pop();
        if (dist[v] != inf) continue;
        if (v == finish) return d;
        dist[v] = d;

        for (auto [t, w] : g[v]) {
            if (dist[t] != inf) continue;
            pq.push({d + w, t});
        }
    }
    return 0;
}

i32 main() {
    ifstream file("test.txt");
    u32 n, m; file >> n >> m;
    vec<vec<duplet>> g(n);

    for (u32 f, t, w, i = 0; i < m; ++i) {
        file >> f >> t >> w; f--; t--;
        g[f].push_back({t, w});
        g[t].push_back({f, w});
    }

    cout << dijkstra(g, 0, 1) << '\n';
    return 0;
}
