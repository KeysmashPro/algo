#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

template <typename T>
using vec = std::vector<T>;

using namespace std;
using usize = size_t;
using u32 = unsigned int;
using i32 = int;

struct Frame {u32 v, n, a, c;};

vec<pair<u32,u32>> find_bridges(vec<vec<pair<u32,u32>>> &g)
{
    u32 n = g.size();
    u32 counter = 1;
    vec<Frame> frames;
    vec<pair<u32,u32>> bridges;
    vec<u32> tin(n, 0);
    vec<u32> low(n, 0);

    for (u32 s = 0; s < n; ++s) {
        if (tin[s]) continue;
        tin[s] = low[s] = ++counter;
        frames.push_back({s, 0, s, 0});

        while(!frames.empty()) {
            auto &top = frames.back();
            auto [v, n, a, c] = top;
            if (n < g[v].size()) {
                top.n++;
                u32 to = g[v][n].first;
                if (to == a) continue;
                if (!tin[to]) {
                    frames.push_back({to, 0, v, 0});
                    tin[to] = low[to] = ++counter;
                } else {
                    low[v] = min(low[v], tin[to]);
                }
                continue;
            }
            frames.pop_back();

            low[a] = min(low[a], low[v]);
            if(low[v] > tin[a]) {
                bridges.push_back({a, v});
            }
        }
    }
    return bridges;
}

i32 main(void) {
    ifstream file("input.txt");
    u32 n, m;
    file >> n >> m;
    vec<vec<pair<u32,u32>>> g(n);
    for (u32 src, sin, i = 0; i < m; ++i) {
        file >> src >> sin; src--; sin--;
        g[src].push_back({sin, 1});
        g[sin].push_back({src, 1});
    }

    vec<pair<u32,u32>> bridges = find_bridges(g);
    std::sort(bridges.begin(), bridges.end());
    cout << "Bridges count: " << bridges.size() << "\n[ ";
    for (auto x : bridges) { cout << x.first + 1 << '-' << x.second + 1 << ' '; }
    cout << "]\n";
    return 0;
}
