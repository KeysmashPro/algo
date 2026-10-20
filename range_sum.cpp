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
    vec<i64> deriv;
    vec<i64> idiff;
    i32 n; // size

    /* array of values */
    explicit bitree(const vec<i64> &arr)
        : deriv(arr.size() + 1, 0),
          idiff(arr.size() + 1, 0),
          n(arr.size()) {
            for (i32 i = 0; i < n; ++i) {
                update(i, i + 1, arr[i]);
            }
    };

    /* [l,r) */
    void update(i32 l, i32 r, i64 d) {
        add(l + 1, d);  /* start  */
        add(r + 1,-d);  /* finish */
    }

    i64 prefix(i32 idx) {
        i64 res = 0;
        for (i32 i = idx; i > 0; i -= i & -i) {
            res += deriv[i];
        }
        res *= idx + 1;

        for (i32 i = idx; i > 0; i -= i & -i) {
            res -= idiff[i];
        }
        return res;
    }

    /* [l,r) */
    i64 range(u32 l, u32 r) {
        return prefix(r) - prefix(l);
    }

    private: 
    void add(i32 i, i64 d) {
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
