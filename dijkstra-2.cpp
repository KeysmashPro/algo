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

using triplet = tuple<u64,u64,u64>;
using duplet = tuple<u64,u64>;

constexpr u64 inf = 1LL << 62;


/* Max ~ 4 billon vertex | max path length ~ 10^15 */
i64 dijkstra(vec<vec<duplet>> &g, vec<u32> &p, u32 start, u32 finish)
{
    u32 n = g.size();
    priority_queue<duplet, vec<duplet>, greater<>> pq;
    vec<u64> dist(n, inf);
    vec<u32> anc(n, 0);
    pq.push({0,start});
    
    while (pq.size()) {
        auto [d, v] = pq.top(); pq.pop();
        if (dist[v] < d) continue;
        if (v == finish) break;

        for (auto [t, w] : g[v]) {
            if (dist[t] < d + w) continue;
            dist[t] = d + w;
            anc[t] = v; 
            pq.push({d + w, t});
        }
    }

    if (dist[finish] == inf) return -1;

    for (u32 v = finish; v != start;) {
        p.push_back(v);
        v = anc[v];
    }
    p.push_back(start);

    return dist[finish];
}

i32 main() {
    fstream file("input.txt");
    u32 n, m; 
    file >> n >> m;
    vec<vec<duplet>> g(n);

    for (u32 f, t, w, i = 0; i < m; ++i) {
        file >> f >> t >> w; f--; t--;
        g[f].push_back({t, w});
        g[t].push_back({f, w});
    }

    vec<u32> p;
    u32 res = dijkstra(g, p, 0, 3);
    cout << res << '\n';

    if(res == - 1) return 0;

    for (i32 i = p.size() - 1; i >= 0; --i)  {
        cout << p[i] + 1 << ' ';
    }
    cout << endl;
    return 0;
}
