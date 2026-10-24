#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
using vec = std::vector<T>;

using namespace std;
using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;
using i32 = int;

struct ring { u32 i, o, h; };

i32 main(void) {
    u32 n; cin >> n;
    vec<tuple<u32,u32,u32>> l;
    l.reserve(n);

    for (u32 a, b, h, i = 0; i < n; ++i) {
        cin >> a >> b >> h;
        l.push_back({a, b, h});
    }

    sort(l.begin(), l.end(), [](ring a, ring b){
            return a.o > b.o;
    });

    
    return 0;
}
