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

struct Frame {u32 v, n, a, c, m;};

void find_all(vec<vec<pair<u32,u32>>> &g, vec<u32> &scc, vec<pair<u32,u32>> &bridges, vec<u32> &points)
{
    u32 n = g.size();
    vec<bool> ispoint(n, false);
    vec<bool> on_stak(n, false);
    vec<u32> stak;

    vec<u32> tin(n, 0);
    vec<u32> low(n, 0);
    u32 counter = 0;
    u32 scc_cnt = 0;

    vec<Frame> frames;

    for(u32 start = 0; start < n; ++start) {
        if (tin[start]) continue;
        tin[start] = low[start] = ++counter;
        frames.push_back({start, 0, start, 0, 0});

        while (!frames.empty()) {
            auto [v, n, a, c, m] = frames.back();
            if (n < g[v].size()) {
                auto to = g[v][n].first;
                frames.back().n++;
                if (to == a) continue;
                if (!tin[to]) {
                    frames.back().c++;
                    on_stak[to] = true;
                    stak.push_back(to);
                    tin[to] = low[to] = ++counter;
                    frames.push_back({to ,0 , v, 0, 0});
                } else {
                    low[v] = min(low[v], tin[to]);
                }
                continue;
            }
            frames.pop_back();

            if (tin[v] == low[a]) {
                scc_cnt++;
                for(;;) {
                    u32 t = stak.back();
                    on_stak[t] = false;
                    stak.pop_back();
                    scc[t] = scc_cnt;
                    if (t == v) break;
                }
            }

            if (frames.empty()) {
                if (c > 1) { ispoint[v] = true; continue; }
                else { continue; }
            }

            if (low[v] > tin[a]) bridges.push_back({a, v});
            if (m >= tin[v]) points.push_back(v);

            frames.back().m = max(frames.back().m, m);
            low[a] = min(low[a], low[v]);
        }
    }
    for (u32 i = 0; i < n; ++i) {
        if (ispoint[i]) { points.push_back(i); }
    }
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

    vector<pair<u32,u32>> bridges;
    vector<u32> points;
    vector<u32> scc(n);

    find_all(g, scc, bridges, points);
    sort(points.begin(), points.end());
    sort(bridges.begin(), bridges.end());

    cout << "Articulation points count: " << points.size() << " | [ ";
    for (auto x : points) { cout << x + 1 << ' '; } cout << "]\n";

    cout << "Bridges count: " << points.size() << " | [ ";
    for (auto x : bridges) { cout << x.first + 1 << ' ' << x.second + 1 << ' '; }
    cout << "]\n";

    return 0;
}
