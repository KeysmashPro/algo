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
    vec<vec<i128>> bit;
    u64 n;

    explicit bitree(const vec<i64> &arr)
        : bit(arr.size() + 1, vec<i128>(arr.size() + 1, 0)),
          n(arr.size()) {
            for (i64 i = 0; i < n; ++i) {

                update(i, i + 1, arr[i]);
            }
    };

    /* [l,r) */
    void update(i64 l, i64 r, i64 d) {
        add(l + 1, d);  /* start  */
        add(r + 1,-d);  /* finish */
    }

    i64 prefix(i64 idx) {
        i128 res = 0;
        for (i64 i = idx; i > 0; i -= i & -i) {
            res += deriv[i];
        }
        res *= idx + 1;

        for (i64 i = idx; i > 0; i -= i & -i) {
            res -= idiff[i];
        }
        return (i64)res;
    }

    /* [l,r) */
    i64 range(i64 l, i64 r) {
        return prefix(r) - prefix(l);
    }

    private: 
    void add(i64 i, i64 d) {
        i64 g = i * d;
        for (; i <= n; i += i & -i) {
            deriv[i] += d;
            idiff[i] += g;
        }
    }
};

i32 main() {
    bitree ft({1,4,0,8,9,3,1,7});
    ft.update(0, 8, 2);
    cout << ft.range(0, 8) << endl;
    return 0;
}
