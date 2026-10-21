#include <iostream>
#include <vector>

template <typename T>
using vec = std::vector<T>;

using namespace std;
using i128 = __int128_t;
using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;
using i32 = int;

struct bitree {
    vec<i64> bit;
    i32 n;

    bitree(const vec<i64> &arr)
        : bit(arr.size() + 1, 0), n(arr.size()) {
            for (i32 i = 1; i <= n; ++i) {
                bit[i] += arr[i-1];
                i32 x = i + (i & -i);
                if (x > n) continue;
                bit[x] += bit[i];
            }
    }

    void change(i32 x, i64 delta) {
        for (i32 i = x + 1; i <= n; i += i & -i) {
            bit[i] += delta;
        }
    }

    i64 prefix(u32 i) {
        i64 res = 0;
        for (; i > 0; i -= i & -i) {
            res += bit[i];
        }
        return res;
    }

    i64 range(u32 l, u32 r) {
        return prefix(r) - prefix(l);
    }
};

i32 main() {
    bitree ft({1,2,3,4,5,6});
    ft.change(0,-1);
    ft.change(4, 4);
    cout << ft.range(0, 6) << endl;
    return 0;
}
