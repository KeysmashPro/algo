#include <iostream>
#include <vector>

template <typename T>
using vec = std::vector<T>;

using namespace std;
using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;
using i32 = int;

class bitree {
    vec<i64> deriv;
    vec<i64> idiff;
    i32 n;

    void m_init(i32 i, i64 d) {
        i32 g = i * d;
        deriv[i] += d;
        idiff[i] += g;
        i32 x = i + (i & -i);
        if (x > n) return;
        deriv[x] += d;
        idiff[x] += g;
    }

public:
    /* Constructor */
    bitree(const vec<i64> &arr)
        : deriv(arr.size() + 1, 0),
          idiff(arr.size() + 1, 0),
          n(arr.size()) {
            m_init(1, arr[0]);
            for (i32 i = 2; i <= n; ++i) {
                m_init(i, arr[i-1] - arr[i-2]);
            }
    }

    /*-----------------------*/
    bitree(const vec<i64>& arr)
    : deriv(arr.size() + 1, 0),
      idiff(arr.size() + 1, 0),
      n(arr.size()) {
        if (n == 0) return;
        // 1) сырой разностный массив
        deriv[1] = arr[0];
        idiff[1] = 1 * arr[0];
        for (i32 i = 2; i <= n; ++i) {
            i64 d = arr[i-1] - arr[i-2];
            deriv[i] = d;
            idiff[i] = (i64)i * d;
        }
        // 2) один проход: слить поддеревья в родителей
        for (i32 i = 1; i <= n; ++i) {
            i32 j = i + (i & -i);
            if (j <= n) {
                deriv[j] += deriv[i];
                idiff[j] += idiff[i];
            }
        }
    }
    /*------------------------*/

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

    i64 range(u32 l, u32 r) {
        return prefix(r) - prefix(l);
    }

    void change(i32 i, i64 d) {
        i64 g = d * i;
        for(;i <= n; i += i & -i) {
            deriv[i] += d;
            idiff[i] += g;
        }
    }

    void update(i32 l, i32 r, i64 d) {
        change(l + 1, d);
        if (r <= n) return;
        change(r + 1,-d);
    }
};

i32 main() {
    bitree ft({1,4,0,8,9,3,1,7});
    cout << ft.range(0, 8) << endl;
    return 0;
}

