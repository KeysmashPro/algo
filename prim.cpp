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
using duplet = tuple<u32,u32>;

u64 prim(vec<vec<duplet>> &g, vec<triplet> &tree)
{
    u64 n = g.size(); u64 tree_sum = 0;
    priority_queue<triplet, vec<triplet>, greater<>> pq;
    vec<bool> used(n, false);
    pq.push({0,0,0});
    
    for (u32 i = 0; i < n; ++i) {
        if (used[i]) continue;
        pq.push({0,i,i});
        while (pq.size()) {
            auto [w, v, a] = pq.top(); pq.pop();
            if (used[v]) continue;
            if (v != a) tree.push_back({a,v,w});
            used[v] = true;
            tree_sum += w;

            for (auto [to, weight] : g[v]) {
                if (used[to]) continue;
                pq.push({weight,to,v});
            }
        }
    }
    return tree_sum;
}

i32 main() {
    ifstream file("input.txt");
    u32 n, m; file >> n >> m;
    vec<vec<duplet>> g(n);
    vec<triplet> tree;
    tree.reserve(n-1);

    for (u32 f, t, w, i = 0; i < m; ++i) {
        file >> f >> t >> w; f--; t--;
        g[f].push_back({t, w});
        g[t].push_back({f, w});
    }

    cout << prim(g, tree) << '\n';
    return 0;
}
