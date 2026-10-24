#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

template <typename T>
using vec = std::vector<T>;

using namespace std;
using u32 = unsigned;
using i32 = int;

struct edge{u32 f, t, w;};

u32 root_dsu(u32 x, vec<u32> &dsu) {
    return (dsu[x] == x) ? x : dsu[x] = root_dsu(dsu[x], dsu);
}

u32 unite_dsu(u32 x1, u32 x2, vec<u32> &dsu, vec<u32> &rng) {
    u32 r1 = root_dsu(x1, dsu);
    u32 r2 = root_dsu(x2, dsu);
    if (rng[r1] < rng[r2]) swap(r1, r2);
    rng[r1] += rng[r2];
    return dsu[r2] = r1;
}

u32 kruskal(vec<edge> &g, vec<edge> &tree, vec<u32> &dsu, vec<u32> &rng)
{
    u32 accum = 0;
    for (auto x : g) {
        if (tree.size() == g.size() - 1) break;
        if (root_dsu(x.f, dsu) == root_dsu(x.t, dsu)) continue;
        unite_dsu(x.f, x.t, dsu, rng);
        tree.push_back(x);
        accum += x.w;
    }
    return accum;
}

i32 main()
{
    ifstream file("input.txt");
    u32 n, m;
    file >> n >> m;
    vec<edge> g(m);
    vec<edge> tree;
    tree.reserve(n-1);

    for (u32 f, t, w, i = 0; i < m; ++i) {
        file >> f >> t >> w; f--; t--;
        g[i] = {f, t, w};
    }

    std::sort(g.begin(), g.end(), [](const auto &a, const auto &b) {
        return a.w < b.w;
    });

    vec<u32> dsu(n, 0);
    vec<u32> rng(n, 1);
    for (u32 i = 0; i < n; ++i) dsu[i] = i;

    cout << kruskal(g, tree, dsu, rng) << '\n';
    return 0;
}
