#include <iostream>
#include <vector>

template <typename T>
using vec = std::vector<T>;

using namespace std;
using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;
using i32 = int;


struct bitree {
    vec<i64> bit; i32 n;

    explicit bitree(i32 s)
        : bit(s + 1, 0), n(s) {}
    
    explicit bitree(const vec<i64> &arr)
        : bit(arr.size() + 1, 0), n(arr.size()) {
            for (i32 i = 0; i < n; ++i) {
                change(i + 1, arr[i]);
            }
    }

    void change(i32 i, i64 delta) {
        for (; i <= n; i += i & -i) {
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
    };
};

i32 main() {
    bitree ft({1,0,4,8,9,3,1,7});
    cout << ft.range(1, 8) << endl;
    return 0;
}
