#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
using usize = size_t;
using u32 = unsigned int;
using i32 = int;

struct Frame {u32 v, n;};

u32 find_bridges(vector<vector<pair<u32, u32>>> &g, vector<u32> &scc)
{
    priority_queue<<vector<u32,u32>, greater<>> pq;
    u32 s = g.size();
    u32 counter = 0;
    vector<Frame> frames;
    vector<u32> tin(s, 0);
    vector<u32> low(s, 0);
    return counter;
}

i32 main(void) {
    /* size, edges */
    u32 n, m;
    ifstream file("test.txt");
    file >> n >> m;

    vector<u32> scc(n);
    vector<vector<pair<u32,u32>>> g(n);
    for (u32 src, sin, i = 0; i < m; ++i) {
        file >> src >> sin; src--; sin--;
        g[src].push_back({sin, 1});
        g[sin].push_back({src, 1});
    }

    cout << "SCC count: " << find_bridges(g, scc) << endl;
    return 0;
}
